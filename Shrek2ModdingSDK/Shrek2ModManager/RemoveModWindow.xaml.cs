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
    public partial class RemoveModWindow : Window
    {
        public Action? CloseModal { get; set; }
        public Action? RemovedMod { get; set; }

        public RemoveModWindow()
        {
            InitializeComponent();
        }

        public void SetModTitle(string title)
        {
            RemoveMod_Text.Text = $"Are you sure you want to remove the '{title}' mod?";
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            CloseModal?.Invoke();
        }

        private void Remove_Click(object sender, RoutedEventArgs e)
        {
            RemovedMod?.Invoke();
            CloseModal?.Invoke();
        }
    }
}
