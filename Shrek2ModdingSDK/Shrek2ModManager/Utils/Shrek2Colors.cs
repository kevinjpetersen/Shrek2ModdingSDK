using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace Shrek2ModManager.Utils
{
    public class Shrek2Colors
    {
        public static string NavColor_Selected { get; set; } = "#65a338";
        public static string NavColor_Normal { get; set; } = "#b7cba8";
        public static string Color_White { get; set; } = "#ffffff";
        public static string Color_Black { get; set; } = "#000000";
        public static string Color_Green { get; set; } = "#65a338";

        public static Brush GetBrushFromHex(string hex)
        {
            return (SolidColorBrush)new BrushConverter().ConvertFrom(hex);
        }
    }
}
