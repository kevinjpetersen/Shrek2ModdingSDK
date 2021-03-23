using Newtonsoft.Json;
using System;
using System.Collections.Generic;
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
        public string Author { get; set; }
        public bool Verified { get; set; }
        public string InternalName { get; set; }

        public static List<Mod> GetMods()
        {
            try
            {
                ServicePointManager.Expect100Continue = true;
                ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;
                var json = new WebClient().DownloadString("https://shrek2modding.fra1.digitaloceanspaces.com/mods.json");
                if (string.IsNullOrWhiteSpace(json)) return new List<Mod>();
                return JsonConvert.DeserializeObject<List<Mod>>(json);
            }
            catch
            {
                return new List<Mod>();
            }
        }
    }
}
