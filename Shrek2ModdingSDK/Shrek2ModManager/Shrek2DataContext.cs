using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager
{
    public class Shrek2DataContext
    {
        public ObservableCollection<Shrek2ModListItem> Items { get; } = new ObservableCollection<Shrek2ModListItem>();

        public Shrek2DataContext()
        {
            //for (int i = 1; i < 20; i++)
            //{
            //    Items.Add(new Shrek2ModListItem($"Item {i}"));
            //}


            Items.Add(new Shrek2ModListItem($"Backflip Mod", "This will allow you to backflip when jumping."));
            Items.Add(new Shrek2ModListItem($"Better Ghost Mod", "This adds a better ghosting mechanic."));
            Items.Add(new Shrek2ModListItem($"MasterToolz"));
            Items.Add(new Shrek2ModListItem($"Chaos Mod v2"));
            Items.Add(new Shrek2ModListItem($"Randomizer Mod"));
            Items.Add(new Shrek2ModListItem($"Infinite Coins Mod"));
            Items.Add(new Shrek2ModListItem($"Replay Mod"));
        }
    }
}
