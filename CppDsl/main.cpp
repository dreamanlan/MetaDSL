// Dsl.cpp : 定义控制台应用程序的入口点。
//
#include "BaseType.h"
#include "Dsl.h"

int main(int argc, char* argv[])
{
    char* pbuf = new char[1024 * 1024 + 1];
    char* pbuf2 = new char[1024 * 1024 + 1];
    FILE* fp = fopen("test.txt", "rb");
    size_t size = fread(pbuf, 1, 1024 * 1024, fp);
    pbuf[size] = 0;
    fclose(fp);
    char* p = pbuf;
    
    FILE* fp2 = fopen("test.h", "rb");
    size_t size2 = fread(pbuf2, 1, 1024 * 1024, fp2);
    pbuf2[size2] = 0;
    fclose(fp2);
    char* p2 = pbuf2;

    if (size >= 3 && pbuf[0] == (char)0xef && pbuf[1] == (char)0xbb && pbuf[2] == (char)0xbf) {
        //skip utf-8 bom
        p += 3;
    }
    if (size >= 3 && pbuf2[0] == (char)0xef && pbuf2[1] == (char)0xbb && pbuf2[2] == (char)0xbf) {
        //skip utf-8 bom
        p2 += 3;
    }
    //Dsl::DslOptions::DontLoadComments(true);
    Dsl::DslStringAndObjectBufferT<>* pDslBuffer = new Dsl::DslStringAndObjectBufferT<>();
    {
        Dsl::DslFile dataFile(*pDslBuffer);
        //dataFile.EnableDebugInfo();
        dataFile.OnBeforeAddFunction.attach([](auto& api, auto* sd) {
            if (sd->GetFunctionNum() > 0 && 0 != strcmp(sd->GetFunctionId(0), "if")) {
                //在BeforeAddFunction回调里结束当前语句并开始一个新语句，效果上相当于给前一个函数加上分号
                //api.endStatement();
                //api.beginStatement();
            }
            return true;
            });
        dataFile.OnAddFunction.attach([](auto& api, auto* sd, auto* func) {
            //在AddFunction里一般不要修改程序结构，但可以修改添加函数的信息
            return true;
            });
        dataFile.OnBeforeEndStatement.attach([](auto& api) {
            //在BeforeEndStatement里可以修改程序结构，要符合dsl的语法语义流程
            return true;
            });
        dataFile.OnEndStatement.attach([](auto& api, auto*& sd) {
            //在EndStatement里一般不要修改程序结构，但可以修改或整体替换当前语句，在回调后会化简语句并添加到上一层语法构造中
            return true;
            });
        dataFile.Parse(p);

        FILE* fp3 = fopen("copy.txt", "wb");
        dataFile.WriteToFile(fp3, 0);
        fclose(fp3);
        dataFile.SaveBinaryFile("binary.txt");
        Dsl::DslFile dataFile2(*pDslBuffer);
        dataFile2.LoadBinaryFile("binary.txt");
        FILE* fp4 = fopen("unbinary.txt", "wb");
        dataFile2.WriteToFile(fp4, 0);
        fclose(fp4);

        Dsl::DslFile dataFile3(*pDslBuffer);
        int len = 1024 * 1024;
        dataFile3.ParseGpp(p2, "={:=", "=:}=", pbuf, len);
        delete[] pbuf;
        delete[] pbuf2;
        FILE* fp5 = fopen("test_gpp.h", "wb");
        dataFile3.WriteToFile(fp5, 0);
        fclose(fp5);
    }
    //必须在DslFile都释放后再释放DslStringAndObjectBuffer
    delete pDslBuffer;
    return 0;
}

