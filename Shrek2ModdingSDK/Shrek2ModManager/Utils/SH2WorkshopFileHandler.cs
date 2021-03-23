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
        private const string PublicMapFolder = "Shrek2WorkshopMaps";
        private const string MapFolder = "Maps";
        private const string ModsFolder = "Mods";
        private const string UploadFolder = "Upload";

        private const string MapDownloadUrlPrefix = "https://shrek2workshop.ams3.digitaloceanspaces.com/Maps";

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

        public static bool IsMapDownloaded(string mapId)
        {
            if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), MapFolder)) == false) return false;
            return File.Exists(Path.Combine(Directory.GetCurrentDirectory(), MapFolder, $"{mapId}.zip"));
        }

        public static bool IsModDownloaded(string modId)
        {
            if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder)) == false) return false;
            return File.Exists(Path.Combine(Directory.GetCurrentDirectory(), ModsFolder, $"{modId}.zip"));
        }

        public static bool IsMapInstalled(string mapId)
        {
            if (Directory.Exists(Path.Combine(GetHarddrivePath(), PublicMapFolder)) == false) return false;
            return File.Exists(Path.Combine(GetHarddrivePath(), PublicMapFolder, $"{mapId}.unr"));
        }

        public static string GetMapPath(string mapId)
        {
            if (File.Exists(Path.Combine(GetHarddrivePath(), PublicMapFolder, $"{mapId}.unr")) == false) return null;
            return Path.Combine(GetHarddrivePath(), PublicMapFolder, $"{mapId}.unr");
        }

        public static string GetHarddrivePath()
        {
            return Path.GetPathRoot(Environment.GetFolderPath(Environment.SpecialFolder.System));
        }

        public static async Task<bool> DownloadMap(string mapId, Action<object, DownloadProgressChangedEventArgs> downloadProgress)
        {
            try
            {
                if (IsMapDownloaded(mapId)) return true;

                if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), MapFolder)) == false)
                {
                    Directory.CreateDirectory(Path.Combine(Directory.GetCurrentDirectory(), MapFolder));
                }

                using (var client = new WebClient())
                {
                    client.DownloadProgressChanged += (s, d) => downloadProgress(s, d);
                    await client.DownloadFileTaskAsync($"{MapDownloadUrlPrefix}/{mapId}.zip", Path.Combine(Directory.GetCurrentDirectory(), MapFolder, $"{mapId}.zip"));
                    return true;
                }
            }
            catch
            {
                return false;
            }
        }

        public static bool ExtractMapFile(string mapId)
        {
            try
            {
                if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), MapFolder)) == false) return false;
                if (Directory.Exists(Path.Combine(GetHarddrivePath(), PublicMapFolder)) == false)
                {
                    Directory.CreateDirectory(Path.Combine(GetHarddrivePath(), PublicMapFolder));
                }

                var packagedFilePath = Path.Combine(Directory.GetCurrentDirectory(), MapFolder, $"{mapId}.zip");
                if (File.Exists(packagedFilePath) == false) return false;

                using (FileStream fs = new FileStream(packagedFilePath, FileMode.Open))
                using (ZipArchive arch = new ZipArchive(fs, ZipArchiveMode.Read))
                {
                    arch.ExtractToDirectory(Path.Combine(GetHarddrivePath(), PublicMapFolder));
                }

                return true;
            }
            catch
            {
                return false;
            }
        }

        public static string PackageMapFile(string filePath, string mapId)
        {
            try
            {
                if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), UploadFolder)) == false)
                {
                    Directory.CreateDirectory(Path.Combine(Directory.GetCurrentDirectory(), UploadFolder));
                }

                var packagedFilePath = Path.Combine(Directory.GetCurrentDirectory(), UploadFolder, $"{mapId}.zip");

                using (FileStream fs = new FileStream(packagedFilePath, FileMode.Create))
                using (ZipArchive arch = new ZipArchive(fs, ZipArchiveMode.Create))
                {
                    arch.CreateEntryFromFile(filePath, $"{mapId}.unr");
                }

                return packagedFilePath;
            }
            catch
            {
                return null;
            }
        }
    }
}
