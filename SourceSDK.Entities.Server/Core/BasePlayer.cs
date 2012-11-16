using SourceSDK.Core.Interfaces.Server;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Entities.Server.Core
{
    [Export(typeof(BaseEntityServer))]
    [Export("player", typeof(BaseEntityServer))]
    [EntityMeta(ClassName = "player")]
    public class BasePlayer : BaseEntityServer
    {
        public void InitalSpawn()
        {
            throw new NotImplementedException();
        }

        public void Disconnect()
        {
            throw new NotImplementedException();
        }

        public void ClientCommand(string[] args)
        {
            throw new NotImplementedException();
        }

        public IPlayerState PlayerState { get; set; }

        public string PlayerName { get; set; }
    }
}
