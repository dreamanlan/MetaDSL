for /f %%a in ('dir /a:d /b %ANDROID_SDK%\cmake\') do set cmake_version=%%a
set cmake_bin=%ANDROID_SDK%\cmake\%cmake_version%\bin\cmake.exe
set ninja_bin=%ANDROID_SDK%\cmake\%cmake_version%\bin\ninja.exe

mkdir build_v7a
%cmake_bin% -H.\ -B.\build_v7a "-GAndroid Gradle - Ninja" -DANDROID=1 -DANDROID_ABI=armeabi-v7a -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=%ninja_bin% -DANDROID_NATIVE_API_LEVEL=23 -DCMAKE_TOOLCHAIN_FILE=.\cmake\android.windows.toolchain.cmake "-DCMAKE_CXX_FLAGS=-std=c++11 -fexceptions"
%ninja_bin% -C .\build_v7a
mkdir .\Plugins\Android\Libs\armeabi-v7a
move .\build_v7a\libCppDsl.so .\Plugins\Android\Libs\armeabi-v7a\libCppDsl.so


mkdir build_android_x86
%cmake_bin% -H.\ -B.\build_android_x86 "-GAndroid Gradle - Ninja" -DANDROID=1 -DANDROID_ABI=x86 -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=%ninja_bin% -DANDROID_NATIVE_API_LEVEL=23 -DCMAKE_TOOLCHAIN_FILE=.\cmake\android.windows.toolchain.cmake "-DCMAKE_CXX_FLAGS=-std=c++11 -fexceptions"
%ninja_bin% -C .\build_android_x86
mkdir .\Plugins\Android\Libs\x86
move .\build_android_x86\libCppDsl.so .\Plugins\Android\Libs\x86\libCppDsl.so


mkdir build_v8a
%cmake_bin% -H.\ -B.\build_v8a "-GAndroid Gradle - Ninja" -DANDROID=1 -DANDROID_ABI=arm64-v8a -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=%ninja_bin% -DANDROID_NATIVE_API_LEVEL=23 -DCMAKE_TOOLCHAIN_FILE=.\cmake\android.windows.toolchain.cmake "-DCMAKE_CXX_FLAGS=-std=c++11 -fexceptions"
%ninja_bin% -C .\build_v8a
mkdir .\Plugins\Android\Libs\arm64-v8a
move .\build_v8a\libCppDsl.so .\Plugins\Android\Libs\arm64-v8a\libCppDsl.so

rmdir /s /q build_v7a
rmdir /s /q build_android_x86
rmdir /s /q build_v8a

echo "compile success"
pause