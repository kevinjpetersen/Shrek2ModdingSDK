using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager.Utils
{
    public class Shrek2Config
    {
        public Dictionary<string, object> Config { get; set; }
        public Dictionary<string, string> Docs { get; set; }

        public static Shrek2Config GetConfig(Mod mod)
        {
            try
            {
                if (SH2WorkshopFileHandler.IsModConfigable(mod.ModGUID) == false) return null;
                var settings = SH2WorkshopFileHandler.GetSettings();
                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return null;

                string configJson = File.ReadAllText(Path.Combine(settings.GameFolderLocation, SH2WorkshopFileHandler.ModsInstalledFolder, mod.ModGUID, "config.json"));

                return JsonConvert.DeserializeObject<Shrek2Config>(configJson);
            }
            catch
            {
                return null;
            }
        }

        public bool SaveConfig(Mod mod)
        {
            try
            {
                if (SH2WorkshopFileHandler.IsModConfigable(mod.ModGUID) == false) return false;
                var settings = SH2WorkshopFileHandler.GetSettings();
                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

                File.WriteAllText(Path.Combine(settings.GameFolderLocation, SH2WorkshopFileHandler.ModsInstalledFolder, mod.ModGUID, "config.json"), JsonConvert.SerializeObject(this, Formatting.Indented));
                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
