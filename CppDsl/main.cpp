// Dsl.cpp : 定义控制台应用程序的入口点。
//
#include "BaseType.h"
#include "SourceCodeScript.h"

int main(int argc, char* argv[])
{
  char* pbuf = new char[1024 * 1024 + 1];
  FILE* fp = fopen("test.txt", "rb");
  size_t size = fread(pbuf, 1, 1024 * 1024, fp);
  pbuf[size] = 0;
  fclose(fp);
  SourceCodeScript script;
  script.Parse(pbuf);
  const Dsl::DslFile& dataFile = script.GetDslFile();
  FILE* fp2 = fopen("copy.txt", "wb");
  dataFile.WriteToFile(fp2, 0);
  fclose(fp2);
  delete[] pbuf;
	return 0;
}

