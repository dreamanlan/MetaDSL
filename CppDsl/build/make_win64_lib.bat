mkdir build64 & pushd build64
cmake -G "Visual Studio 16 2019" -A x64 ..
popd
cmake --build build64 --config Release --target CppDsl ZERO_CHECK

md Plugins\x86_64
copy /Y build64\Release\CppDsl.lib Plugins\x86_64\CppDsl.lib

rem rmdir /s /q .\build64

pause