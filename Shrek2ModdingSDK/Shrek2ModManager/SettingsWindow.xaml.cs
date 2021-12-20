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
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Shrek2ModManager
{
    /// <summary>
    /// Interaction logic for TestWindow.xaml
    /// </summary>
    public partial class SettingsWindow : Window
    {
        public Action? CloseModal { get; set; }

        public Shrek2MMSettings Settings { get; set; }

        public SettingsWindow()
        {
            InitializeComponent();
        }

        public void Init()
        {
            Settings = Shrek2MM.LoadSettings();

            if (Settings == null)
            {
                Settings = new Shrek2MMSettings();
            }

            Settings_GameFolder.Text = Settings.GameFolderPath;
            Settings_DisplayMode.SelectedIndex = Settings.DisplayMode;
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            CloseModal?.Invoke();
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            Settings_ErrorMessage.Text = "";

            Settings.DisplayMode = Settings_DisplayMode.SelectedIndex;
            var saved = Shrek2MM.SaveSettings(Settings);

            if(!saved)
            {
                Settings_ErrorMessage.Text = "Failed to save the Settings. This could be because of Read/write permissions not being given. Ensure these permissions have been given.";
                return;
            }

            CloseModal?.Invoke();
        }

        private void Settings_GameFolder_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            if(e.LeftButton == MouseButtonState.Pressed)
            {
                using (var dialog = new FolderBrowserDialog())
                {
                    DialogResult result = dialog.ShowDialog();
                    if (result == System.Windows.Forms.DialogResult.OK)
                    {
                        var folderName = dialog.SelectedPath;

                        if(File.Exists(System.IO.Path.Combine(folderName, "System", "game.exe")) == false)
                        {
                            System.Windows.MessageBox.Show("The selected folder isn't a correct Shrek 2 Game Folder. Please ensure you've selected the root folder of your Shrek 2 installation (This should contain folders like System, Maps, etc.)");
                            return;
                        }

                        Settings.GameFolderPath = folderName;
                        Settings_GameFolder.Text = folderName;
                    }
                }
            }
        }
    }
}
