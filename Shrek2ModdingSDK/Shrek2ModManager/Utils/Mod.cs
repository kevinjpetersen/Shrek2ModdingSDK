using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager.Utils
{
    public class Mod
    {
        public int ID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public string Username { get; set; }
        public int Verified { get; set; }
        public int Official { get; set; }
        public int Visible { get; set; }
        public int Approved { get; set; }
        public int HasThumbnail { get; set; }
        public string ModGUID { get; set; }
        public DateTime? Created { get; set; }
        public DateTime? Modified { get; set; }
        public int VersionNumber { get; set; }
        public string VersionText { get; set; }
        public int RunType { get; set; }

        public static List<Mod> GetMods()
        {
            try
            {
                ServicePointManager.Expect100Continue = true;
                ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;
                var json = new WebClient().DownloadString("https://shrek2mods.com/api/mod/getmods");
                if (string.IsNullOrWhiteSpace(json)) return new List<Mod>();
                return JsonConvert.DeserializeObject<List<Mod>>(json);
            }
            catch
            {
                return new List<Mod>();
            }
        }

        public static List<Mod> GetInstalledMods(List<Mod> modList)
        {
            try
            {
                var settings = SH2WorkshopFileHandler.GetSettings();

                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return new List<Mod>();

                if (Directory.Exists(Path.Combine(settings.GameFolderLocation, SH2WorkshopFileHandler.ModsInstalledFolder)) == false) return new List<Mod>();
                var modGuids = Directory.GetDirectories(Path.Combine(settings.GameFolderLocation, SH2WorkshopFileHandler.ModsInstalledFolder));

                var installedMods = new List<Mod>();
                foreach(var mgPath in modGuids)
                {
                    var mg = Path.GetFileName(mgPath);
                    if(modList.Any(p => p.ModGUID == mg))
                    {
                        var mod = modList.FirstOrDefault(p => p.ModGUID == mg);
                        if (mod == null) continue;
                        installedMods.Add(mod);
                    }
                }
                return installedMods;
            }
            catch
            {
                return new List<Mod>();
            }
        }
    }
}
