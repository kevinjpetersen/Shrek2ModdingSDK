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

        public List<Mod> Mods { get; set; } = new List<Mod>();

        public static Settings Settings { get; set; }

        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            Application.Current.Shutdown();
        }

        private async void Window_Loaded(object sender, RoutedEventArgs rea)
        {
            Nav_Button_Overview.Click += async (s, e) => await SelectNavItem(0);
            Nav_Button_Mods.Click += async (s, e) => await SelectNavItem(1);

            Nav_Button_Settings.Click += Nav_Button_Settings_Click;

            Overview_Button_PlayGame.MouseEnter += Overview_Button_PlayGame_MouseEnter;
            Overview_Button_PlayGame.MouseLeave += Overview_Button_PlayGame_MouseLeave;
            Overview_Button_ManageMods.MouseEnter += Overview_Button_ManageMods_MouseEnter;
            Overview_Button_ManageMods.MouseLeave += Overview_Button_ManageMods_MouseLeave;

            Overview_Button_PlayGame.MouseUp += Overview_Button_PlayGame_MouseUp;
            Overview_Button_ManageMods.MouseUp += Overview_Button_ManageMods_MouseUp;

            Settings = SH2WorkshopFileHandler.GetSettings();

            Mods = Mod.GetMods();
            Mods = Mods.OrderByDescending(p => p.ID).ToList();

            PopulateMaps(Popular_Maps_Panel, false);
            PopulateMaps(Maps_Panel, true);

            PopulatePagination(Maps_Pagination_Panel);
        }

        private void Overview_Button_ManageMods_MouseUp(object sender, MouseButtonEventArgs e)
        {
            try
            {
                //if (string.IsNullOrWhiteSpace(Settings.UE2EditorExeLocation))
                //{
                //    MessageBox.Show("You have not setup the UE2 UnrealEd.exe in the Settings! You need to set it up before you can open the editor from here!");
                //    return;
                //}
                //Process.Start(Settings.UE2EditorExeLocation);
            }
            catch
            {

            }
        }

        private void Overview_Button_PlayGame_MouseUp(object sender, MouseButtonEventArgs e)
        {
            try
            {
                if (string.IsNullOrWhiteSpace(Settings.GameExeLocation))
                {
                    MessageBox.Show("You have not setup the Shrek 2 Game.exe in the Settings! You need to set it up before you can play maps directly!");
                    return;
                }
                Process.Start(Settings.GameExeLocation, Settings.WindowMode == Settings.WindowModes.WindowMode ? "-windowed" : "");
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

        private void SwitchPage(int i)
        {
            //MapsPageNumber = i;
            //PopulateMaps(Maps_Panel, true);
        }
        /*
        private void PopulatePagination(StackPanel panel)
        {
            panel.Children.Clear();

            var maxPages = (Maps.Count / 10) + (Maps.Count % 10 > 0 ? 1 : 0);
            for (int i = 1; i <= maxPages; i++)
            {
                var button = new Button()
                {
                    Style = (Style)FindResource("MaterialDesignFloatingActionButton"),
                    Background = Shrek2Colors.GetBrushFromHex(i == 1 ? Shrek2Colors.NavColor_Selected : Shrek2Colors.NavColor_Normal),
                    BorderBrush = Shrek2Colors.GetBrushFromHex(i == 1 ? Shrek2Colors.NavColor_Selected : Shrek2Colors.NavColor_Normal),
                    Height = 30,
                    Width = 30,
                    Margin = new Thickness(10, 0, 0, 0),
                    Content = i
                };
                button.Click += (e, s) =>
                {
                    foreach (var child in panel.Children)
                    {
                        if (child is Button)
                        {
                            (child as Button).Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Normal);
                            (child as Button).BorderBrush = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Normal);
                        }
                    }

                    button.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);
                    button.BorderBrush = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);

                    SwitchPage(int.Parse(button.Content.ToString()) - 1);
                };
                panel.Children.Add(button);
            }
        }
        */

        /*
        private void PopulateMaps(StackPanel panel, bool hasTwoRows)
        {
            panel.Children.Clear();

            var rowPanel1 = new StackPanel()
            {
                Orientation = Orientation.Horizontal
            };

            var rowPanel2 = new StackPanel()
            {
                Orientation = Orientation.Horizontal
            };

            foreach (var map in Maps.Skip(10 * MapsPageNumber).Take(5))
            {
                var card = new MaterialDesignThemes.Wpf.Card()
                {
                    Margin = new Thickness(map == Maps.Skip(10 * MapsPageNumber).First() ? 0 : 10, 10, map == Maps.Skip(10 * MapsPageNumber).Take(5).Last() ? 0 : 10, 10),
                    Width = 156,
                    Height = 200
                };

                card.Content = new StackPanel();
                card.Cursor = Cursors.Hand;

                StackPanel cardPanel = card.Content as StackPanel;

                var defaultBorderBrush = cardPanel.Background;

                cardPanel.MouseEnter += (s, e) =>
                {
                    cardPanel.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);
                    foreach (var child in cardPanel.Children)
                    {
                        if (child is TextBlock) (child as TextBlock).Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
                        if (child is StackPanel)
                        {
                            ((child as StackPanel).Children[0] as TextBlock).Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
                            ((child as StackPanel).Children[1] as Image).Source = new BitmapImage(new Uri(@"/Shrek2Workshop;component/images/tick_white.png", UriKind.Relative));
                        }
                    }
                };

                cardPanel.MouseLeave += (s, e) =>
                {
                    cardPanel.Background = defaultBorderBrush;
                    foreach (var child in cardPanel.Children)
                    {
                        if (child is TextBlock)
                        {
                            (child as TextBlock).Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black);
                        }
                        if (child is StackPanel)
                        {
                            ((child as StackPanel).Children[0] as TextBlock).Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Green);
                            ((child as StackPanel).Children[1] as Image).Source = new BitmapImage(new Uri(@"/Shrek2Workshop;component/images/tick.png", UriKind.Relative));
                        }
                    }
                };

                cardPanel.MouseUp += (s, e) =>
                {
                    if (MapWindow != null)
                    {
                        MapWindow.Focus();
                        return;
                    }

                    MapWindow = new MapWindow(map);
                    MapWindow.Closed += (a, b) => MapWindow = null;
                    MapWindow.Show();
                };

                cardPanel.Children.Add(new Image()
                {
                    Source = new BitmapImage(new Uri(Uri.IsWellFormedUriString(map.ImageUrl, UriKind.Absolute) ? map.ImageUrl : "https://www.hbo.com/content/dam/hbodata/movies/s/shrek-2/article/shrek-2-1920.jpg/_jcr_content/renditions/cq5dam.web.1200.675.jpeg")),
                    Height = 80,
                    Width = 156,
                    Stretch = Stretch.UniformToFill
                });

                cardPanel.Children.Add(new TextBlock()
                {
                    Style = (Style)FindResource("MaterialDesignBody1TextBlock"),
                    Text = map.Name,
                    Margin = new Thickness(10, 5, 10, 0),
                    TextTrimming = TextTrimming.CharacterEllipsis,
                    FontWeight = FontWeights.Bold,
                    Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black)
                });

                var authorPanel = new StackPanel()
                {
                    Orientation = Orientation.Horizontal
                };
                authorPanel.Children.Add(new TextBlock()
                {
                    Style = (Style)FindResource("MaterialDesignSubtitle2TextBlock"),
                    Text = $"By {map.Author}",
                    Margin = new Thickness(10, 0, 5, 5),
                    TextTrimming = TextTrimming.CharacterEllipsis,
                    FontWeight = FontWeights.Normal,
                    Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Green)
                });
                authorPanel.Children.Add(new Image()
                {
                    Visibility = map.Verified ? Visibility.Visible : Visibility.Hidden,
                    Height = 15,
                    Width = 15,
                    VerticalAlignment = VerticalAlignment.Top,
                    Source = new BitmapImage(new Uri(@"/Shrek2Workshop;component/images/tick.png", UriKind.Relative)),
                    Margin = new Thickness(0, 2, 5, 0)
                });

                cardPanel.Children.Add(authorPanel);

                cardPanel.Children.Add(new TextBlock()
                {
                    Style = (Style)FindResource("MaterialDesignBody1TextBlock"),
                    Text = map.Description,
                    Margin = new Thickness(10, 0, 10, 0),
                    FontSize = 12,
                    TextTrimming = TextTrimming.CharacterEllipsis,
                    TextWrapping = TextWrapping.Wrap,
                    MaxHeight = 65,
                    Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black)
                });

                card.Content = cardPanel;
                rowPanel1.Children.Add(card);
            }
            panel.Children.Add(rowPanel1);

            if (hasTwoRows)
            {
                foreach (var map in Maps.Skip(10 * MapsPageNumber).Skip(5).Take(5))
                {
                    var card = new MaterialDesignThemes.Wpf.Card()
                    {
                        Margin = new Thickness(map == Maps.Skip(10 * MapsPageNumber).Skip(5).First() ? 0 : 10, 10, map == Maps.Skip(10 * MapsPageNumber).Skip(5).Take(5).Last() ? 0 : 10, 10),
                        Width = 156,
                        Height = 200
                    };

                    card.Content = new StackPanel();
                    card.Cursor = Cursors.Hand;

                    StackPanel cardPanel = card.Content as StackPanel;

                    var defaultBorderBrush = cardPanel.Background;

                    cardPanel.MouseEnter += (s, e) =>
                    {
                        cardPanel.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);
                        foreach (var child in cardPanel.Children)
                        {
                            if (child is TextBlock) (child as TextBlock).Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
                            if (child is StackPanel)
                            {
                                ((child as StackPanel).Children[0] as TextBlock).Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_White);
                                ((child as StackPanel).Children[1] as Image).Source = new BitmapImage(new Uri(@"/Shrek2Workshop;component/images/tick_white.png", UriKind.Relative));
                            }
                        }
                    };

                    cardPanel.MouseLeave += (s, e) =>
                    {
                        cardPanel.Background = defaultBorderBrush;
                        foreach (var child in cardPanel.Children)
                        {
                            if (child is TextBlock)
                            {
                                (child as TextBlock).Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black);
                            }
                            if (child is StackPanel)
                            {
                                ((child as StackPanel).Children[0] as TextBlock).Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Green);
                                ((child as StackPanel).Children[1] as Image).Source = new BitmapImage(new Uri(@"/Shrek2Workshop;component/images/tick.png", UriKind.Relative));
                            }
                        }
                    };

                    cardPanel.MouseUp += (s, e) =>
                    {
                        //if (MapWindow != null)
                        //{
                        //    MapWindow.Focus();
                        //    return;
                        //}

                        //MapWindow = new MapWindow(map);
                        //MapWindow.Closed += (a, b) => MapWindow = null;
                        //MapWindow.Show();
                    };

                    cardPanel.Children.Add(new Image()
                    {
                        Source = new BitmapImage(new Uri(Uri.IsWellFormedUriString(map.ImageUrl, UriKind.Absolute) ? map.ImageUrl : "https://www.hbo.com/content/dam/hbodata/movies/s/shrek-2/article/shrek-2-1920.jpg/_jcr_content/renditions/cq5dam.web.1200.675.jpeg")),
                        Height = 80,
                        Width = 156,
                        Stretch = Stretch.UniformToFill
                    });

                    cardPanel.Children.Add(new TextBlock()
                    {
                        Style = (Style)FindResource("MaterialDesignBody1TextBlock"),
                        Text = map.Name,
                        Margin = new Thickness(10, 5, 10, 0),
                        TextTrimming = TextTrimming.CharacterEllipsis,
                        FontWeight = FontWeights.Bold,
                        Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black)
                    });

                    var authorPanel = new StackPanel()
                    {
                        Orientation = Orientation.Horizontal
                    };
                    authorPanel.Children.Add(new TextBlock()
                    {
                        Style = (Style)FindResource("MaterialDesignSubtitle2TextBlock"),
                        Text = $"By {map.Author}",
                        Margin = new Thickness(10, 0, 5, 5),
                        TextTrimming = TextTrimming.CharacterEllipsis,
                        FontWeight = FontWeights.Normal,
                        Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Green)
                    });
                    authorPanel.Children.Add(new Image()
                    {
                        Visibility = map.Verified ? Visibility.Visible : Visibility.Hidden,
                        Height = 15,
                        Width = 15,
                        VerticalAlignment = VerticalAlignment.Top,
                        Source = new BitmapImage(new Uri(@"/Shrek2Workshop;component/images/tick.png", UriKind.Relative)),
                        Margin = new Thickness(0, 2, 5, 0)
                    });

                    cardPanel.Children.Add(authorPanel);

                    cardPanel.Children.Add(new TextBlock()
                    {
                        Style = (Style)FindResource("MaterialDesignBody1TextBlock"),
                        Text = map.Description,
                        Margin = new Thickness(10, 0, 10, 0),
                        FontSize = 12,
                        TextTrimming = TextTrimming.CharacterEllipsis,
                        TextWrapping = TextWrapping.Wrap,
                        MaxHeight = 65,
                        Foreground = Shrek2Colors.GetBrushFromHex(Shrek2Colors.Color_Black)
                    });

                    card.Content = cardPanel;
                    rowPanel2.Children.Add(card);
                }
                panel.Children.Add(rowPanel2);
            }
        }
        */
        private async Task RefreshMaps()
        {
            //Maps = await SH2WorkshopSDK.GetMaps();
            //Maps = Maps.OrderByDescending(p => DateTimeOffset.ParseExact(p.MapCreated, "yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture)).ToList();

            //PopulateMaps(Popular_Maps_Panel, false);
            //PopulateMaps(Maps_Panel, true);
            //PopulatePagination(Maps_Pagination_Panel);
            //PopulateMaps(Mods_Panel, true);
        }

        private async Task SelectNavItem(int item)
        {
            if (item == 0)
            {
                //MapsPageNumber = 0;
                Nav_Button_Overview.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);
                Nav_Button_Mods.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Normal);

                Content_Panel_Overview.Visibility = Visibility.Visible;
                Content_Panel_Mods.Visibility = Visibility.Collapsed;

                //await RefreshMaps();
            }
            else if (item == 1)
            {
                Nav_Button_Overview.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Normal);
                Nav_Button_Mods.Background = Shrek2Colors.GetBrushFromHex(Shrek2Colors.NavColor_Selected);

                Content_Panel_Overview.Visibility = Visibility.Collapsed;
                Content_Panel_Mods.Visibility = Visibility.Visible;

                //await RefreshMaps();
            }
        }
    }
}
