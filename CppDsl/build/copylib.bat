rem working directory

set workdir=%~dp0
cd %workdir%

xcopy /Y/S Plugins\* ..\lib\*

xcopy /Y/S ..\lib\* ..\..\..\..\UGit\ScriptableUnreal\Plugins\Brace\Source\Brace\lib\*

xcopy /Y/S ..\lib\* ..\..\..\..\SVN\CurBranch\Plugins\Durer\Source\CppDsl\lib\*
