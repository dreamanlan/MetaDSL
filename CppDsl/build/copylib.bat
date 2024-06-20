rem working directory

set workdir=%~dp0
cd %workdir%

xcopy /Y/S Plugins\* ..\lib\*

xcopy /Y/S ..\lib\* ..\..\..\..\UGit\ScriptableUnreal\Plugins\Brace\Source\Brace\lib\*
xcopy /Y/S ..\lib\* ..\..\..\suyu\externals\brace\lib\*

xcopy /Y/S ..\include\* ..\..\..\..\UGit\ScriptableUnreal\Plugins\Brace\Source\Brace\Private\include\*
xcopy /Y/S ..\include\* ..\..\..\suyu\externals\brace\include\*

