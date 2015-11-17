using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.IO;

namespace Dsl
{
  class MainClass
  {
    [STAThread]
    public static void Main(string[] args)
    {
      DslLogDelegation logCallback = (string msg) => {
        Console.WriteLine("{0}", msg);
      };
      Dictionary<string, string> encodeTable = new Dictionary<string, string>();
      Dictionary<string, string> decodeTable = new Dictionary<string, string>();

      AddCrypto("skill", encodeTable, decodeTable);
      AddCrypto("section", encodeTable, decodeTable);
      AddCrypto("foreach", encodeTable, decodeTable);
      AddCrypto("looplist", encodeTable, decodeTable);
      AddCrypto("loop", encodeTable, decodeTable);
      AddCrypto("wait", encodeTable, decodeTable);
      AddCrypto("sleep", encodeTable, decodeTable);
      AddCrypto("while", encodeTable, decodeTable);
      AddCrypto("if", encodeTable, decodeTable);
      AddCrypto("log", encodeTable, decodeTable);

      AddCrypto("=", encodeTable, decodeTable);
      AddCrypto("+", encodeTable, decodeTable);
      AddCrypto("-", encodeTable, decodeTable);
      AddCrypto("*", encodeTable, decodeTable);
      AddCrypto("/", encodeTable, decodeTable);
      AddCrypto("%", encodeTable, decodeTable);
      AddCrypto(">", encodeTable, decodeTable);
      AddCrypto(">=", encodeTable, decodeTable);
      AddCrypto("==", encodeTable, decodeTable);
      AddCrypto("!=", encodeTable, decodeTable);
      AddCrypto("<", encodeTable, decodeTable);
      AddCrypto("<=", encodeTable, decodeTable);
      AddCrypto("&&", encodeTable, decodeTable);
      AddCrypto("||", encodeTable, decodeTable);
      AddCrypto("!", encodeTable, decodeTable);

      ScriptableDataFile file = new ScriptableDataFile();
      file.Load("test.txt", logCallback);
#if FULL_VERSION
      file.Save("copy.txt");
      string code1 = file.GenerateBinaryCode(File.ReadAllText("test.txt"), encodeTable, logCallback);
      File.WriteAllText("binary.txt", code1);
#endif
      file.ScriptableDatas.Clear();
      string code = File.ReadAllText("binary.txt");
      file.LoadBinaryCode(code, decodeTable);
#if FULL_VERSION
      file.Save("unbinary.txt");
#endif
      long t1 = GetLocalMilliseconds();
      for (int i = 0; i < 1000; ++i) {
        file.LoadBinaryCode(code, decodeTable);
      }
      long t2 = GetLocalMilliseconds();
      Console.WriteLine("time:{0}", t2 - t1);
    }

    private static void AddCrypto(string s, Dictionary<string, string> encodeTable, Dictionary<string, string> decodeTable)
    {
      string d = string.Format("_{0}_", s_NextIndex);
      ++s_NextIndex;
      encodeTable.Add(s, d);
      decodeTable.Add(d, s);
    }
    public static long GetLocalMilliseconds()
    {
      return (long)(Stopwatch.GetTimestamp() / s_TickPerUs);
    }
    
    private static double s_TickPerUs = Stopwatch.Frequency / 1000000.0;
    private static int s_NextIndex = 1;
  }
}
