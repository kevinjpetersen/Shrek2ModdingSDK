using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager
{
    public class Shrek2ModListItem
    {
        public string Title { get; set; }
        public string Description { get; set; }
        public string FileName { get; set; }
        public ModTypes ModType { get; set; }
        public bool IsActive { get; set; }
        public string UUID { get; set; }

        public enum ModTypes
        {
            ModFile, ModZip
        }

        public Shrek2ModListItem(string title, ModTypes modType, bool isActive, string uuid, string description = "No description found.")
        {
            Title = title;
            FileName = $"{uuid}.{(modType == ModTypes.ModFile ? "dll" : "zip")}";
            ModType = modType;
            Description = description;
            IsActive = isActive;
            UUID = uuid;
        }
    }
}
