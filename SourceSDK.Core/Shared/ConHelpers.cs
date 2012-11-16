using SourceSDK.Core.Interfaces;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Shared
{
    [Export(typeof(IConCommand))]
    public class CmdListConCommand : BaseConCommand
    {
        public override string Name
        {
            get { return "cmdlist"; }
        }

        public override string HelpString
        {
            get { return "Displays all the commands"; }
        }

        public override CVarFlags Flags
        {
            get { return CVarFlags.NONE; }
        }

        public override void AutoComplete(string partial, List<string> suggetions)
        {
        }

        public override void Execute(string[] args)
        {
            var cm = Mef.GetExportedValue<NI_ConsoleManager>();
            var list = cm.GetConCommands();

            list.Sort((a, b) => a.Name.CompareTo(b.Name));

            foreach (var c in list)
            {
                var h = c.HelpString;

                h = h.Replace('\n', ' ');

                if (h.Length > 64)
                    h = h.Substring(0, 64) + "...";

                cm.Write("\t" + c.Name);

                if (String.IsNullOrEmpty(h))
                    cm.WriteLine("");
                else
                    cm.WriteLine(Color.DarkRed, String.Format(" - {0}", h));
            }
        }
    }

    [Export(typeof(IConCommand))]
    public class CVarListConCommand : BaseConCommand
    {
        public override string Name
        {
            get { return "cvarlist"; }
        }

        public override string HelpString
        {
            get { return "Displays all the console variables"; }
        }

        public override CVarFlags Flags
        {
            get { return CVarFlags.NONE; }
        }

        public override void AutoComplete(string partial, List<string> suggetions)
        {
        }

        public override void Execute(string[] args)
        {
            var cm = Mef.GetExportedValue<NI_ConsoleManager>();
            var list = cm.GetConVariables();

            list.Sort((a, b) => a.Name.CompareTo(b.Name));

            foreach (var c in list)
            {
                var h = c.HelpString;

                h = h.Replace('\n', ' ');

                if (h.Length > 64)
                    h = h.Substring(0, 64) + "...";

                cm.Write(String.Format("\t{0} ({1})", c.Name, c.Value));

                if (String.IsNullOrEmpty(h))
                    cm.WriteLine("");
                else
                    cm.WriteLine(Color.DarkRed, String.Format(" - {0}", h));
            }
        }
    }
}
