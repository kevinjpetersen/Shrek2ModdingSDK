using MaterialDesignThemes.Wpf;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Shrek2ModManager
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public ObservableCollection<Shrek2ModListItem> ModItems { get; } = new ObservableCollection<Shrek2ModListItem>();
        public RemoveModWindow RemoveModWindow { get; set; }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Initialized(object sender, EventArgs e)
        {
            RemoveModWindow = new RemoveModWindow();
            RemoveModWindow.CloseModal = () =>
            {
                DialogHost.Close(null);
            };

            ModItems.Add(new Shrek2ModListItem($"Backflip Mod", "This will allow you to backflip when jumping."));
            ModItems.Add(new Shrek2ModListItem($"Better Ghost Mod", "This adds a better ghosting mechanic."));
            ModItems.Add(new Shrek2ModListItem($"MasterToolz"));
            ModItems.Add(new Shrek2ModListItem($"Chaos Mod v2"));
            ModItems.Add(new Shrek2ModListItem($"Randomizer Mod"));
            ModItems.Add(new Shrek2ModListItem($"Infinite Coins Mod"));
            ModItems.Add(new Shrek2ModListItem($"Replay Mod"));

            ModItemsList.ItemsSource = ModItems;
        }

        private void Specific_Mod_Settings_Click(object sender, RoutedEventArgs e)
        {
            var tag = ((Button)sender).Tag.ToString();
            var modItem = ModItems.First(p => p.UUID == tag);

            //MessageBox.Show(ModItems.Count(p => p.IsChecked).ToString());

        }

        private void Specific_Mod_Remove_Click(object sender, RoutedEventArgs e)
        {
            var tag = ((Button)sender).Tag.ToString();
            var modItem = ModItems.First(p => p.UUID == tag);

            RemoveModWindow.SetModTitle(modItem.Title);
            RemoveModWindow.RemovedMod = () =>
            {
                ModItems.Remove(modItem);
            };

            DialogHost.Show(RemoveModWindow.Content);
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            Application.Current.Shutdown();
        }

    }
}
