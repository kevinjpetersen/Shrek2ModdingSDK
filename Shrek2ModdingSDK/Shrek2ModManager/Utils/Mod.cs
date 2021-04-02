using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace Shrek2ModManager.Utils
{
    public class Mod
    {
        public class VisualMod
        {
            public string Name { get; set; }
            public string Author { get; set; }
            public string Image { get; set; }
            public Visibility ImageVisibility { get; set; }
            public string IsInstalled { get; set; }
            public Brush InstalledButtonColor { get; set; }
            public string Description { get; set; }
            public Mod Mod { get; set; }
            public bool UpdateAvailable { get; set; }

            public static List<VisualMod> ToVisualMods(List<Mod> mods)
            {
                var installedMods = SH2WorkshopFileHandler.GetInstalledModObjects();
                return mods.Select(p => new VisualMod(p, installedMods.Any(i => i.ModGUID == p.ModGUID), installedMods.Any(i => i.ModGUID == p.ModGUID && i.VersionNumber < p.VersionNumber))).ToList();
            }

            public VisualMod(Mod mod, bool isInstalled, bool updateAvailable)
            {
                Name = mod.Name;
                Author = $"By {mod.Username}";
                Image = mod.HasThumbnail == 1 ? $"{SH2WorkshopFileHandler.ThumbnailDownloadUrlPrefix}/{mod.ModGUID}.png" : "https://shrek2modding.fra1.digitaloceanspaces.com/Internal/defaultmodimage.jpeg";
                ImageVisibility = mod.Verified == 1 ? Visibility.Visible : Visibility.Hidden;
                IsInstalled = isInstalled ? "Uninstall" : "Install";
                InstalledButtonColor = isInstalled ? Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Red) : Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Green);
                Description = mod.Description.Replace("\n", " ");
                Mod = mod;

                if(updateAvailable)
                {
                    IsInstalled = "Update";
                    InstalledButtonColor = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Orange);
                    UpdateAvailable = true;
                }
            }
        }

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
