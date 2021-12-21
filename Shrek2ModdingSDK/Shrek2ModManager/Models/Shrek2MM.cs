using ICSharpCode.SharpZipLib.Zip;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager
{
    public class Shrek2MM
    {
        private static string ListToJSON(List<Shrek2ModListItem> items)
        {
            if (items == null) return "[]";

            return JsonConvert.SerializeObject(items, Formatting.Indented);
        }

        private static List<Shrek2ModListItem>? JSONToList(string json)
        {
            if (string.IsNullOrEmpty(json)) return new List<Shrek2ModListItem>();

            var items = JsonConvert.DeserializeObject<List<Shrek2ModListItem>>(json);
            if (items == null) return null;
            return items;
        }

        private static string SettingsToJSON(Shrek2MMSettings settings)
        {
            if (settings == null) return "{}";

            return JsonConvert.SerializeObject(settings, Formatting.Indented);
        }

        private static Shrek2MMSettings? JSONToSettings(string json)
        {
            if (string.IsNullOrEmpty(json)) return new Shrek2MMSettings();

            return JsonConvert.DeserializeObject<Shrek2MMSettings>(json);
        }

        public static bool SaveMods(List<Shrek2ModListItem> items)
        {
            try
            {
                Shrek2Utils.EnsureDataFolderExists();

                var json = ListToJSON(items);
                File.WriteAllText(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_ADDED_MODS), json);
                return true;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }

        public static List<Shrek2ModListItem>? LoadMods()
        {
            try
            {
                Shrek2Utils.EnsureDataFolderExists();

                if (File.Exists(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_ADDED_MODS)) == false) return new List<Shrek2ModListItem>();

                var json = File.ReadAllText(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_ADDED_MODS));
                return JSONToList(json);
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return null;
            }
        }

        public static bool SaveSettings(Shrek2MMSettings settings)
        {
            try
            {
                Shrek2Utils.EnsureDataFolderExists();

                var json = SettingsToJSON(settings);
                File.WriteAllText(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_SETTINGS), json);
                return true;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }

        public static Shrek2MMSettings? LoadSettings()
        {
            try
            {
                Shrek2Utils.EnsureDataFolderExists();

                if (File.Exists(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_SETTINGS)) == false) return new Shrek2MMSettings();

                var json = File.ReadAllText(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_SETTINGS));
                return JSONToSettings(json);
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return null;
            }
        }

        public static bool CopyModToDataFolder(string filePath, string uuid)
        {
            try
            {
                Shrek2Utils.EnsureAddedModsFolderExists();

                File.Copy(filePath, Path.Combine(Shrek2Utils.GetAddedModsFolderPath(), $"{uuid}{Path.GetExtension(filePath)}"));

                return true;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }

        public static bool DeleteModFromDataFolder(string? fileName)
        {
            try
            {
                if (fileName == null) return false;

                Shrek2Utils.EnsureAddedModsFolderExists();

                var filePath = Path.Combine(Shrek2Utils.GetAddedModsFolderPath(), fileName);

                if (File.Exists(filePath) == false) return true;

                File.Delete(filePath);

                return true;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }

        public static async Task<bool> ExtractModLoader()
        {
            try
            {
                Shrek2Utils.EnsureDataFolderExists();

                var assembly = Assembly.GetExecutingAssembly();
                var resourceName = assembly.GetManifestResourceNames().Single(str => str.EndsWith(Shrek2Utils.SHREK2MM_FILE_MOD_LOADER_ZIP));

                if (string.IsNullOrEmpty(resourceName)) return false;

                using (var resStream = assembly.GetManifestResourceStream(resourceName))
                {
                    var ms = new MemoryStream();

                    if (resStream != null)
                    {
                        await resStream.CopyToAsync(ms);
                        var bytes = ms.ToArray();

                        File.WriteAllBytes(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_MOD_LOADER_ZIP), bytes);

                        return true;
                    }
                }

                return false;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }

        public static bool InstallModLoader(string gameFolderPath)
        {
            try
            {
                if (IsModLoaderInstalled(gameFolderPath)) return true;

                if (Directory.Exists(gameFolderPath) == false) return false;
                if (Directory.Exists(Shrek2Utils.GetGameSystemFolderPath(gameFolderPath)) == false) return false;

                if (Directory.Exists(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath)) == false)
                {
                    Directory.CreateDirectory(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath));
                }

                var zipFilePath = Shrek2Utils.GetModLoaderZipFilePath();
                var targetDir = Shrek2Utils.GetGameSystemFolderPath(gameFolderPath);
                FastZip fastZip = new FastZip();

                fastZip.ExtractZip(zipFilePath, targetDir, null);

                return true;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }

        public static bool IsModLoaderInstalled(string gameFolderPath)
        {
            try
            {
                if (Directory.Exists(gameFolderPath) == false) return false;
                if (Directory.Exists(Shrek2Utils.GetGameSystemFolderPath(gameFolderPath)) == false) return false;
                if (File.Exists(Path.Combine(Shrek2Utils.GetGameSystemFolderPath(gameFolderPath), Shrek2Utils.SHREK2MM_MODLOADER_FILE_EXE)) == false) return false;
                if (File.Exists(Path.Combine(Shrek2Utils.GetGameSystemFolderPath(gameFolderPath), Shrek2Utils.SHREK2MM_MODLOADER_FILE_INT)) == false) return false;
                if (File.Exists(Path.Combine(Shrek2Utils.GetGameSystemFolderPath(gameFolderPath), Shrek2Utils.SHREK2MM_MODLOADER_FILE_DLL)) == false) return false;

                return true;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }

        public static bool ReinstallMods(string gameFolderPath, List<Shrek2ModListItem> mods)
        {
            try
            {
                if (IsModLoaderInstalled(gameFolderPath) == false) return false;

                if (Directory.Exists(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath)) == false)
                {
                    Directory.CreateDirectory(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath));
                }
                else
                {
                    Directory.Delete(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath), true);
                    Directory.CreateDirectory(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath));
                }

                if (mods == null || mods.Count <= 0) return false;

                foreach (var mod in mods)
                {
                    Directory.CreateDirectory(Path.Combine(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath), mod.UUID));
                    if (mod.ModType == Shrek2ModListItem.ModTypes.ModFile)
                    {
                        File.Copy(Path.Combine(Shrek2Utils.GetAddedModsFolderPath(), mod.FileName), Path.Combine(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath), mod.UUID, mod.FileName));
                    }
                    else if (mod.ModType == Shrek2ModListItem.ModTypes.ModZip)
                    {
                        var zipFilePath = Path.Combine(Shrek2Utils.GetAddedModsFolderPath(), mod.FileName);
                        var targetDir = Path.Combine(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath), mod.UUID);
                        FastZip fastZip = new FastZip();
                        fastZip.ExtractZip(zipFilePath, targetDir, null);

                        string dllFilePath = Path.Combine(Shrek2Utils.GetGameSystemModsFolderPath(gameFolderPath), mod.UUID, $"{mod.UUID}.dll");

                        var files = Directory.GetFiles(targetDir);

                        if(files.Length <= 0)
                        {
                            Shrek2Utils.LogError(new Exception($"Failed to install the mod '{mod.Title}' because it had no files inside of it's .zip file."));
                            return false;
                        }

                        var zipDllName = files.FirstOrDefault(p => Path.GetExtension(p) == ".dll");

                        if(string.IsNullOrWhiteSpace(zipDllName))
                        {
                            Shrek2Utils.LogError(new Exception($"Failed to install the mod '{mod.Title}' a .dll file inside of the .zip file doesn't exist!"));
                            return false;
                        }

                        if(File.Exists(zipDllName))
                        {
                            FileInfo fi = new FileInfo(zipDllName);

                            if (fi.Exists)
                            {
                                fi.MoveTo(dllFilePath);
                            }
                        }

                    }
                }

                return true;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }

        public static bool UpdateDefUserFile(string gameFolderPath, List<Shrek2ModListItem> mods)
        {
            try
            {
                if (mods == null || mods.Count <= 0) return false;
                if (IsModLoaderInstalled(gameFolderPath) == false) return false;

                var backupDefUserFilePath = Path.Combine(Shrek2Utils.GetGameSystemFolderPath(gameFolderPath), Shrek2Utils.SHREK2MM_DEF_USER_BACKUP_FILE);
                var defUserFilePath = Path.Combine(Shrek2Utils.GetGameSystemFolderPath(gameFolderPath), Shrek2Utils.SHREK2MM_DEF_USER_FILE);

                if (File.Exists(backupDefUserFilePath) == false)
                {
                    File.Copy(defUserFilePath, backupDefUserFilePath, true);
                }

                var lines = File.ReadAllLines(defUserFilePath);

                string execString = "";
                int x = 1;
                foreach (var installedMod in mods)
                {
                    if (x == mods.Count)
                    {
                        execString += "exec " + installedMod.UUID.Replace(" ", "");
                    }
                    else
                    {
                        execString += "exec " + installedMod.UUID.Replace(" ", "") + " | ";
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

                File.WriteAllLines(defUserFilePath, lines);
                return true;
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return false;
            }
        }
    }
}
