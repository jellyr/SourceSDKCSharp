using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    public delegate void ValueUpdatedHandler(String value);

    public interface IConVariable
    {
        String Name { get; }
        String HelpString { get; }
        
        CVarFlags Flags { get; }

        String Value { get; set; }
        String DefaultValue { get; }

        bool Managed { get; }

        //Reserved for console manager
        ValueUpdatedHandler ValueUpdated { set; }
    }

    public abstract class BaseConVariable : IConVariable
    {
        public abstract String Name { get; }
        public abstract String HelpString { get; }

        public abstract CVarFlags Flags { get; }
        public abstract String DefaultValue { get; }

        public int GetInt()
        {
            int v=0;
            Int32.TryParse(Value, out v);
            return v;
        }

        public bool GetBool()
        {
            bool v = false;
            Boolean.TryParse(Value, out v);
            return v;
        }

        public double GetDouble()
        {
            double v = 0.0f;
            Double.TryParse(Value, out v);
            return v;
        }

        private String _Value;
        public String Value
        {
            get
            {
                if (String.IsNullOrEmpty(_Value))
                    return DefaultValue;

                return _Value;
            }
            set
            {
                if (ValueUpdated != null)
                    ValueUpdated(value);

                _Value = value;
            }
        }

        public bool Managed
        {
            get
            {
                return true;
            }
        }

        public ValueUpdatedHandler ValueUpdated { private get; set; }
    }
}
