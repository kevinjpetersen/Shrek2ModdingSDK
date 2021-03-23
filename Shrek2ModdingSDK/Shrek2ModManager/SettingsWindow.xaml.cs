using Microsoft.Win32;
using Shrek2ModManager.Utils;
using System;
using System.Collections.Generic;
using System.IO;
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
    /// Interaction logic for SettingsWindow.xaml
    /// </summary>
    public partial class SettingsWindow : Window
    {
        private Settings NewSettings;

        public SettingsWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            NewSettings = new Settings();
            NewSettings.GameExeLocation = MainWindow.Settings.GameExeLocation;
            NewSettings.Language = MainWindow.Settings.Language;
            NewSettings.WindowMode = MainWindow.Settings.WindowMode;

            if (string.IsNullOrWhiteSpace(MainWindow.Settings.GameExeLocation) == false)
            {
                Settings_GameFolder.Text = MainWindow.Settings.GameExeLocation;
            }

            Settings_Language.SelectedIndex = MainWindow.Settings.Language == Settings.Languages.English ? 0 : 1;
            Settings_WindowModes.SelectedIndex = MainWindow.Settings.WindowMode == Settings.WindowModes.Fullscreen ? 0 : 1;

            Button_PickGameFolder.Click += Button_PickGameFolder_Click;
            Button_SaveSettings.Click += Button_SaveSettings_Click;
        }

        private void Button_SaveSettings_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(Settings_GameFolder.Text)) return;
            if (File.Exists(Settings_GameFolder.Text) == false) return;

            NewSettings.Language = Settings_Language.SelectedIndex == 0 ? Settings.Languages.English : Settings.Languages.Russian;
            NewSettings.WindowMode = Settings_WindowModes.SelectedIndex == 0 ? Settings.WindowModes.Fullscreen : Settings.WindowModes.WindowMode;

            var saved = SH2WorkshopFileHandler.SaveSettings(NewSettings);
            if (saved)
            {
                MainWindow.Settings = NewSettings;
                Close();
            }
        }

        private void Button_PickGameFolder_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog()
            {
                Filter = "Shrek 2 (game.exe)|game.exe"
            };
            if (openFileDialog.ShowDialog() == true)
            {
                if (string.IsNullOrWhiteSpace(openFileDialog.FileName) == false)
                {
                    if (System.IO.Path.GetFileName(openFileDialog.FileName) != "game.exe")
                    {
                        MessageBox.Show("The located file doesn't look like 'game.exe'!");
                        return;
                    }

                    NewSettings.GameExeLocation = openFileDialog.FileName;
                    Settings_GameFolder.Text = openFileDialog.FileName;
                }
            }
        }
    }
}
