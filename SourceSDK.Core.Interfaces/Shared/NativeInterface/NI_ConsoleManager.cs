using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    public enum CVarFlags
	{
		NONE = 0,
		UNREGISTERED = (1<<0),
		DEVELOPMENTONLY = (1<<1),
		GAMEDLL = (1<<2),
		CLIENTDLL = (1<<3),
		HIDDEN = (1<<4),
		PROTECTED = (1<<5),
		SPONLY = (1<<6),
		ARCHIVE = (1<<7),
		NOTIFY = (1<<8),
		USERINFO = (1<<9),
		CHEAT = (1<<14),
		PRINTABLEONLY = (1<<10),
		UNLOGGED = (1<<11),
		NEVER_AS_STRING = (1<<12),
		REPLICATED = (1<<13),
		DEMO = (1<<16),
		DONTRECORD = (1<<17),
		NOT_CONNECTED = (1<<22),
		SERVER_CAN_EXECUTE = (1<<28),
		SERVER_CANNOT_QUERY = (1<<29),
		CLIENTCMD_CAN_EXECUTE = (1<<30)
	}

    public interface NI_ConsoleManager
    {
		void Register(IConCommand conCommand);
		void Unregister(IConCommand conCommand);

		void Register(IConVariable conVariable);
		void Unregister(IConVariable conVariable);

		List<IConCommand> GetConCommands();
		List<IConVariable> GetConVariables();

		IConCommand FindConCommand(String name);
		IConVariable FindConVariable(String name);

        void Write(String line);
        void Write(Color color, String line);

        void WriteLine(String line);
        void WriteLine(Color color, String line);
    }
}
