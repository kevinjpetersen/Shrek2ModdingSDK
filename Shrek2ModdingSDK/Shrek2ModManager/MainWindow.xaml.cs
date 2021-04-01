using MaterialDesignThemes.Wpf;
using Shrek2ModManager.Utils;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
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
        public ModWindow ModWindow { get; set; }
        public SettingsWindow SettingsWindow { get; set; }
        public ManageModsWindow ManageModsWindow { get; set; }

        public List<Mod> Mods { get; set; } = new List<Mod>();

        public static Settings Settings { get; set; }

        public int CurrentPage { get; set; } = 0;
        public bool IsDownloading { get; set; } = false;

        public List<Mod> InstalledMods { get; set; }

        public Mod SelectedMod { get; set; }
        public Shrek2Config LoadedConfig { get; set; }
        public Dictionary<string, string> LoadedBinds { get; set; }
        public int ManageMods_CurrentSettingType { get; set; }

        public static List<string> AvailableBinds = new List<string>()
        {
            "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
        };

        public bool UnsavedChangesDialogOpened { get; set; } = false;

        public enum FieldTypes
        {
            Unknown, String, Bool, Int, Long, Float, Double, Decimal
        }

        ResponsiveManager RM;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if(RM != null) RM.Handle();
        }

        private void Card_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            MaterialDesignThemes.Wpf.Card btn = sender as MaterialDesignThemes.Wpf.Card;
            var dataObject = btn.DataContext as Mod.VisualMod;

            if (ModWindow != null)
            {
                ModWindow.Close();
            }

            ModWindow = new ModWindow(dataObject.Mod, RefreshMods);
            ModWindow.Closed += (a, b) => ModWindow = null;
            ModWindow.Show();
        }

        private async void InstallButton_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            var dataObject = btn.DataContext as Mod.VisualMod;

            if (IsDownloading) return;

            var Mod = dataObject.Mod;

            if (SH2WorkshopFileHandler.IsModInstalled(Mod.ModGUID))
            {
                if (dataObject.UpdateAvailable)
                {
                    if (string.IsNullOrWhiteSpace(Settings.GameFolderLocation))
                    {
                        MessageBox.Show("You have not setup the Shrek 2 Game.exe in the Settings! You need to set it up before you can play mods directly!");
                        return;
                    }

                    IsDownloading = true;
                    var Downloaded = await SH2WorkshopFileHandler.UpdateMod(Mod, (s, p) =>
                    {
                        btn.Content = $"{p.ProgressPercentage}%";
                    });

                    if (Downloaded)
                    {
                        SH2WorkshopFileHandler.ExtractModFile(Mod.ModGUID);
                        if (SH2WorkshopFileHandler.IsModInstalled(Mod.ModGUID))
                        {
                            Downloaded = true;
                        }
                    }
                    else
                    {
                        MessageBox.Show($"Failed to download '{Mod.Name}'. Try again later!");
                    }

                    SH2WorkshopFileHandler.HandleDefUserChanges();
                    RefreshMods();
                    IsDownloading = false;
                }
                else
                {
                    if (string.IsNullOrWhiteSpace(Settings.GameFolderLocation))
                    {
                        MessageBox.Show("You have not setup the Shrek 2 Game.exe in the Settings! You need to set it up before you can play mods directly!");
                        return;
                    }

                    bool uninstalled = SH2WorkshopFileHandler.UninstallMod(Mod);
                    if (uninstalled)
                    {
                        SH2WorkshopFileHandler.HandleDefUserChanges();
                        RefreshMods();
                    }
                    IsDownloading = false;
                }
            }
            else
            {
                // Update Mod
                IsDownloading = true;
                var Downloaded = await SH2WorkshopFileHandler.DownloadMod(Mod, (s, p) =>
                {
                    btn.Content = $"{p.ProgressPercentage}%";
                });

                if (Downloaded)
                {
                    SH2WorkshopFileHandler.ExtractModFile(Mod.ModGUID);
                    if (SH2WorkshopFileHandler.IsModInstalled(Mod.ModGUID))
                    {
                        Downloaded = true;
                    }
                }
                else
                {
                    MessageBox.Show($"Failed to update '{Mod.Name}'. Try again later!");
                }

                SH2WorkshopFileHandler.HandleDefUserChanges();
                RefreshMods();
                IsDownloading = false;
            }
        }

        public void RefreshMods()
        {
            if (CurrentPage == 0)
            {
                Mods = Mod.GetMods();
                OverviewModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods.Take(4).ToList());
            }
            else if (CurrentPage == 1)
            {
                Mods = Mod.GetMods();
                AllModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods);
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            Application.Current.Shutdown();
        }

        private void Window_Loaded(object sender, RoutedEventArgs rea)
        {
            RM = new ResponsiveManager(this);
            RM.Handle();

            ManageModsDialog.DialogClosing += (s, e) =>
            {
                if (UnsavedChangesDialogOpened)
                {
                    e.Cancel();
                    return;
                }
                UnsavedChangesDialogOpened = true;

                if(ManageMods_CurrentSettingType == 0)
                {
                    var changes = ConfigChanges();
                    if (changes == 1 || changes == 2)
                    {

                        MessageBoxResult dialogResult = MessageBox.Show("You have some unsaved 'Mod Settings' changes. Would you like to save them?", "Unsaved changes", MessageBoxButton.YesNo, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                        if (dialogResult == MessageBoxResult.Yes)
                        {
                            if(changes == 2) e.Cancel();
                            ConfigSaveButton_Click(null, null);
                        }
                    }
                    UnsavedChangesDialogOpened = false;
                }
                else if(ManageMods_CurrentSettingType == 1)
                {
                    var changes = BindChanges();
                    if (changes == 1 || changes == 2)
                    {

                        MessageBoxResult dialogResult = MessageBox.Show("You have some unsaved 'Mod Binds' changes. Would you like to save them?", "Unsaved changes", MessageBoxButton.YesNo, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                        if (dialogResult == MessageBoxResult.Yes)
                        {
                            if (changes == 2) e.Cancel();
                            ConfigSaveButton_Click(null, null);
                        }
                    }
                    UnsavedChangesDialogOpened = false;
                } else
                {
                    UnsavedChangesDialogOpened = false;
                }
            };

            Nav_Button_Overview.Click += (s, e) => SelectNavItem(0);
            Nav_Button_Mods.Click += (s, e) => SelectNavItem(1);

            Nav_Button_Settings.Click += Nav_Button_Settings_Click;

            Overview_Button_PlayGame.MouseEnter += Overview_Button_PlayGame_MouseEnter;
            Overview_Button_PlayGame.MouseLeave += Overview_Button_PlayGame_MouseLeave;
            Overview_Button_ManageMods.MouseEnter += Overview_Button_ManageMods_MouseEnter;
            Overview_Button_ManageMods.MouseLeave += Overview_Button_ManageMods_MouseLeave;

            Overview_Button_PlayGame.MouseUp += Overview_Button_PlayGame_MouseUp;
            Overview_Button_ManageMods.MouseUp += Overview_Button_ManageMods_MouseUp;

            Settings = SH2WorkshopFileHandler.GetSettings();

            if (SH2WorkshopFileHandler.IsInternalModFilesInstalled())
            {
                Overview_Button_PlayGame_Text.Text = "Play Shrek 2 Modded";
            }
            else
            {
                Overview_Button_PlayGame_Text.Text = "Install Shrek 2 Modded";
            }

            Mods = Mod.GetMods();
            OverviewModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods.Take(4).ToList());
        }

        private async void Overview_Button_ManageMods_MouseUp(object sender, MouseButtonEventArgs e)
        {
            UnsavedChangesDialogOpened = false;
            LoadedConfig = null;
            SelectedMod = null;
            ErrorMessage.Text = "";
            SelectedModNoConfig.Visibility = Visibility.Collapsed;
            ManageMods_CurrentSettingType = -1;

            DefaultText.Visibility = Visibility.Visible;
            SelectedModName.Text = "";
            SelectedModInfo.Visibility = Visibility.Collapsed;

            ConfigFields_Items.Children.Clear();

            InstalledMods = Mod.GetInstalledMods(Mods);

            InstalledModsList.Items.Clear();
            foreach (var mod in InstalledMods)
            {
                InstalledModsList.Items.Add(new ListViewItem()
                {
                    Content = mod.Name,
                    BorderThickness = new Thickness(0, 0, 0, 1),
                    BorderBrush = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White),
                    Name = mod.ModGUID.Replace("-", "")
                });
            }

            await ManageModsDialog.ShowDialog(null);
            

            //if (ManageModsWindow != null)
            //{
            //    ManageModsWindow.Focus();
            //    return;
            //}

            //ManageModsWindow = new ManageModsWindow(Mods);
            //ManageModsWindow.Closed += (a, b) =>
            //{
            //    ManageModsWindow = null;
            //};
            //ManageModsWindow.Show();
        }

        private async void Overview_Button_PlayGame_MouseUp(object sender, MouseButtonEventArgs e)
        {
            try
            {
                if (string.IsNullOrWhiteSpace(Settings.GameFolderLocation))
                {
                    MessageBox.Show("You have not setup the Shrek 2 Game.exe in the Settings! You need to set it up before you can play mods directly!");
                    return;
                }

                if (SH2WorkshopFileHandler.IsInternalModFilesInstalled())
                {
                    Process.Start(System.IO.Path.Combine(Settings.GameFolderLocation, "Shrek 2 Modded.exe"), Settings.WindowMode == Settings.WindowModes.WindowMode ? "-windowed" : "");
                }
                else
                {
                    Overview_Button_PlayGame_Text.Text = "Downloading..";
                    bool downloaded = await SH2WorkshopFileHandler.DownloadInternalModFiles((ea, ex) =>
                    {

                    });

                    if (downloaded)
                    {
                        Overview_Button_PlayGame_Text.Text = "Installing..";

                        bool installed = SH2WorkshopFileHandler.ExtractInternalModFiles();
                        if (installed)
                        {
                            Overview_Button_PlayGame_Text.Text = "Play Shrek 2 Modded";
                            return;
                        }
                    }
                    Overview_Button_PlayGame_Text.Text = "Failed to install. Try again!";
                }

            }
            catch
            {

            }
        }

        private void Nav_Button_Settings_Click(object sender, RoutedEventArgs e)
        {
            if (SettingsWindow != null)
            {
                SettingsWindow.Focus();
                return;
            }

            SettingsWindow = new SettingsWindow();
            SettingsWindow.Closed += (a, b) =>
            {
                SettingsWindow = null;
                // TODO: Refresh all Language stuff
            };
            SettingsWindow.Show();
        }

        private void Overview_Button_ManageMods_MouseLeave(object sender, MouseEventArgs e)
        {
            Overview_Button_ManageMods.Opacity = 1;
        }

        private void Overview_Button_ManageMods_MouseEnter(object sender, MouseEventArgs e)
        {
            Overview_Button_ManageMods.Opacity = 0.8;
        }

        private void Overview_Button_PlayGame_MouseLeave(object sender, MouseEventArgs e)
        {
            Overview_Button_PlayGame.Opacity = 1;
        }

        private void Overview_Button_PlayGame_MouseEnter(object sender, MouseEventArgs e)
        {
            Overview_Button_PlayGame.Opacity = 0.8;
        }

        private void SelectNavItem(int item)
        {
            if (item == 0)
            {
                CurrentPage = 0;
                Nav_Button_Overview.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);
                Nav_Button_Mods.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Normal);

                Content_Panel_Overview.Visibility = Visibility.Visible;
                Content_Panel_Mods.Visibility = Visibility.Collapsed;

                Mods = Mod.GetMods();
                OverviewModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods.Take(4).ToList());
            }
            else if (item == 1)
            {
                Mods_Search_Sorting.SelectedIndex = 0;
                Mods_Search_Text.Text = "";
                CurrentPage = 1;
                Nav_Button_Overview.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Normal);
                Nav_Button_Mods.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);

                Content_Panel_Overview.Visibility = Visibility.Collapsed;
                Content_Panel_Mods.Visibility = Visibility.Visible;

                Mods = Mod.GetMods();
                AllModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods);
            }
        }

        private void ModItem_MouseEnter(object sender, MouseEventArgs e)
        {
            MaterialDesignThemes.Wpf.Card card = (MaterialDesignThemes.Wpf.Card)sender;
            var ModItem_Panel = FindElementByName<StackPanel>(card, "ModItem_Panel");
            //var ModItem_Name = FindElementByName<TextBlock>(card, "ModItem_Name");
            //var ModItem_Author = FindElementByName<TextBlock>(card, "ModItem_Author");
            //var ModItem_AuthorTick = FindElementByName<Image>(card, "ModItem_AuthorTick");
            //var ModItem_Desc = FindElementByName<TextBlock>(card, "ModItem_Desc");

            ModItem_Panel.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_WhiteIsh);
            //ModItem_Name.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
            //ModItem_Author.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
            //ModItem_AuthorTick.Source = new BitmapImage(new Uri(@"Resources/embed_tick_white.png", UriKind.Relative));
            //ModItem_Desc.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);

        }

        private void ModItem_MouseLeave(object sender, MouseEventArgs e)
        {
            MaterialDesignThemes.Wpf.Card card = (MaterialDesignThemes.Wpf.Card)sender;
            var ModItem_Panel = FindElementByName<StackPanel>(card, "ModItem_Panel");
            //var ModItem_Name = FindElementByName<TextBlock>(card, "ModItem_Name");
            //var ModItem_Author = FindElementByName<TextBlock>(card, "ModItem_Author");
            //var ModItem_AuthorTick = FindElementByName<Image>(card, "ModItem_AuthorTick");
            //var ModItem_Desc = FindElementByName<TextBlock>(card, "ModItem_Desc");

            ModItem_Panel.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
            //ModItem_Name.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black);
            //ModItem_Author.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Green);
            //ModItem_AuthorTick.Source = new BitmapImage(new Uri(@"Resources/embed_tick.png", UriKind.Relative));
            //ModItem_Desc.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black);
        }

        public T FindElementByName<T>(FrameworkElement element, string sChildName) where T : FrameworkElement
        {
            T childElement = null;
            var nChildCount = VisualTreeHelper.GetChildrenCount(element);
            for (int i = 0; i < nChildCount; i++)
            {
                FrameworkElement child = VisualTreeHelper.GetChild(element, i) as FrameworkElement;

                if (child == null)
                    continue;

                if (child is T && child.Name.Equals(sChildName))
                {
                    childElement = (T)child;
                    break;
                }

                childElement = FindElementByName<T>(child, sChildName);

                if (childElement != null)
                    break;
            }
            return childElement;
        }

        /* MANAGE MODS */

        private void ManageModsSelectSetting(int type)
        {
            ManageMods_CurrentSettingType = type;
            if (ManageMods_CurrentSettingType == 0)
            {
                // Settings
                ModSettingsTitle.Text = "Mod Settings";
                ModSettings_SettingsButton.Background = Shrek2Colors.GetBrushFromHex("#65a338");
                ModSettings_BindsButton.Background = Shrek2Colors.GetBrushFromHex("#b7cba8");

                if (SelectedMod != null)
                {
                    DefaultText.Visibility = Visibility.Collapsed;
                    SelectedModName.Text = SelectedMod.Name;
                    SelectedModInfo.Visibility = Visibility.Visible;
                    SelectedModNoConfig.Visibility = Visibility.Collapsed;

                    var configable = SH2WorkshopFileHandler.IsModConfigable(SelectedMod.ModGUID);
                    if (configable)
                    {
                        AddConfigFields();
                        ConfigFields.Visibility = Visibility.Visible;
                    }
                    else
                    {
                        SelectedModNoConfig.Visibility = Visibility.Visible;
                        ConfigFields.Visibility = Visibility.Collapsed;
                    }
                }
            } else if(ManageMods_CurrentSettingType == 1)
            {
                // Binds
                ModSettingsTitle.Text = "Mod Binds";
                ModSettings_SettingsButton.Background = Shrek2Colors.GetBrushFromHex("#b7cba8");
                ModSettings_BindsButton.Background = Shrek2Colors.GetBrushFromHex("#65a338");

                if (SelectedMod != null)
                {
                    DefaultText.Visibility = Visibility.Collapsed;
                    SelectedModName.Text = SelectedMod.Name;
                    SelectedModInfo.Visibility = Visibility.Visible;
                    SelectedModNoConfig.Visibility = Visibility.Collapsed;

                    var bindable = SH2WorkshopFileHandler.IsModBindable(SelectedMod.ModGUID);
                    if (bindable)
                    {
                        AddBindFields();
                        ConfigFields.Visibility = Visibility.Visible;
                    }
                    else
                    {
                        SelectedModNoConfig.Visibility = Visibility.Visible;
                        ConfigFields.Visibility = Visibility.Collapsed;
                    }
                }
            }
        }

        private void InstalledModsList_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            ErrorMessage.Text = "";

            var item = e.Source as ListViewItem;
            if (item != null && item.IsSelected)
            {
                SelectedMod = InstalledMods.FirstOrDefault(p => p.ModGUID.Replace("-", "") == item.Name);
                
                ManageModsSelectSetting(0);
                if (SH2WorkshopFileHandler.IsModBindable(SelectedMod.ModGUID))
                {
                    ModSettings_BindsButton.Visibility = Visibility.Visible;
                } else
                {
                    ModSettings_BindsButton.Visibility = Visibility.Collapsed;
                }
            }
        }

        public void AddBindFields()
        {
            try
            {
                LoadedBinds = Shrek2Binds.GetBinds(SelectedMod);
                if (LoadedBinds == null)
                {
                    ConfigFields.Visibility = Visibility.Collapsed;
                    MessageBox.Show("Failed to load binds from binds.json! The binds file could be incorrectly formatted.");
                    return;
                }

                ConfigFields_Items.Children.Clear();

                if (LoadedBinds == null || LoadedBinds.Count <= 0)
                {
                    ConfigFields.Visibility = Visibility.Collapsed;
                    MessageBox.Show("The loaded mod's binds file has no fields to configure!");
                    return;
                }

                foreach (var field in LoadedBinds)
                {
                    try
                    {
                        AddBindField(field);
                    }
                    catch { }
                }
            }
            catch
            {
                ConfigFields.Visibility = Visibility.Collapsed;
                MessageBox.Show("Failed to load bind fields!");
            }
        }

        public void AddBindField(KeyValuePair<string, string> field)
        {
            var sp = new StackPanel()
            {
                Orientation = Orientation.Vertical,
                Margin = new Thickness(20, 0, 20, 20),
                HorizontalAlignment = HorizontalAlignment.Left,
            };

            sp.Children.Add(new TextBlock()
            {
                FontWeight = FontWeights.Bold,
                Text = field.Key,
                HorizontalAlignment = HorizontalAlignment.Left,
                Margin = new Thickness(0, 0, 0, 0),
                FontSize = 16
            });

            var listBox = new ComboBox()
            {
                Width = 200,
                HorizontalAlignment = HorizontalAlignment.Left,
                DataContext = field.Key
            };

            foreach(var ab in AvailableBinds)
            {
                listBox.Items.Add(ab);
            }
            listBox.SelectedItem = field.Value;

            sp.Children.Add(listBox);

            ConfigFields_Items.Children.Add(sp);
        }

        public void AddConfigFields()
        {
            try
            {
                LoadedConfig = Shrek2Config.GetConfig(SelectedMod);
                if (LoadedConfig == null)
                {
                    ConfigFields.Visibility = Visibility.Collapsed;
                    MessageBox.Show("Failed to load config fields from config.json! The config file could be incorrectly formatted.");
                    return;
                }

                ConfigFields_Items.Children.Clear();

                if (LoadedConfig.Config == null || LoadedConfig.Config.Count <= 0)
                {
                    ConfigFields.Visibility = Visibility.Collapsed;
                    MessageBox.Show("The loaded mod's config file has no fields to configure!");
                    return;
                }

                foreach (var field in LoadedConfig.Config)
                {
                    try
                    {
                        AddConfigField(field);
                    }
                    catch { }
                }
            }
            catch
            {
                ConfigFields.Visibility = Visibility.Collapsed;
                MessageBox.Show("Failed to load config fields!");
            }
        }

        public void AddConfigField(KeyValuePair<string, object> field)
        {
            var fieldType = GetFieldType(field.Value);

            var sp = new StackPanel()
            {
                Orientation = Orientation.Vertical,
                Margin = new Thickness(20, 0, 20, 20),
                HorizontalAlignment = HorizontalAlignment.Left,
            };

            sp.Children.Add(new TextBlock()
            {
                FontWeight = FontWeights.Bold,
                Text = field.Key,
                HorizontalAlignment = HorizontalAlignment.Left,
                Margin = new Thickness(0, 0, 0, 0),
                FontSize = 16
            });

            if (LoadedConfig.Docs.ContainsKey(field.Key))
            {
                sp.Children.Add(new TextBlock()
                {
                    FontWeight = FontWeights.Normal,
                    FontSize = 13,
                    Text = LoadedConfig.Docs[field.Key],
                    HorizontalAlignment = HorizontalAlignment.Left,
                    Margin = new Thickness(0, 0, 0, 5),
                    TextWrapping = TextWrapping.Wrap
                });
            }

            if (fieldType == FieldTypes.String || fieldType == FieldTypes.Int || fieldType == FieldTypes.Float || fieldType == FieldTypes.Long || fieldType == FieldTypes.Double || fieldType == FieldTypes.Decimal)
            {
                sp.Children.Add(new TextBox()
                {
                    Text = field.Value.ToString(),
                    Width = 200,
                    HorizontalAlignment = HorizontalAlignment.Left,
                    DataContext = field.Key
                });
            }

            if (fieldType == FieldTypes.Bool)
            {
                sp.Children.Add(new CheckBox()
                {
                    IsChecked = (bool)field.Value,
                    HorizontalAlignment = HorizontalAlignment.Left,
                    DataContext = field.Key
                });
            }

            ConfigFields_Items.Children.Add(sp);
        }

        private void ConfigDiscardButton_Click(object sender, RoutedEventArgs e)
        {
            if (ManageModsDialog == null || ManageModsDialog.CurrentSession == null) return;
            if (ManageModsDialog.CurrentSession.IsEnded) return;
            ManageModsDialog.CurrentSession.Close();
        }

        private int BindChanges()
        {
            try
            {
                if (LoadedBinds == null || LoadedBinds.Count <= 0) return 0;

                foreach (var field in LoadedBinds)
                {
                    var fieldItem = FindElementByDataContext<ComboBox>(ConfigFields_Items, field.Key);
                    if (field.Value != fieldItem.Text) return 1;
                }

                return 0;
            }
            catch
            {
                return 2;
            }
        }

        private int ConfigChanges()
        {
            try
            {
                if (LoadedConfig == null || LoadedConfig.Config == null || LoadedConfig.Config.Count <= 0) return 0;

                foreach (var field in LoadedConfig.Config)
                {
                    var fieldType = GetFieldType(field.Value);

                    if (fieldType == FieldTypes.String)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        if (LoadedConfig.Config[field.Key].ToString() != fieldItem.Text) return 1;
                    }
                    else if (fieldType == FieldTypes.Int)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        if (int.TryParse(fieldItem.Text, out int num))
                        {
                            if ((int)LoadedConfig.Config[field.Key] != num) return 1;
                        }
                        else
                        {
                            return 2;
                        }
                    }
                    else if (fieldType == FieldTypes.Float)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        if (float.TryParse(fieldItem.Text, out float num))
                        {
                            if ((float)LoadedConfig.Config[field.Key] != num) return 1;
                        }
                        else
                        {
                            return 2;
                        }
                    }
                    else if (fieldType == FieldTypes.Long)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        if (long.TryParse(fieldItem.Text, out long num))
                        {
                            if ((long)LoadedConfig.Config[field.Key] != num) return 1;
                        }
                        else
                        {
                            return 2;
                        }
                    }
                    else if (fieldType == FieldTypes.Double)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        if (double.TryParse(fieldItem.Text, out double num))
                        {
                            if ((double)LoadedConfig.Config[field.Key] != num) return 1;
                        }
                        else
                        {
                            return 2;
                        }
                    }
                    else if (fieldType == FieldTypes.Decimal)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        if (decimal.TryParse(fieldItem.Text, out decimal num))
                        {
                            if ((decimal)LoadedConfig.Config[field.Key] != num) return 1;
                        }
                        else
                        {
                            return 2;
                        }
                    }
                    else if (fieldType == FieldTypes.Bool)
                    {
                        var fieldItem = FindElementByDataContext<CheckBox>(ConfigFields_Items, field.Key);
                        if ((bool)LoadedConfig.Config[field.Key] != fieldItem.IsChecked) return 1;
                    }
                }

                return 0;
            }
            catch
            {
                return 2;
            }
        }

        private void SaveConfig()
        {
            try
            {
                ErrorMessage.Text = "";
                var configFields = new Dictionary<string, object>();

                foreach (var field in LoadedConfig.Config)
                {
                    var fieldType = GetFieldType(field.Value);

                    if (fieldType == FieldTypes.String)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        configFields.Add(field.Key, fieldItem.Text);
                    }
                    else if (fieldType == FieldTypes.Int)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        if (int.TryParse(fieldItem.Text, out int num))
                        {
                            configFields.Add(field.Key, num);
                        }
                        else
                        {
                            ErrorMessage.Text = $"The setting '{field.Key}' can only be a number!";
                            MessageBox.Show($"The setting '{field.Key}' can only be a number!");
                            return;
                        }
                    }
                    else if (fieldType == FieldTypes.Float || fieldType == FieldTypes.Long || fieldType == FieldTypes.Decimal || fieldType == FieldTypes.Double)
                    {
                        var fieldItem = FindElementByDataContext<TextBox>(ConfigFields_Items, field.Key);
                        if (float.TryParse(fieldItem.Text, out float num))
                        {
                            configFields.Add(field.Key, num);
                        }
                        else
                        {
                            ErrorMessage.Text = $"The setting '{field.Key}' can only be a decimal number!";
                            MessageBox.Show($"The setting '{field.Key}' can only be a decimal number!");
                            return;
                        }
                    }
                    else if (fieldType == FieldTypes.Bool)
                    {
                        var fieldItem = FindElementByDataContext<CheckBox>(ConfigFields_Items, field.Key);
                        configFields.Add(field.Key, fieldItem.IsChecked);
                    }
                }

                LoadedConfig.Config = configFields;
                LoadedConfig.SaveConfig(SelectedMod);
                ErrorMessage.Text = "Successfully saved changes!";
            }
            catch
            {
                ErrorMessage.Text = "Failed to save changes to config!";
                MessageBox.Show("Failed to save changes to config!");
            }
        }

        private void SaveBinds()
        {
            try
            {
                ErrorMessage.Text = "";
                var configFields = new Dictionary<string, string>();

                foreach (var field in LoadedBinds)
                {
                    var fieldItem = FindElementByDataContext<ComboBox>(ConfigFields_Items, field.Key);
                    configFields.Add(field.Key, fieldItem.SelectedItem.ToString());
                }

                LoadedBinds = configFields;
                Shrek2Binds.SaveBinds(SelectedMod, LoadedBinds);
                ErrorMessage.Text = "Successfully saved changes!";
            }
            catch
            {
                ErrorMessage.Text = "Failed to save changes to config!";
                MessageBox.Show("Failed to save changes to config!");
            }
        }

        private void ConfigSaveButton_Click(object sender, RoutedEventArgs e)
        {
            if(ManageMods_CurrentSettingType == 0)
            {
                SaveConfig();
            } else if(ManageMods_CurrentSettingType == 1)
            {
                SaveBinds();
            }
        }

        public FieldTypes GetFieldType(object fieldObject)
        {
            if (fieldObject is bool) return FieldTypes.Bool;
            if (fieldObject is float) return FieldTypes.Float;
            if (fieldObject is long) return FieldTypes.Long;
            if (fieldObject is double) return FieldTypes.Double;
            if (fieldObject is decimal) return FieldTypes.Decimal;
            if (fieldObject is string) return FieldTypes.String;
            if (fieldObject is int) return FieldTypes.Int;
            return FieldTypes.Unknown;
        }

        public T FindElementByDataContext<T>(FrameworkElement element, string sChildName) where T : FrameworkElement
        {
            T childElement = null;
            var nChildCount = VisualTreeHelper.GetChildrenCount(element);
            for (int i = 0; i < nChildCount; i++)
            {
                FrameworkElement child = VisualTreeHelper.GetChild(element, i) as FrameworkElement;

                if (child == null)
                    continue;

                if (child is T && child.DataContext.Equals(sChildName))
                {
                    childElement = (T)child;
                    break;
                }

                childElement = FindElementByDataContext<T>(child, sChildName);

                if (childElement != null)
                    break;
            }
            return childElement;
        }

        private void Mods_Search_Text_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Mods == null || Mods.Count <= 0) return;

            var items = Mods.Where(p => p.Name.ToLower().Contains(Mods_Search_Text.Text.ToLower())).OrderByDescending(p => p.ID).ToList();

            if (Mods_Search_Sorting.SelectedIndex == 0)
            {
                AllModsList.ItemsSource = Mod.VisualMod.ToVisualMods(items.OrderByDescending(p => p.ID).ToList());
            }
            else if (Mods_Search_Sorting.SelectedIndex == 1)
            {
                AllModsList.ItemsSource = Mod.VisualMod.ToVisualMods(items.OrderByDescending(p => p.Modified).ToList());
            }
        }

        private void Mods_Search_Sorting_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (Mods == null || Mods.Count <= 0) return;

            if(Mods_Search_Sorting.SelectedIndex == 0)
            {
                AllModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods.OrderByDescending(p => p.ID).ToList());
            }
            else if(Mods_Search_Sorting.SelectedIndex == 1)
            {
                AllModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods.OrderByDescending(p => p.Modified).ToList());
            }
        }

        private void ModSettings_SettingsButton_Click(object sender, RoutedEventArgs e)
        {
            ManageModsSelectSetting(0);
        }

        private void ModSettings_BindsButton_Click(object sender, RoutedEventArgs e)
        {
            ManageModsSelectSetting(1);
        }
    }
}
