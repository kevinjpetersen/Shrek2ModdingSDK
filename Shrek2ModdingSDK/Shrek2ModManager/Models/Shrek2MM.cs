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
    }
}
