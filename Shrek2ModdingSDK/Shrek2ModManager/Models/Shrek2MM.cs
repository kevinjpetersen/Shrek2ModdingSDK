using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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

        public static bool SaveMods(List<Shrek2ModListItem> items)
        {
            try
            {
                Shrek2Utils.EnsureDataFolderExists();

                var json = ListToJSON(items);
                File.WriteAllText(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_ADDED_MODS), json);
                return true;
            }
            catch(Exception ex)
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

                var json = File.ReadAllText(Path.Combine(Shrek2Utils.GetDataFolderPath(), Shrek2Utils.SHREK2MM_FILE_ADDED_MODS));
                return JSONToList(json);
            }
            catch(Exception ex)
            {
                Shrek2Utils.LogError(ex);
                return null;
            }
        }
    }
}
