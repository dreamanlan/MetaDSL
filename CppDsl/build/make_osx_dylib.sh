mkdir -p build_dylib && cd build_dylib
cmake -G Xcode -D BUILD_AS_OSX_DYLIB=1 -D BUILD_AS_OSX_BUNDLE=0 -D CMAKE_OSX_ARCHITECTURES='$(ARCHS_STANDARD)' ../
cd ..
cmake --build build_dylib --config Release
cp -rf build_dylib/Release/libCppDsl.dylib Plugins/
