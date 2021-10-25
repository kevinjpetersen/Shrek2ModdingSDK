using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager.Utils
{
    public class Shrek2Binds
    {
        public static Dictionary<string, string> GetBinds(Mod mod)
        {
            try
            {
                if (SH2WorkshopFileHandler.IsModBindable(mod.ModGUID) == false) return null;
                var settings = SH2WorkshopFileHandler.GetSettings();
                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return null;

                string bindsJson = File.ReadAllText(Path.Combine(settings.GameFolderLocation, SH2WorkshopFileHandler.ModsInstalledFolder, mod.ModGUID, "binds.json"));

                return JsonConvert.DeserializeObject<Dictionary<string, string>>(bindsJson);
            }
            catch
            {
                return null;
            }
        }

        public static bool SaveBinds(Mod mod, Dictionary<string, string> binds)
        {
            try
            {
                if (SH2WorkshopFileHandler.IsModBindable(mod.ModGUID) == false) return false;
                var settings = SH2WorkshopFileHandler.GetSettings();
                if (string.IsNullOrWhiteSpace(settings.GameFolderLocation)) return false;

                File.WriteAllText(Path.Combine(settings.GameFolderLocation, SH2WorkshopFileHandler.ModsInstalledFolder, mod.ModGUID, "binds.json"), JsonConvert.SerializeObject(binds, Formatting.Indented));
                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
