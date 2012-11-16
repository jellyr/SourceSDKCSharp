using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
	public interface IConCommand
	{
		String Name { get; }
		String HelpString { get; }
		CVarFlags Flags { get; }

		void AutoComplete(String partial, List<String> suggetions);
		void Execute(String[] args);

        bool Managed { get; }
	}

    public abstract class BaseConCommand : IConCommand
    {
        public abstract String Name { get; }
        public abstract String HelpString { get; }
        public abstract CVarFlags Flags { get; }

        public abstract void AutoComplete(String partial, List<String> suggetions);
        public abstract void Execute(String[] args);

        public bool Managed
        {
            get { return true; }
        }
    }
}
