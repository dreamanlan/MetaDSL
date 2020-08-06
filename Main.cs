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
            //DslFile.DontLoadComments = true;
            DslFile file = new DslFile();
            file.Load("test.txt", logCallback);
#if FULL_VERSION
            file.Save("copy.txt");
            file.SaveBinaryFile("binary.txt");
#endif
            file.DslInfos.Clear();
            var code = File.ReadAllBytes("binary.txt");
            file.LoadBinaryCode(code);
#if FULL_VERSION
            file.Save("unbinary.txt");
#endif
            long t1 = GetLocalMilliseconds();
            for (int i = 0; i < 1000; ++i) {
                file.LoadBinaryCode(code);
            }
            long t2 = GetLocalMilliseconds();
            Console.WriteLine("time:{0}", t2 - t1);
        }

        public static long GetLocalMilliseconds()
        {
            return (long)(Stopwatch.GetTimestamp() / s_TickPerUs);
        }

        private static double s_TickPerUs = Stopwatch.Frequency / 1000000.0;
    }
}
