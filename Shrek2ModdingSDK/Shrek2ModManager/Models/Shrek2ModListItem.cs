using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager
{
    public class Shrek2ModListItem
    {
        public bool IsChecked { get; set; }
        public string Title { get; }
        public string Description { get; }
        public string UUID { get; set; }

        public Shrek2ModListItem(string title, string description = "No description found.")
        {
            Title = title;
            Description = description;
            UUID = Guid.NewGuid().ToString();
        }
    }
}
