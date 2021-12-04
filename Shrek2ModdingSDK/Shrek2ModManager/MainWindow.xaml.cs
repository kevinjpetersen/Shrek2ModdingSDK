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
        public RemoveModWindow? RemoveModWindow { get; set; }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void Window_Initialized(object sender, EventArgs e)
        {
            RemoveModWindow = new RemoveModWindow
            {
                CloseModal = () =>
                {
                    DialogHost.Close(null);
                }
            };

            var mods = Shrek2MM.LoadMods();
            if(mods == null)
            {
                MessageBox.Show("Failed to load Added Mods correctly, this might indicate that the JSON file is corrupted or damaged! Please close this application and ensure the JSON file isn't damaged in any way before proceeding.");
                Add_Mod_Button.IsEnabled = false;
                Play_Button.IsEnabled = false;
                ModItemsList.ItemsSource = ModItems;
                return;
            }

            mods.ForEach(mod => ModItems.Add(mod));

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

            if(RemoveModWindow == null) return;

            RemoveModWindow.SetModTitle(modItem.Title);
            RemoveModWindow.RemovedMod = () =>
            {
                ModItems.Remove(modItem);
                var saved = Shrek2MM.SaveMods(ModItems.ToList());
                if (saved == false) MessageBox.Show("Failed to update mod list, this can be becaues of read/write permissions.");
            };

            DialogHost.Show(RemoveModWindow.Content);
        }

        private void Specific_Mod_ToggleIsActive_Click(object sender, RoutedEventArgs e)
        {
            var tag = ((CheckBox)sender).Tag.ToString();
            var modItem = ModItems.First(p => p.UUID == tag);

            var saved = Shrek2MM.SaveMods(ModItems.ToList());
            if (saved == false) MessageBox.Show("Failed to update mod list, this can be becaues of read/write permissions.");
        }
    }
}
