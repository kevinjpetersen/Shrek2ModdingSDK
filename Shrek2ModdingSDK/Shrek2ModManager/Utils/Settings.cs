using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager.Utils
{
    public class Settings
    {
        public string GameExeLocation { get; set; }
        public Languages Language { get; set; } = Languages.English;
        public WindowModes WindowMode { get; set; } = WindowModes.Fullscreen;

        public enum Languages
        {
            English, Russian
        }

        public enum WindowModes
        {
            Fullscreen, WindowMode
        }
    }
}
