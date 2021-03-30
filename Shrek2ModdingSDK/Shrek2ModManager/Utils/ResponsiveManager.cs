using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager.Utils
{
    public class ResponsiveManager
    {
        public MainWindow Window { get; set; }

        public ResponsiveManager(MainWindow window)
        {
            Window = window;
        }

        public void Handle()
        {
            Window.Res_Top_Menu.Width = GetWidth(1);
            Window.Res_Top_Menu_Left.Width = GetWidth(0.5f);
            Window.Res_Top_Menu_Right.Width = GetWidth(0.5f);

            Window.Res_Middle_Buttons.Width = GetWidth(1);
            Window.Res_Middle_Buttons_Left.Width = GetWidth(0.5f);
            Window.Res_Middle_Buttons_Right.Width = GetWidth(0.5f) - 37;

            Window.Res_Middle_Buttons_Left.Height = GetHeight(0.2f) + 20;
            Window.Res_Middle_Buttons_Right.Height = GetHeight(0.2f) + 20;

            Window.Overview_Button_PlayGame.Height = GetHeight(0.2f);
            Window.Overview_Button_ManageMods.Height = GetHeight(0.2f);

            Window.Res_Middle_Buttons_Left_Border.Height = GetHeight(0.2f);
            Window.Res_Middle_Buttons_Right_Border.Height = GetHeight(0.2f);

            Window.AllModsScrollViewer.Height = GetHeight(0.9f) - 150;

            Window.ManageModsPopup.Width = GetWidth(0.8f);
            Window.ManageModsPopup.Height = GetHeight(0.8f);

            Window.ManageModsPopup_Left.Width = Window.ManageModsPopup.Width * 0.2;
            Window.ManageModsPopup_Left.Height = Window.ManageModsPopup.Height;

            Window.ManageModsPopup_Right.Width = Window.ManageModsPopup.Width * 0.8;
            Window.ManageModsPopup_Right.Height = Window.ManageModsPopup.Height;

            Window.ManageModsPopup_Right_ScrollViewer.Height = (Window.ManageModsPopup_Right.Height * 0.7) - 50;
        }

        private double GetWidth(float percentage)
        {
            return Window.ActualWidth * percentage;
        }

        private double GetHeight(float percentage)
        {
            return Window.ActualHeight * percentage;
        }
    }
}
