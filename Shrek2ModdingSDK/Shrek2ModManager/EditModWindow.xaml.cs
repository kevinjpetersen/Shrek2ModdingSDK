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
    /// Interaction logic for TestWindow.xaml
    /// </summary>
    public partial class EditModWindow : Window
    {
        public Action? CloseModal { get; set; }
        public Action<Shrek2ModListItem?>? EditedMod { get; set; }

        public Shrek2ModListItem? Mod { get; set; }

        public EditModWindow()
        {
            InitializeComponent();
        }

        public void InitEditMod(Shrek2ModListItem? mod)
        {
            Mod = mod;
            EditMod_ErrorMessage.Text = "";
            EditMod_Text.Text = $"Settings for '{Mod?.Title}'";

            EditMod_Title.Text = mod?.Title;
            EditMod_Description.Text = mod?.Description;
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            CloseModal?.Invoke();
        }

        private void Edited_Click(object sender, RoutedEventArgs e)
        {
            if(string.IsNullOrWhiteSpace(EditMod_Title.Text))
            {
                EditMod_ErrorMessage.Text = "Title cannot be empty!";
                return;
            }

            if (Mod == null) return;

            Mod.Title = EditMod_Title.Text;
            Mod.Description = EditMod_Description.Text;

            EditedMod?.Invoke(Mod);
            CloseModal?.Invoke();
        }
    }
}
