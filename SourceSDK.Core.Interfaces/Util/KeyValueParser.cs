using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Util
{
    public static class KeyValueParser
    {
        public static bool ParseEntities(String mapEntites, List<Dictionary<String, String>> outList)
        {
            var inGroup = false;
            var inKey = false;
            var inValue = false;

            var key = "";
            var val = "";

            Dictionary<String, String> curDict = null;

            foreach (var c in mapEntites)
            {
                if (c == '{' && !inKey && !inValue)
                {
                    if (inGroup)
                    {
                        Debug.Assert(false);
                        return false;
                    }

                    curDict = new Dictionary<string, string>();
                    inGroup = true;
                }
                else if (c == '}' && !inKey && !inValue)
                {
                    if (!inGroup)
                    {
                        Debug.Assert(false);
                        return false;
                    }

                    outList.Add(curDict);
                    curDict = null;
                    inGroup = false;
                }
                else if (c == '"')
                {
                    if (!inKey && String.IsNullOrEmpty(key))
                    {
                        inKey = true;
                    }
                    else if (!inKey && !inValue && String.IsNullOrEmpty(val))
                    {
                        inValue = true;
                    }
                    else if (inKey)
                    {
                        inKey = false;
                    }
                    else if (inValue)
                    {
                        inValue = false;

                        if (curDict.ContainsKey(key))
                            curDict[key] = val;
                        else
                            curDict.Add(key, val);

                        key = "";
                        val = "";
                    }
                }
                else if (inKey)
                {
                    key += c;
                }
                else if (inValue)
                {
                    val += c;
                }
            }

            if (inGroup || inKey || inValue)
                return false;

            return true;
        }

    }
}
