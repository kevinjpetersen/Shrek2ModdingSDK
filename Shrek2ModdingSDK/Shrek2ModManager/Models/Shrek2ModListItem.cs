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
        public string Title { get; }
        public string Description { get; }
        public string DllName { get; set; }

        // Used to determine whether to load the mod or not
        public bool IsActive { get; set; }

        public string UUID { get; set; }

        public Shrek2ModListItem(string title, string description = "No description found.")
        {
            Title = title;
            DllName = $"{title.Replace(" ", "")}.dll";
            Description = description;
            UUID = Guid.NewGuid().ToString();
        }
    }
}
