mkdir build32 & pushd build32
cmake -G "Visual Studio 16 2019" -A Win32 -DWIN32_X86=1 ..
popd
cmake --build build32 --config Release

md Plugins\x86
copy /Y build32\Release\CppDsl.lib Plugins\x86\CppDsl.lib

pause