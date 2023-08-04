mkdir build64 & pushd build64
cmake -G "Visual Studio 15 2017" -A x64 ..
popd
cmake --build build64 --config Debug --target CppDsl ZERO_CHECK

md Plugins\x86_64
copy /Y build64\Debug\CppDsl.lib Plugins\x86_64\CppDsl_Debug.lib

rem rmdir /s /q .\build64

pause