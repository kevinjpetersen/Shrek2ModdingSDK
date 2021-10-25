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
        public Shrek2Config LoadedConfig { get; set; }

        public enum FieldTypes
        {
            Unknown, String, Bool, Int, Long, Float
        }

        public ManageModsWindow(List<Mod> mods)
        {
            InitializeComponent();
            Mods = mods;
            LoadedConfig = null;
            SelectedMod = null;
        }

        private void Window_Loaded(object sender, RoutedEventArgs rea)
        {
            LoadedConfig = null;
            SelectedMod = null;
            ErrorMessage.Text = "";
            SelectedModNoConfig.Visibility = Visibility.Collapsed;

            InstalledMods = Mod.GetInstalledMods(Mods);

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
        }

        private void InstalledModsList_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            ErrorMessage.Text = "";

            var item = e.Source as ListViewItem;
            if (item != null && item.IsSelected)
            {
                SelectedMod = InstalledMods.FirstOrDefault(p => p.ModGUID.Replace("-", "") == item.Name);

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
            }
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

            if(LoadedConfig.Docs.ContainsKey(field.Key))
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

            if (fieldType == FieldTypes.String || fieldType == FieldTypes.Int || fieldType == FieldTypes.Float || fieldType == FieldTypes.Long)
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

        private void ConfigSaveButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                ErrorMessage.Text = "";
                var configFields = new Dictionary<string, object>();

                foreach(var field in LoadedConfig.Config)
                {
                    var fieldType = GetFieldType(field.Value);

                    if (fieldType == FieldTypes.String)
                    {
                        var fieldItem = FindElementByName<TextBox>(ConfigFields_Items, field.Key);
                        configFields.Add(field.Key, fieldItem.Text);
                    } 
                    else if (fieldType == FieldTypes.Int)
                    {
                        var fieldItem = FindElementByName<TextBox>(ConfigFields_Items, field.Key);
                        if(int.TryParse(fieldItem.Text, out int num))
                        {
                            configFields.Add(field.Key, num);
                        } else
                        {
                            ErrorMessage.Text = $"The setting '{field.Key}' can only be a number!";
                            MessageBox.Show($"The setting '{field.Key}' can only be a number!");
                            return;
                        }
                    } 
                    else if (fieldType == FieldTypes.Float || fieldType == FieldTypes.Long)
                    {
                        var fieldItem = FindElementByName<TextBox>(ConfigFields_Items, field.Key);
                        if(float.TryParse(fieldItem.Text, out float num))
                        {
                            configFields.Add(field.Key, num);
                        } else
                        {
                            ErrorMessage.Text = $"The setting '{field.Key}' can only be a decimal number!";
                            MessageBox.Show($"The setting '{field.Key}' can only be a decimal number!");
                            return;
                        }
                    } 
                    else if (fieldType == FieldTypes.Bool)
                    {
                        var fieldItem = FindElementByName<CheckBox>(ConfigFields_Items, field.Key);
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

        public FieldTypes GetFieldType(object fieldObject)
        {
            if (fieldObject is bool) return FieldTypes.Bool;
            if (fieldObject is float) return FieldTypes.Float;
            if (fieldObject is long) return FieldTypes.Long;
            if (fieldObject is double) return FieldTypes.Long;
            if (fieldObject is decimal) return FieldTypes.Long;
            if (fieldObject is string) return FieldTypes.String;
            if (fieldObject is int) return FieldTypes.Int;
            return FieldTypes.Unknown;
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

                if (child is T && child.DataContext.Equals(sChildName))
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
