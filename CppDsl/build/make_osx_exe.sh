mkdir -p build_osx && cd build_osx
cmake -G Xcode -D BUILD_AS_OSX_DYLIB=0 -D BUILD_AS_OSX_BUNDLE=0 -D CMAKE_OSX_ARCHITECTURES='$(ARCHS_STANDARD)' ../
cd ..
cmake --build build_osx --config Debug
cmake --build build_osx --config Release

cp -rf build_osx/Debug/CppDsl ../../Debug
cp -rf build_osx/Release/CppDsl ../../Release
