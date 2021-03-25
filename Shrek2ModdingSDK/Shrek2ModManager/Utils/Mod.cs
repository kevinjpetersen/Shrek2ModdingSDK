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
        public string Username { get; set; }
        public int Verified { get; set; }
        public int Official { get; set; }
        public int Visible { get; set; }
        public int Approved { get; set; }
        public int HasThumbnail { get; set; }
        public string ModGUID { get; set; }
        public DateTime? Created { get; set; }
        public DateTime? Modified { get; set; }

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
    }
}
