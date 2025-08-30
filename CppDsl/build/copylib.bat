rem working directory

set workdir=%~dp0
cd %workdir%

xcopy /Y/S Plugins\* ..\lib\*

xcopy /Y/S ..\lib\* e:\UGit\ScriptableUnreal\Plugins\Brace\Source\Brace\lib\*
xcopy /Y/S ..\lib\* ..\..\..\myuzu\externals\brace\lib\*

xcopy /Y/S ..\include\* e:\UGit\ScriptableUnreal\Plugins\Brace\Source\Brace\Private\include\*
xcopy /Y/S ..\include\* ..\..\..\myuzu\externals\brace\include\*

