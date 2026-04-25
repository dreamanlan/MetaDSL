mkdir -p build_lib && cd build_lib
cmake -G Xcode -D BUILD_AS_OSX_BUNDLE=1 -D BUILD_AS_OSX_DYLIB=0 -D CMAKE_OSX_ARCHITECTURES='$(ARCHS_STANDARD)' ../
cd ..
cmake --build build_lib --config Release
cp -rf build_lib/Release/CppDsl.bundle Plugins/
