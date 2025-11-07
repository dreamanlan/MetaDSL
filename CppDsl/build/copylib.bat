rem working directory

set workdir=%~dp0
cd %workdir%

xcopy /Y/S Plugins\* ..\lib\*

xcopy /Y/S ..\lib\* E:\UGit\ScriptableUnreal\Plugins\Myself\MyPluginRuntime\Source\Brace\lib\*
xcopy /Y/S ..\lib\* ..\..\..\myuzu\externals\brace\lib\*

xcopy /Y/S ..\include\* E:\UGit\ScriptableUnreal\Plugins\Myself\MyPluginRuntime\Source\Brace\Private\include\*
xcopy /Y/S ..\include\* ..\..\..\myuzu\externals\brace\include\*

