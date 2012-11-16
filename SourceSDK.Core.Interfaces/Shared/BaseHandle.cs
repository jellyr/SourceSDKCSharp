using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    public class BaseHandle
    {
        public const UInt32 MaxEdictBits = 11;
        public const UInt32 MaxEntEntries = MaxEdictBits + 1;
        public const UInt32 InvalidEHandleIndex = 0xFFFFFFFF;

        public bool IsValid
        {
            get
            {
                return Index != InvalidEHandleIndex;
            }
        }

        public int EntityIndex
        {
            get
            {
                return (int)(Index & MaxEdictBits);
            }
        }

        public int SerialNumber
        {
            get
            {
                return (int)(Index >> (int)MaxEntEntries);
            }
        }

        public UInt32 Index
        {
            get;
            protected set;
        }
  
        public BaseHandle(UInt32 value)
        {
            Index = value;
        }

        public BaseHandle(int entry, int serialNumber)
        {
            Index = (UInt32)entry + ((UInt32)serialNumber << (int)MaxEntEntries);
        }

        public BaseHandle(BaseHandle handle)
        {
            Index = handle.Index;
        }

        public void Release()
        {
            Index = InvalidEHandleIndex;
        }

        public M_IHandleEntity Get()
        {
            return null;
        }

        public override bool Equals(object obj)
        {
            if (obj is BaseHandle == false)
                return false;

            return Index == ((BaseHandle)obj).Index;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public static bool operator < (BaseHandle a, BaseHandle b)
        {
            return a.Index < b.Index;
        }

        public static bool operator >(BaseHandle a, BaseHandle b)
        {
            return a.Index > b.Index;
        }

        public static bool operator <=(BaseHandle a, BaseHandle b)
        {
            return a.Index <= b.Index;
        }

        public static bool operator >=(BaseHandle a, BaseHandle b)
        {
            return a.Index >= b.Index;
        }

        public static bool operator ==(BaseHandle a, BaseHandle b)
        {
            return a.Index == b.Index;
        }

        public static bool operator !=(BaseHandle a, BaseHandle b)
        {
            return a.Index != b.Index;
        }
    }
}
