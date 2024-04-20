#include <iostream>

extern "C" int cmain(int, char* []);

int main(int argc, char* argv[])
{
    return cmain(argc, argv);
}
