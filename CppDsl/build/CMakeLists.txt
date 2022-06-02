
# For MetaDSL cpp proj.

cmake_minimum_required(VERSION 3.6)

if ( WIN32 AND NOT CYGWIN AND NOT ( CMAKE_SYSTEM_NAME STREQUAL "WindowsStore" ) AND NOT ANDROID)
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MD" CACHE STRING "")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MDd" CACHE STRING "")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD" CACHE STRING "")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd" CACHE STRING "")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /Od /EHs")
    add_compile_options(/std:c++17)
    add_compile_definitions(__WINDOWS__ _CRT_SECURE_NO_WARNINGS FULL_VERSION)
elseif (ANDROID)
    add_compile_options(-std=c++1y -fwritable-strings)
    add_compile_definitions(__LINUX__ _CRT_SECURE_NO_WARNINGS FULL_VERSION)
else ()
    add_compile_options(-std=c++1y -fwritable-strings)
    add_compile_definitions(__LINUX__ _CRT_SECURE_NO_WARNINGS FULL_VERSION)
endif ()

message(${CMAKE_CURRENT_SOURCE_DIR})

project(CppDsl)

if (APPLE)
    if ( IOS )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fembed-bitcode")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fembed-bitcode")
    else ()
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -undefined dynamic_lookup")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
    endif ()
endif ()

set (CLIB_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(${CLIB_SRC_PATH}
    ${CLIB_SRC_PATH}/Common
    ${CLIB_SRC_PATH}/Parser
    ${CLIB_SRC_PATH}/BraceScript
    ${CLIB_SRC_PATH}/deps/include
)

set (CLIB_SRC
    ${CLIB_SRC_PATH}/Dsl.h
    ${CLIB_SRC_PATH}/Dsl.cpp
    ${CLIB_SRC_PATH}/DslCommon.h
    ${CLIB_SRC_PATH}/DslData.h
    ${CLIB_SRC_PATH}/DslData.cpp
    ${CLIB_SRC_PATH}/DslParser.h
    ${CLIB_SRC_PATH}/DslParser.cpp
    ${CLIB_SRC_PATH}/DslUtility.h
    ${CLIB_SRC_PATH}/DslUtility.cpp
    ${CLIB_SRC_PATH}/main.cpp
	${CLIB_SRC_PATH}/Common/BaseType.h
	${CLIB_SRC_PATH}/Common/Delegation.h
	${CLIB_SRC_PATH}/Common/Queue.h
	${CLIB_SRC_PATH}/Common/StaticCheck.h
	${CLIB_SRC_PATH}/Common/StringFormat.h
	${CLIB_SRC_PATH}/Common/StringFormat.cpp
	${CLIB_SRC_PATH}/Common/tsnprintf.h
	${CLIB_SRC_PATH}/Parser/ByteCode.h
	${CLIB_SRC_PATH}/Parser/ByteCode.inl
	${CLIB_SRC_PATH}/Parser/ByteCode.cpp
	${CLIB_SRC_PATH}/Parser/RuntimeBuilderData.h
	${CLIB_SRC_PATH}/Parser/RuntimeBuilderData.cpp
	${CLIB_SRC_PATH}/Parser/SlkAction.h
	${CLIB_SRC_PATH}/Parser/SlkAction.cpp
	${CLIB_SRC_PATH}/Parser/SlkConstants.h
	${CLIB_SRC_PATH}/Parser/SlkError.h
	${CLIB_SRC_PATH}/Parser/SlkError.cpp
	${CLIB_SRC_PATH}/Parser/SlkInc.h
	${CLIB_SRC_PATH}/Parser/SlkParse.h
	${CLIB_SRC_PATH}/Parser/SlkParse.cpp
	${CLIB_SRC_PATH}/Parser/SlkString.h
	${CLIB_SRC_PATH}/Parser/SlkString.cpp
	${CLIB_SRC_PATH}/Parser/SlkTerminals.h
	${CLIB_SRC_PATH}/Parser/SlkToken.h
	${CLIB_SRC_PATH}/Parser/SlkToken.cpp
	${CLIB_SRC_PATH}/Parser/SourceCodeScript.h
	${CLIB_SRC_PATH}/Parser/SourceCodeScript.cpp
	${CLIB_SRC_PATH}/BraceScript/BraceScript.h
	${CLIB_SRC_PATH}/BraceScript/BraceScript.cpp
	${CLIB_SRC_PATH}/BraceScript/BraceCoroutine.h
	${CLIB_SRC_PATH}/BraceScript/BraceCoroutine.cpp
	${CLIB_SRC_PATH}/BraceScript/SimpleCoroutine.h
	${CLIB_SRC_PATH}/BraceScript/SimpleCoroutine.cpp
	${CLIB_SRC_PATH}/BraceScript/ShareStackCoroutine.h
	${CLIB_SRC_PATH}/BraceScript/ShareStackCoroutine.cpp
)

if (APPLE)
    if (IOS)
        set (DEPS_LIB_PATH ${CLIB_SRC_PATH}/deps/lib/iOS)
    else ()
        set (DEPS_LIB_PATH ${CLIB_SRC_PATH}/deps/lib)
    endif ()
elseif ( WIN32 AND NOT CYGWIN)
    if (CMAKE_SIZEOF_VOID_P EQUAL 64)
        set (DEPS_LIB_PATH ${CLIB_SRC_PATH}/deps/lib/x86_64)
    else ()
        set (DEPS_LIB_PATH ${CLIB_SRC_PATH}/deps/lib/x86)
    endif ()
else ()
    set (DEPS_LIB_PATH ${CLIB_SRC_PATH}/deps/lib/Android)
endif ()
    
link_directories(${CLIB_SRC_PATH}/lib
    ${DEPS_LIB_PATH}
)

set (THIRDPART_LIB
    boost_context
)

if (APPLE)
    if (IOS)
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
        add_library(CppDsl STATIC
            ${CLIB_SRC}
        )
		set_xcode_property (CppDsl IPHONEOS_DEPLOYMENT_TARGET "7.0" "all")
    else ()
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_64_BIT)")
        if (NOT BUILD_AS_OSX_DYLIB)
            add_library(CppDsl MODULE
                ${CLIB_SRC}
            )
            set_target_properties ( CppDsl PROPERTIES BUNDLE TRUE )
            #set_target_properties ( CppDsl PROPERTIES FRAMEWORK TRUE )
            #set_target_properties ( CppDsl PROPERTIES MACOSX_RPATH TRUE )
        else ()
            add_library(CppDsl SHARED
                ${CLIB_SRC}
            )
        endif ()
    endif ()
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Switch")
    add_library(CppDsl STATIC
        ${CLIB_SRC}
    )
    target_compile_options(CppDsl PRIVATE -m64 -mcpu=cortex-a57+fp+simd+crypto+crc -fno-common -fno-short-enums -ffunction-sections -fdata-sections -fPIC -fms-extensions)
elseif ( WIN32 AND NOT CYGWIN OR ANDROID )
    add_library(CppDsl STATIC
        ${CLIB_SRC}
    )
else ( )
    add_library(CppDsl SHARED
        ${CLIB_SRC}
    )
endif ( )

if(UINT_ESPECIALLY)
    ADD_DEFINITIONS(-DUINT_ESPECIALLY)
endif()
	
if ( WIN32 AND NOT CYGWIN )
    target_link_libraries(CppDsl
        ws2_32
        ${THIRDPART_LIB} 
    )
elseif (APPLE AND NOT IOS)
    target_link_libraries(CppDsl
        m
        ${THIRDPART_LIB} 
    )
else ( )
    target_link_libraries(CppDsl
        m
        ${THIRDPART_LIB} 
    )
endif ( )
