using ICSharpCode.SharpZipLib.Zip;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using static System.Environment;

namespace Shrek2ModManager.Utils
{
    public class SH2WorkshopFileHandler
    {
        private const string ModsFolder = "Mods";
        private const string ModsInstalledFolder = "Shrek 2 Mods";

        private const string ModDownloadUrlPrefix = "https://shrek2modding.fra1.digitaloceanspaces.com/Mods";
        private const string InternalDownloadUrlPrefix = "https://shrek2modding.fra1.digitaloceanspaces.com/Internal";

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

        public static bool IsModInstalled(string modId)
        {
            var settings = GetSettings();

            if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

            return Directory.Exists(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder, modId));
        }

        public static async Task<bool> DownloadMod(string modId, Action<object, DownloadProgressChangedEventArgs> downloadProgress)
        {
            try
            {
                if (IsModDownloaded(modId)) return true;

                if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder)) == false)
                {
                    Directory.CreateDirectory(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder));
                }

                using (var client = new WebClient())
                {
                    client.DownloadProgressChanged += (s, d) => downloadProgress(s, d);
                    await client.DownloadFileTaskAsync($"{ModDownloadUrlPrefix}/{modId}.zip", Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{modId}.zip"));
                    return true;
                }
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

                var packagedFilePath = Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{modId}.zip");
                if (File.Exists(packagedFilePath) == false) return false;

                using (FileStream fs = new FileStream(packagedFilePath, FileMode.Open))
                using (ZipArchive arch = new ZipArchive(fs, ZipArchiveMode.Read))
                {
                    arch.ExtractToDirectory(Path.Combine(settings.GameFolderLocation, ModsInstalledFolder));
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
