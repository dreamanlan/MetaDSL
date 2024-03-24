mkdir -p build_osx && cd build_osx
cmake -G Xcode -D BUILD_AS_OSX_DYLIB=1 -D CMAKE_OSX_ARCHITECTURES='$(ARCHS_STANDARD)' ../
cd ..
cmake --build build_osx --config Release
cp -rf build_osx/Release/libCppDsl.dylib Plugins/
