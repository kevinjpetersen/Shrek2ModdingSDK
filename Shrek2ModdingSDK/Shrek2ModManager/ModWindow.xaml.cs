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

        public ModWindow(Mod mod)
        {
            InitializeComponent();
            this.Mod = mod;
            Title = $"{Mod.Name} | By {Mod.Author}";
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Map_Title.Text = Mod.Name;
            Map_Author.Text = $"By {Mod.Author}";
            Map_Desc.Text = Mod.Description;
            Map_Verified.Visibility = Mod.Verified ? Visibility.Visible : Visibility.Hidden;
            IsDownloading = false;
            HandleMapStatus();
        }

        private void HandleMapStatus()
        {
            Button_DownloadPlayMap.Click += Button_DownloadPlayMap_Click;

            if (SH2WorkshopFileHandler.IsModInstalled(Mod.InternalName))
            {
                Downloaded = true;
                Button_DownloadPlayMap.Content = "Uninstall Mod";
                return;
            }
            Downloaded = false;
            Button_DownloadPlayMap.Content = "Install Mod";
        }

        private async void Button_DownloadPlayMap_Click(object sender, RoutedEventArgs e)
        {
            if (IsDownloading) return;

            if (Downloaded)
            {
                if (string.IsNullOrWhiteSpace(MainWindow.Settings.GameFolderLocation))
                {
                    MessageBox.Show("You have not setup the Shrek 2 Game.exe in the Settings! You need to set it up before you can play mods directly!");
                    return;
                }

                bool uninstalled = SH2WorkshopFileHandler.UninstallMod(Mod.InternalName);
                if(uninstalled)
                {
                    SH2WorkshopFileHandler.HandleDefUserChanges();
                    Button_DownloadPlayMap.Content = "Install Mod";
                    Downloaded = false;
                }
            }
            else
            {
                // Download Mod
                IsDownloading = true;
                Progress_DownloadMap.Value = 0;
                Progress_DownloadMap.Visibility = Visibility.Visible;
                Downloaded = await SH2WorkshopFileHandler.DownloadMod(Mod.InternalName, DownloadProgress);
                if (Downloaded)
                {
                    SH2WorkshopFileHandler.ExtractModFile(Mod.InternalName);
                    if (SH2WorkshopFileHandler.IsModInstalled(Mod.InternalName))
                    {
                        Button_DownloadPlayMap.Content = "Uninstall Mod";
                        Downloaded = true;
                    }
                }

                SH2WorkshopFileHandler.HandleDefUserChanges();
                Progress_DownloadMap.Visibility = Visibility.Hidden;
                IsDownloading = false;
            }
        }

        private void DownloadProgress(object sender, System.Net.DownloadProgressChangedEventArgs args)
        {
            Progress_DownloadMap.Value = args.ProgressPercentage;
        }
    }
}
