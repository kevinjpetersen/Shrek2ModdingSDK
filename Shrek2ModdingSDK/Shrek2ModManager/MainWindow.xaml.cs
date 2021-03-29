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
        public int MapsPageNumber { get; set; }

        public static Settings Settings { get; set; }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Card_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            MaterialDesignThemes.Wpf.Card btn = sender as MaterialDesignThemes.Wpf.Card;
            var dataObject = btn.DataContext as Mod.VisualMod;

            if (ModWindow != null)
            {
                ModWindow.Focus();
                return;
            }

            ModWindow = new ModWindow(dataObject.Mod);
            ModWindow.Closed += (a, b) => ModWindow = null;
            ModWindow.Show();
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            Application.Current.Shutdown();
        }

        private void Window_Loaded(object sender, RoutedEventArgs rea)
        {
            MapsPageNumber = 0;

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

            if(SH2WorkshopFileHandler.IsInternalModFilesInstalled())
            {
                Overview_Button_PlayGame_Text.Text = "Play Shrek 2 Modded";
            } else
            {
                Overview_Button_PlayGame_Text.Text = "Install Shrek 2 Modded";
            }

            Mods = Mod.GetMods();
            OverviewModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods.Take(4).ToList());
        }

        private void Overview_Button_ManageMods_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (ManageModsWindow != null)
            {
                ManageModsWindow.Focus();
                return;
            }

            ManageModsWindow = new ManageModsWindow(Mods);
            ManageModsWindow.Closed += (a, b) =>
            {
                ManageModsWindow = null;
            };
            ManageModsWindow.Show();
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

                if(SH2WorkshopFileHandler.IsInternalModFilesInstalled())
                {
                    Process.Start(System.IO.Path.Combine(Settings.GameFolderLocation, "Shrek 2 Modded.exe"), Settings.WindowMode == Settings.WindowModes.WindowMode ? "-windowed" : "");
                } else
                {
                    Overview_Button_PlayGame_Text.Text = "Downloading..";
                    bool downloaded = await SH2WorkshopFileHandler.DownloadInternalModFiles((ea, ex) =>
                    {

                    });

                    if(downloaded)
                    {
                        Overview_Button_PlayGame_Text.Text = "Installing..";

                        bool installed = SH2WorkshopFileHandler.ExtractInternalModFiles();
                        if(installed)
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
                MapsPageNumber = 0;
                Nav_Button_Overview.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);
                Nav_Button_Mods.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Normal);

                Content_Panel_Overview.Visibility = Visibility.Visible;
                Content_Panel_Mods.Visibility = Visibility.Collapsed;

                Mods = Mod.GetMods();
                OverviewModsList.ItemsSource = Mod.VisualMod.ToVisualMods(Mods.Take(4).ToList());
            }
            else if (item == 1)
            {
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
            var ModItem_Name = FindElementByName<TextBlock>(card, "ModItem_Name");
            var ModItem_Author = FindElementByName<TextBlock>(card, "ModItem_Author");
            var ModItem_AuthorTick = FindElementByName<Image>(card, "ModItem_AuthorTick");
            var ModItem_Desc = FindElementByName<TextBlock>(card, "ModItem_Desc");

            ModItem_Panel.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Green);
            ModItem_Name.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
            ModItem_Author.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
            ModItem_AuthorTick.Source = new BitmapImage(new Uri(@"Resources/embed_tick_white.png", UriKind.Relative));
            ModItem_Desc.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);

        }

        private void ModItem_MouseLeave(object sender, MouseEventArgs e)
        {
            MaterialDesignThemes.Wpf.Card card = (MaterialDesignThemes.Wpf.Card)sender;
            var ModItem_Panel = FindElementByName<StackPanel>(card, "ModItem_Panel");
            var ModItem_Name = FindElementByName<TextBlock>(card, "ModItem_Name");
            var ModItem_Author = FindElementByName<TextBlock>(card, "ModItem_Author");
            var ModItem_AuthorTick = FindElementByName<Image>(card, "ModItem_AuthorTick");
            var ModItem_Desc = FindElementByName<TextBlock>(card, "ModItem_Desc");

            ModItem_Panel.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
            ModItem_Name.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black);
            ModItem_Author.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Green);
            ModItem_AuthorTick.Source = new BitmapImage(new Uri(@"Resources/embed_tick.png", UriKind.Relative));
            ModItem_Desc.Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black);
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
    }
}
