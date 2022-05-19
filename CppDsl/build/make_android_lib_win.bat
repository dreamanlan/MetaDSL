set ANDROID_NDK=D:\android-ndk-r23b
set ANDROID_CMAKE=C:\Users\Admin\AppData\Local\Android\Sdk\cmake\3.18.1\bin\cmake.exe
set ANDROID_NINJA=C:\Users\Admin\AppData\Local\Android\Sdk\cmake\3.18.1\bin\ninja.exe

cmake -S . -B build.Android.armeabi-v7a -DANDROID=1 -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_MAKE_PROGRAM=%ANDROID_NINJA% -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_VERSION=23 -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_GENERATOR="Ninja"
cd build.Android.armeabi-v7a
%ANDROID_NINJA%
cd ..
md Plugins\Android\libs\armeabi-v7a\
copy /Y build.Android.armeabi-v7a\libCppDsl.so Plugins\Android\libs\armeabi-v7a\libCppDsl.so

cmake -S . -B build.Android.arm64-v8a -DANDROID=1 -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a -DCMAKE_MAKE_PROGRAM=%ANDROID_NINJA% -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_VERSION=23 -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_GENERATOR="Ninja"
cd build.Android.arm64-v8a
%ANDROID_NINJA%
cd ..
md Plugins\Android\libs\arm64-v8a\
copy /Y build.Android.arm64-v8a\libCppDsl.so Plugins\Android\libs\arm64-v8a\libCppDsl.so

cmake -S . -B build.Android.x86 -DANDROID=1 -DCMAKE_ANDROID_ARCH_ABI=x86 -DCMAKE_MAKE_PROGRAM=%ANDROID_NINJA% -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_VERSION=23 -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_GENERATOR="Ninja"
cd build.Android.x86
%ANDROID_NINJA%
cd ..
md Plugins\Android\libs\x86\
copy /Y build.Android.x86\libCppDsl.so Plugins\Android\libs\x86\libCppDsl.so
