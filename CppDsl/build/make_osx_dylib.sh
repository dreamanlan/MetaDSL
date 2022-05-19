mkdir -p build_osx && cd build_osx
cmake -DBUILD_AS_OSX_DYLIB=1 -GXcode ../
cd ..
cmake --build build_osx --config Release
cp -rf build_osx/Release/libCppDsl.dylib Plugins/
