mkdir -p build_osx && cd build_osx
cmake -GXcode ../
cd ..
cmake --build build_osx --config Release
cp -rf build_osx/Release/CppDsl.bundle Plugins/
