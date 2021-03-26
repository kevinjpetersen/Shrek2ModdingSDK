using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;
using Shrek2ModManager.Utils;

namespace Shrek2ModManager
{
    /// <summary>
    /// Interaction logic for ManageModsWindow.xaml
    /// </summary>
    public partial class ManageModsWindow : Window
    {
        public List<Mod> Mods { get; set; }
        public List<Mod> InstalledMods { get; set; }

        public Mod SelectedMod { get; set; }

        public ManageModsWindow(List<Mod> mods)
        {
            InitializeComponent();
            Mods = mods;
        }

        private void Window_Loaded(object sender, RoutedEventArgs rea)
        {
            InstalledMods = Mod.GetInstalledMods(Mods);

            foreach(var mod in InstalledMods)
            {
                InstalledModsList.Items.Add(new ListViewItem()
                {
                    Content = mod.Name,
                    BorderThickness = new Thickness(0, 0, 0, 1), 
                    BorderBrush = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White),
                    Name = mod.ModGUID.Replace("-", "")
                });
            }
        }

        private void InstalledModsList_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            var item = e.Source as ListViewItem;
            if (item != null && item.IsSelected)
            {
                SelectedMod = InstalledMods.FirstOrDefault(p => p.ModGUID.Replace("-", "") == item.Name);

                if(SelectedMod != null)
                {
                    DefaultText.Visibility = Visibility.Collapsed;
                    SelectedModName.Text = SelectedMod.Name;
                    SelectedModInfo.Visibility = Visibility.Visible;

                    var configable = SH2WorkshopFileHandler.IsModConfigable(SelectedMod.ModGUID);
                    if(configable)
                    {
                        ConfigFields.Visibility = Visibility.Visible;
                    } else
                    {
                        ConfigFields.Visibility = Visibility.Collapsed;
                    }
                }
            }
        }
    }
}
