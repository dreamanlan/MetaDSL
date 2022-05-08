// pg.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

extern "C" int cmain(int, char* []);

int main(int argc, char* argv[])
{
    return cmain(argc, argv);
}
