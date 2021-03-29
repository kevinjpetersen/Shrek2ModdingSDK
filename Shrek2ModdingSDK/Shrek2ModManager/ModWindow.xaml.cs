using Shrek2ModManager.Utils;
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

namespace Shrek2ModManager
{
    /// <summary>
    /// Interaction logic for ModWindow.xaml
    /// </summary>
    public partial class ModWindow : Window
    {
        public Mod Mod { get; set; }
        public bool Downloaded { get; set; } = false;
        public bool IsDownloading { get; set; } = false;

        public Action RefreshMods { get; set; }

        public ModWindow(Mod mod, Action refreshMods)
        {
            InitializeComponent();
            this.Mod = mod;
            Title = $"{Mod.Name} | By {Mod.Username}";
            RefreshMods = refreshMods;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Map_Title.Text = Mod.Name;
            Map_Author.Text = $"By {Mod.Username}";
            Map_Desc.Text = Mod.Description;
            Map_Verified.Visibility = Mod.Verified == 1 ? Visibility.Visible : Visibility.Hidden;
            Map_Version.Text = $"Version: {Mod.VersionText} ({Mod.VersionNumber})";
            IsDownloading = false;
        }
    }
}
