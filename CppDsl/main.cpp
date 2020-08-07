// Dsl.cpp : 定义控制台应用程序的入口点。
//
#include "BaseType.h"
#include "Dsl.h"

int main(int argc, char* argv[])
{
	char* pbuf = new char[1024 * 1024 + 1];
	FILE* fp = fopen("test.txt", "rb");
	size_t size = fread(pbuf, 1, 1024 * 1024, fp);
	pbuf[size] = 0;
	fclose(fp);
	char* p = pbuf;
	if (size >= 3 && pbuf[0] == (char)0xef && pbuf[1] == (char)0xbb && pbuf[2] == (char)0xbf) {
		//skip utf-8 bom
		p += 3;
	}
    //Dsl::DslOptions::DontLoadComments(true);
    Dsl::DslStringAndObjectBufferT<>* pDslBuffer = new Dsl::DslStringAndObjectBufferT<>();
    {
        Dsl::DslFile dataFile(*pDslBuffer);
        //dataFile.EnableDebugInfo();
        dataFile.Parse(p);
        FILE* fp2 = fopen("copy.txt", "wb");
        dataFile.WriteToFile(fp2, 0);
        fclose(fp2);
        dataFile.SaveBinaryFile("binary.txt");
        Dsl::DslFile dataFile2(*pDslBuffer);
        dataFile2.LoadBinaryFile("binary.txt");
        FILE* fp3 = fopen("unbinary.txt", "wb");
        dataFile2.WriteToFile(fp3, 0);
        fclose(fp3);
    }
    //必须在DslFile都释放后再释放DslStringAndObjectBuffer
	delete[] pbuf;
    delete pDslBuffer;
	return 0;
}

