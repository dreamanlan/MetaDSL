﻿using System;
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
            //string txt = Utility.CheckCppParseTable();
            //File.WriteAllText("CppParseTableCheck.txt", txt);
            //DslFile.DontLoadComments = true;
            List<string> keyBuffer = new List<string>();
            List<string> idBuffer = new List<string>();
            ///*
            DslFile file0 = new DslFile();
            string gppSrc;
            file0.LoadGpp("test.h", logCallback, "={:=", "=:}=", out gppSrc);
#if FULL_VERSION
            File.WriteAllText("test_gpp_src.h", gppSrc);
            file0.Save("test_gpp.h");
#endif
            file0.LoadCpp("test.h", logCallback);
#if FULL_VERSION
            file0.Save("copy.h");
#endif
            DslFile file1 = new DslFile();
            file1.LoadLua("test.lua", logCallback);
#if FULL_VERSION
            file1.Save("copy.lua");
#endif
            //*/
            DslFile file = new DslFile();
            //Modify the return statement to the 'return <-' syntax, ensuring that the return is at a shallow level
            //of semantic data for easier subsequent processing.
            file.onGetToken = (ref Dsl.Common.DslAction action, ref Dsl.Common.DslToken dslToken, ref string tok, ref short val, ref int line) => {
                if (tok == "return") {
                    string oldCurToken = dslToken.getCurToken();
                    string oldLastToken = dslToken.getLastToken();
                    int index;
                    char nc = dslToken.PeekNextValidChar(0, out index);
                    if (nc == '<' && dslToken.PeekChar(index + 1) == '-')
                        return false;
                    dslToken.setCurToken("<-");
                    dslToken.setLastToken(oldCurToken);
                    dslToken.enqueueToken(dslToken.getCurToken(), dslToken.getOperatorTokenValue(), line);
                    dslToken.setCurToken(oldCurToken);
                    dslToken.setLastToken(oldLastToken);
                }
                return true;
            };
            file.Load("test.txt", logCallback);
#if FULL_VERSION
            file.Save("copy.txt");
            file.SaveBinaryFile("binary.txt");
#endif
            
            file.DslInfos.Clear();
            var code = File.ReadAllBytes("binary.txt");
            file.LoadBinaryCode(code, keyBuffer, idBuffer);
#if FULL_VERSION
            file.Save("unbinary.txt");
#endif
            long t1 = GetLocalMilliseconds();
            for (int i = 0; i < 1000; ++i) {
                file.LoadBinaryCode(code, keyBuffer, idBuffer);
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
