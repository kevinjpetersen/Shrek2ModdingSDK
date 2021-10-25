using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Shrek2CETConverter
{
    public partial class Form1 : Form
    {
        class SCheatOffsets
        {
            public List<object> Offset { get; set; }
        }

        class SCheatRoot
        {
            public List<SCheatEntry> CheatEntries { get; set; }
        }

        class SCheatTable
        {
            public SCheatEntries CheatEntries { get; set; }
        }

        class SCheatEntries
        {
            public List<SCheatEntry> CheatEntries { get; set; }
        }

        class SCheatEntry
        {
            public int ID { get; set; }
            public string Description { get; set; }
            public string VariableType { get; set; }
            public string Address { get; set; }
            public List<string> Offsets { get; set; }
        }

        public Form1()
        {
            InitializeComponent();
        }

        string GetReturnType(string type)
        {
            switch (type)
            {
                case "Float": return "float";
                case "2 Bytes": return "short int";
                case "4 Bytes": return "int";
                case "Byte": return "bool";
                default: return "UNKNOWN_TYPE";
            }
        }

        string GetMemoryFunctionType(string type)
        {
            switch (type)
            {
                case "Float": return "Float";
                case "2 Bytes": return "ShortInt";
                case "4 Bytes": return "Int";
                case "Byte": return "Bool";
                default: return "UNKNOWN_TYPE";
            }
        }

        private void convertButton_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(inputTextbox.Text)) return;

            //try
            //{
            var ct = JsonConvert.DeserializeObject<SCheatRoot>(inputTextbox.Text);

            var headerPointerCodes = new List<string>();
            var sourcePointerCodes = new List<string>();

            foreach (var ce in ct.CheatEntries)
            {
                ce.Description = ce.Description.Replace(" ", "").Replace("\"", "");
                ce.Offsets.Reverse();
                var baseAddr = ce.Address.Split('+')[0];
                var addr = ce.Address.Split('+')[1];

                if (ce.Description.Contains("T)"))
                {
                    var descSplits = ce.Description.Split('(');
                    var area = descSplits[1];
                    ce.Description = descSplits[0];

                    int falseValue = int.Parse(area.Substring(0, area.IndexOf('=')));
                    int trueValue = int.Parse(area.Substring(area.IndexOf(',') + 1).Replace("=T)", ""));

                    string header = @"
" + GetReturnType(ce.VariableType) + " Get" + ce.Description + @"();
bool Set" + ce.Description + "(" + GetReturnType(ce.VariableType) + " " + ce.Description + @");";

                    string source = @"
bool Shrek2Pointers::Set" + ce.Description + "(bool " + ce.Description + @") {
	return Shrek2Memory::WriteByte(" + ce.Description + " ? " + trueValue + " : " + falseValue + ", " + baseAddr + ", 0x" + addr + ", 0x" + ce.Offsets[0].ToString() + ", 0x" + ce.Offsets[1].ToString() + ", 0x" + ce.Offsets[2].ToString() + ", 0x" + ce.Offsets[3].ToString() + @");
}
bool Shrek2Pointers::Get" + ce.Description + @"() {
    byte localByte = Shrek2Memory::ReadByte(" + baseAddr + ", 0x" + addr + ", 0x" + ce.Offsets[0].ToString() + ", 0x" + ce.Offsets[1].ToString() + ", 0x" + ce.Offsets[2].ToString() + ", 0x" + ce.Offsets[3].ToString() + @");
    return localByte == " + trueValue + @" ? true : false;
}";

                    headerPointerCodes.Add(header);
                    sourcePointerCodes.Add(source);

                }
                else
                {
                    string header = @"
" + GetReturnType(ce.VariableType) + " Get" + ce.Description + @"();
bool Set" + ce.Description + "(" + GetReturnType(ce.VariableType) + " " + ce.Description + @");";

                    string source = @"
bool Shrek2Pointers::Set" + ce.Description + "(" + GetReturnType(ce.VariableType) + " " + ce.Description + @") {
	return Shrek2Memory::Write" + GetMemoryFunctionType(ce.VariableType) + "(" + ce.Description + ", " + baseAddr + ", 0x" + addr + ", 0x" + ce.Offsets[0].ToString() + ", 0x" + ce.Offsets[1].ToString() + ", 0x" + ce.Offsets[2].ToString() + ", 0x" + ce.Offsets[3].ToString() + @");
}
" + GetReturnType(ce.VariableType) + " Shrek2Pointers::Get" + ce.Description + @"() {
    return Shrek2Memory::Read" + GetMemoryFunctionType(ce.VariableType) + "(" + baseAddr + ", 0x" + addr + ", 0x" + ce.Offsets[0].ToString() + ", 0x" + ce.Offsets[1].ToString() + ", 0x" + ce.Offsets[2].ToString() + ", 0x" + ce.Offsets[3].ToString() + @");
}";

                    headerPointerCodes.Add(header);
                    sourcePointerCodes.Add(source);
                }

                outputTextbox.Text = string.Join("\r\n", headerPointerCodes);
                outputTextbox.Text += "\r\n\r\n";
                outputTextbox.Text += string.Join("\r\n", sourcePointerCodes);


            }
            //}
            //catch
            //{
            //    MessageBox.Show("Invalid Cheat Table JSON");
            //}
        }
    }
}
