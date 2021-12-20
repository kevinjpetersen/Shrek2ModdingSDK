using MaterialDesignThemes.Wpf;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
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
        public EditModWindow? EditModWindow { get; set; }
        public SettingsWindow? SettingsWindow { get; set; }

        public Process GameProcess { get; set; }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            Application.Current.Shutdown();
        }

        private async void Window_Initialized(object sender, EventArgs e)
        {
            RemoveModWindow = new RemoveModWindow
            {
                CloseModal = () =>
                {
                    DialogHost.Close(null);
                }
            };

            EditModWindow = new EditModWindow
            {
                CloseModal = () =>
                {
                    DialogHost.Close(null);
                }
            };

            SettingsWindow = new SettingsWindow
            {
                CloseModal = () =>
                {
                    DialogHost.Close(null);
                }
            };

            var mods = Shrek2MM.LoadMods();
            if (mods == null)
            {
                MessageBox.Show("Failed to load Added Mods correctly, this might indicate that the JSON file is corrupted or damaged! Please close this application and ensure the JSON file isn't damaged in any way before proceeding.");
                Add_Mod_Button.IsEnabled = false;
                Play_Button.IsEnabled = false;
                ModItemsList.ItemsSource = ModItems;
                return;
            }

            var extractedModLoader = await Shrek2MM.ExtractModLoader();
            if (extractedModLoader == false)
            {
                MessageBox.Show("Couldn't extract the Mod Loader which is embedded in the Shrek 2 Mod Manager Program. Please check that the program has permissions to read/write on disk, and if the issue still persists please contact the developer.");
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

            if (EditModWindow == null) return;

            EditModWindow.InitEditMod(modItem);
            EditModWindow.EditedMod = (updatedMod) =>
            {
                if (updatedMod == null) return;

                var modItemsList = ModItems.ToList();

                var index = modItemsList.FindIndex(p => p.UUID == updatedMod.UUID);
                modItemsList[index] = updatedMod;

                var saved = Shrek2MM.SaveMods(modItemsList);
                if (saved == false) MessageBox.Show("Failed to update mod list, this can be becaues of read/write permissions.");

                ModItems.Clear();
                modItemsList.ForEach(mod => ModItems.Add(mod));
            };

            DialogHost.Show(EditModWindow.Content);
        }

        private void Specific_Mod_Remove_Click(object sender, RoutedEventArgs e)
        {
            var tag = ((Button)sender).Tag.ToString();
            var modItem = ModItems.First(p => p.UUID == tag);

            if (RemoveModWindow == null) return;

            RemoveModWindow.SetModTitle(modItem.Title);
            RemoveModWindow.RemovedMod = () =>
            {
                var deleted = Shrek2MM.DeleteModFromDataFolder(modItem.FileName);

                if (deleted == false) MessageBox.Show("Failed to delete the mod file/zip from Data folder, this can be becaues of read/write permissions. You can delete this file yourself if you go to 'Your PC/My Documents/Shrek 2 Mod Manager/Added mods'.");

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

        private void Add_Mod_Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog ofd = new()
                {
                    Filter = "Shrek 2 Mod File (.dll)|*.dll|Shrek 2 Mod Zip (.zip)|*.zip"
                };
                ofd.ShowDialog();

                if (string.IsNullOrEmpty(ofd.FileName)) return;

                var modTitle = System.IO.Path.GetFileNameWithoutExtension(ofd.FileName);
                var fileName = System.IO.Path.GetFileName(ofd.FileName);
                var extension = System.IO.Path.GetExtension(ofd.FileName);
                var uuid = Guid.NewGuid().ToString();

                var copied = Shrek2MM.CopyModToDataFolder(ofd.FileName, uuid);

                if (copied == false)
                {
                    MessageBox.Show("Couldn't add the selected mod. Please check that the program has permissions to read/write on disk, and if the issue still persists please contact the developer.");
                    return;
                }

                ModItems.Add(new Shrek2ModListItem(
                    modTitle,
                    extension == ".dll" ? Shrek2ModListItem.ModTypes.ModFile : Shrek2ModListItem.ModTypes.ModZip,
                    true,
                    uuid
                ));

                if (Shrek2MM.SaveMods(ModItems.ToList()) == false)
                {
                    MessageBox.Show("Failed to save the selected mod you wanted to add. We correctly copied the mod data but we couldn't save the metadata. Please check that the program has permissions to read/write on disk, and if the issue still persists please contact the developer.");
                    return;
                }
            }
            catch (Exception ex)
            {
                Shrek2Utils.LogError(ex);
                MessageBox.Show("Error occured when trying to add a mod. For more details check the Error Log in 'This PC/My Documents/Shrek 2 Mod Manager'.");
            }
        }

        private void Settings_Button_Click(object sender, RoutedEventArgs e)
        {
            if (SettingsWindow == null) return;
            SettingsWindow.Init();
            DialogHost.Show(SettingsWindow.Content);
        }

        private void Play_Mods_Click(object sender, RoutedEventArgs e)
        {
            var settings = Shrek2MM.LoadSettings();

            if (settings == null || string.IsNullOrWhiteSpace(settings.GameFolderPath))
            {
                MessageBox.Show("Unable to 'Play' yet as you have not set up Settings correctly yet. Please ensure your Game Folder is selected before proceeding!");
                return;
            }

            if (ModItems == null || ModItems.Count <= 0)
            {
                MessageBox.Show("You currently have no added mods in the Shrek 2 Mod Manager so you cannot 'Play' yet.");
                return;
            }

            if (ModItems.Any(p => p.IsActive) == false)
            {
                MessageBox.Show("You have no Enabled Mods in the Shrek 2 Mod Manager. Ensure atleast 1 mod is enabled before proceeding.");
                return;
            }

            var installed = Shrek2MM.InstallModLoader(settings.GameFolderPath);

            if (installed == false)
            {
                MessageBox.Show("Failed to install Mod Loader into the selected Game Folder you chose in Settings. This could be a Read/write Permission issue. Check the error_log in 'Documents/Shrek 2 Mod Manager' for more details.");
                return;
            }

            if (Shrek2MM.ReinstallMods(settings.GameFolderPath, ModItems.Where(p => p.IsActive).ToList()) == false)
            {
                MessageBox.Show("Failed to install the enabled mods. This could be a Read/write Permission issue. Check the error_log in 'Documents/Shrek 2 Mod Manager' for more details.");
                return;
            }

            if (Shrek2MM.UpdateDefUserFile(settings.GameFolderPath, ModItems.Where(p => p.IsActive).ToList()) == false)
            {
                MessageBox.Show("Failed to update DefUser.ini file, this could be a Read/write Permission issue. Check the error_log in 'Documents/Shrek 2 Mod Manager' for more details.");
                return;
            }



            GameProcess = Process.Start(Shrek2Utils.GetModdedGameExeFilePath(settings.GameFolderPath), settings.DisplayMode == 0 ? "-windowed" : "");
            GameProcess.EnableRaisingEvents = true;

            Play_Button.IsEnabled = false;
            Play_Button.Content = "Running";

            GameProcess.Exited += (sender, e) =>
            {
                Dispatcher.Invoke(() =>
                {
                    Play_Button.IsEnabled = true;
                    Play_Button.Content = "Play";
                });
            };
        }
    }
}
