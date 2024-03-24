mkdir -p build_osx && cd build_osx
cmake -G Xcode -D CMAKE_OSX_ARCHITECTURES='$(ARCHS_STANDARD)' ../
cd ..
cmake --build build_osx --config Debug
cmake --build build_osx --config Release

cp -rf build_osx/Debug/CppDsl ../../Debug
cp -rf build_osx/Release/CppDsl ../../Release
