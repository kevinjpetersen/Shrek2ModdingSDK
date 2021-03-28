using ICSharpCode.SharpZipLib.Zip;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using static System.Environment;

namespace Shrek2ModManager.Utils
{
    public class SH2WorkshopFileHandler
    {
        private const string ModsFolder = "Mods";
        public const string ModsInstalledFolder = "Shrek 2 Mods";

        private const string ModDownloadUrlPrefix = "https://shrek2modding.fra1.digitaloceanspaces.com/Mods";
        private const string InternalDownloadUrlPrefix = "https://shrek2modding.fra1.digitaloceanspaces.com/Internal";
        public const string ThumbnailDownloadUrlPrefix = "https://shrek2modding.fra1.digitaloceanspaces.com/Thumbnails";

        public static bool SaveSettings(Settings settings)
        {
            try
            {
                if (settings == null) return false;
                File.WriteAllText(Path.Combine(Directory.GetCurrentDirectory(), "Settings.json"), JsonConvert.SerializeObject(settings));
                return true;
            }
            catch
            {
                return false;
            }
        }

        public static Settings GetSettings()
        {
            try
            {
                var settingsPath = Path.Combine(Directory.GetCurrentDirectory(), "Settings.json");
                if (File.Exists(Path.Combine(Directory.GetCurrentDirectory(), "Settings.json")) == false) return new Settings();

                return JsonConvert.DeserializeObject<Settings>(File.ReadAllText(Path.Combine(Directory.GetCurrentDirectory(), "Settings.json")));
            }
            catch
            {
                return new Settings();
            }
        }

        public static bool IsModDownloaded(string modId)
        {
            if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder)) == false) return false;
            return File.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{modId}.zip"));
        }

        public static bool IsInternalModFilesInstalled()
        {
            var settings = GetSettings();

            if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

            if (File.Exists(Path.Combine(settings.GameFolderLocation, "Shrek 2 Modded.exe")) == false) return false;
            if (File.Exists(Path.Combine(settings.GameFolderLocation, "Shrek 2 Modded.int")) == false) return false;
            if (File.Exists(Path.Combine(settings.GameFolderLocation, "Shrek2ModLoader.dll")) == false) return false;

            return true;
        }

        public static List<string> GetInstalledMods()
        {
            try
            {
                var settings = GetSettings();

                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return new List<string>();

                var installedModsFolder = Path.Combine(settings.GameFolderLocation, ModsInstalledFolder);

                if (Directory.Exists(installedModsFolder) == false) return new List<string>();

                var folders = Directory.EnumerateDirectories(installedModsFolder);

                var installedMods = new List<string>();

                foreach (var folder in folders)
                {
                    var files = Directory.GetFiles(folder);
                    bool foundMod = false;
                    foreach (var file in files)
                    {
                        if (foundMod) continue;
                        if (Path.GetExtension(file) == ".dll")
                        {
                            installedMods.Add(Path.GetFileNameWithoutExtension(file));
                            foundMod = true;
                        }
                    }
                }

                return installedMods;
            }
            catch
            {
                return new List<string>();
            }
        }

        public static bool HandleDefUserChanges()
        {
            try
            {
                var settings = GetSettings();

                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

                var backupFilePath = Path.Combine(settings.GameFolderLocation, "Backup_DefUser.ini");
                var realFilePath = Path.Combine(settings.GameFolderLocation, "DefUser.ini");

                if (File.Exists(backupFilePath) == false)
                {
                    File.Copy(realFilePath, backupFilePath);
                }

                var lines = File.ReadAllLines(realFilePath);

                var installedMods = GetInstalledMods();

                string execString = "";
                int x = 1;
                foreach (var installedMod in installedMods)
                {
                    if (x == installedMods.Count)
                    {
                        execString += "exec " + installedMod.Replace(" ", "");
                    }
                    else
                    {
                        execString += "exec " + installedMod.Replace(" ", "") + " | ";
                    }

                    x++;
                }

                for (int i = 0; i < lines.Length; i++)
                {
                    if (lines[i].Contains("F24="))
                    {
                        lines[i] = "F24=" + execString;
                    }
                }

                File.WriteAllLines(realFilePath, lines);
                return true;
            }
            catch
            {
                return false;
            }
        }

        public static bool IsModConfigable(string modId)
        {
            var settings = GetSettings();

            if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

            if (Directory.Exists(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder, modId)) == false) return false;
            return File.Exists(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder, modId, "config.json"));
        }

        public static bool IsModInstalled(string modId)
        {
            var settings = GetSettings();

            if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

            return Directory.Exists(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder, modId));
        }

        public static async Task<bool> DownloadInternalModFiles(Action<object, DownloadProgressChangedEventArgs> downloadProgress)
        {
            try
            {
                if (IsInternalModFilesInstalled()) return true;

                using (var client = new WebClient())
                {
                    client.DownloadProgressChanged += (s, d) => downloadProgress(s, d);
                    await client.DownloadFileTaskAsync($"{InternalDownloadUrlPrefix}/InternalModFiles.zip", Path.Combine(Directory.GetCurrentDirectory(), $"InternalModFiles.zip"));
                    return true;
                }
            }
            catch
            {
                return false;
            }
        }

        public static bool UninstallMod(Mod mod)
        {
            try
            {
                var settings = GetSettings();

                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;
                if (IsModInstalled(mod.ModGUID) == false) return false;

                var modPath = Path.Combine(settings.GameFolderLocation, ModsInstalledFolder, mod.ModGUID);
                Directory.Delete(modPath, true);

                bool zipFileExist = File.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{mod.ModGUID}.zip"));
                if (zipFileExist) File.Delete(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{mod.ModGUID}.zip"));

                RemoveModFromInstalledJson(mod);

                return true;
            }
            catch
            {
                return false;
            }
        }

        public static bool AddOrUpdateModToInstalledJson(Mod mod)
        {
            try
            {
                var installedJsonPath = Path.Combine(Directory.GetCurrentDirectory(), "installed_mods.json");
                if (File.Exists(installedJsonPath) == false)
                {
                    var mods = new List<Mod>() { mod };
                    File.WriteAllText(installedJsonPath, JsonConvert.SerializeObject(mods));
                    return true;
                }
                var installedMods = JsonConvert.DeserializeObject<List<Mod>>(File.ReadAllText(installedJsonPath));
                if(installedMods == null)
                {
                    installedMods = new List<Mod>();
                }

                if(installedMods.Any(p => p.ModGUID == mod.ModGUID))
                {
                    for(int i = 0; i < installedMods.Count; i++)
                    {
                        var m = installedMods[i];
                        if(m.ModGUID == mod.ModGUID)
                        {
                            installedMods[i] = mod;
                        }
                    }
                } else
                {
                    installedMods.Add(mod);
                }

                File.WriteAllText(installedJsonPath, JsonConvert.SerializeObject(installedMods));

                return true;
            }
            catch
            {
                return false;
            }
        }

        public static bool RemoveModFromInstalledJson(Mod mod)
        {
            try
            {
                var installedJsonPath = Path.Combine(Directory.GetCurrentDirectory(), "installed_mods.json");
                if (File.Exists(installedJsonPath) == false)
                {
                    return true;
                }
                var installedMods = JsonConvert.DeserializeObject<List<Mod>>(File.ReadAllText(installedJsonPath));
                if (installedMods == null)
                {
                    return true;
                }
                installedMods.RemoveAll(p => p.ModGUID == mod.ModGUID);

                File.WriteAllText(installedJsonPath, JsonConvert.SerializeObject(installedMods));

                return true;
            }
            catch
            {
                return false;
            }
        }

        public static async Task<bool> DownloadMod(Mod mod, Action<object, DownloadProgressChangedEventArgs> downloadProgress)
        {
            try
            {
                if (IsModDownloaded(mod.ModGUID)) return true;

                if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder)) == false)
                {
                    Directory.CreateDirectory(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder));
                }

                using (var client = new WebClient())
                {
                    client.DownloadProgressChanged += (s, d) => downloadProgress(s, d);
                    await client.DownloadFileTaskAsync($"{ModDownloadUrlPrefix}/{mod.ModGUID}.zip", Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{mod.ModGUID}.zip"));

                    if(AddOrUpdateModToInstalledJson(mod))
                    {
                        return true;
                    }

                    if(File.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{mod.ModGUID}.zip")))
                    {
                        File.Delete(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{mod.ModGUID}.zip"));
                    }
                    return false;
                }
            }
            catch
            {
                return false;
            }
        }

        public static bool ExtractInternalModFiles()
        {
            try
            {
                if (IsInternalModFilesInstalled()) return true;

                var settings = GetSettings();

                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

                var packagedFilePath = Path.Combine(Directory.GetCurrentDirectory(), $"InternalModFiles.zip");
                if (File.Exists(packagedFilePath) == false) return false;

                using (FileStream fs = new FileStream(packagedFilePath, FileMode.Open))
                using (ZipArchive arch = new ZipArchive(fs, ZipArchiveMode.Read))
                {
                    arch.ExtractToDirectory(settings.GameFolderLocation);
                }

                return true;
            }
            catch
            {
                return false;
            }
        }

        public static bool ExtractModFile(string modId)
        {
            try
            {
                var settings = GetSettings();

                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

                if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder)) == false) return false;
                if (Directory.Exists(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder)) == false)
                {
                    Directory.CreateDirectory(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder));
                }

                if(Directory.Exists(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder, modId)) == false)
                {
                    Directory.CreateDirectory(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder, modId));
                }

                var packagedFilePath = Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{modId}.zip");
                if (File.Exists(packagedFilePath) == false) return false;

                using (FileStream fs = new FileStream(packagedFilePath, FileMode.Open))
                using (ZipArchive arch = new ZipArchive(fs, ZipArchiveMode.Read))
                {
                    arch.ExtractToDirectory(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder, modId));
                }

                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
