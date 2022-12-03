@echo on

copy /y DslLib\bin\Debug\Dsl.dll ..\BatchCommand\deps\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.pdb ..\BatchCommand\deps\Dsl.pdb

copy /y DslLib\bin\Debug\Dsl.dll ..\Cs2Dsl\dep\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.pdb ..\Cs2Dsl\dep\Dsl.pdb

copy /y DslLib\bin\Debug\Dsl.dll ..\Cs2Lua\dep\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.pdb ..\Cs2Lua\dep\Dsl.pdb

rem copy /y DslLib\bin\Debug\Dsl.dll ..\Cs2LuaRewriter\dep\Dsl.dll
rem copy /y DslLib\bin\Debug\Dsl.pdb ..\Cs2LuaRewriter\dep\Dsl.pdb

rem copy /y DslLib\bin\Debug\Dsl.dll ..\CSharpHookRewriter\dep\Dsl.dll
rem copy /y DslLib\bin\Debug\Dsl.pdb ..\CSharpHookRewriter\dep\Dsl.pdb

rem copy /y DslLib\bin\Debug\Dsl.dll ..\UnusedClass\dep\Dsl.dll
rem copy /y DslLib\bin\Debug\Dsl.pdb ..\UnusedClass\dep\Dsl.pdb

rem copy /y DslLib\bin\Debug\Dsl.dll ..\ScriptInterpreterByDsl\deps\Dsl.dll
rem copy /y DslLib\bin\Debug\Dsl.pdb ..\ScriptInterpreterByDsl\deps\Dsl.pdb

rem copy /y DslLib\bin\Debug\Dsl.dll ..\mallochook\dep\Dsl.dll
rem copy /y DslLib\bin\Debug\Dsl.pdb ..\mallochook\dep\Dsl.pdb

copy /y DslLib\bin\Debug\Dsl.dll ..\DotnetPatch\dep\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.pdb ..\DotnetPatch\dep\Dsl.pdb

copy /y DslLib\bin\Debug\Dsl.dll ..\CSharpGameFramework\ExternalLibrary\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.pdb ..\CSharpGameFramework\ExternalLibrary\Dsl.pdb

copy /y DslLib\bin\Debug\Dsl.dll ..\GameDemo\GameLibrary\ExternLibrary\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.pdb ..\GameDemo\GameLibrary\ExternLibrary\Dsl.pdb

copy /y DslLib\bin\Debug\Dsl.dll ..\BatchCommandApp\Assets\Plugins\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.dll ..\CSharpGameFramework\Unity3d\Assets\Plugins\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.dll ..\GameDemo\Unity3dProject\Assets\Plugins\game\Dsl.dll
copy /y DslLib\bin\Debug\Dsl.dll ..\UnityProjForProfiler\Assets\Plugins\Dsl.dll

rem copy /y DslLib\bin\Debug\Dsl.dll ..\TerrainGenByDsl\Assets\Plugins\Dsl.dll

@pause
