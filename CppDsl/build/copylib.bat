rem working directory

set workdir=%~dp0
cd %workdir%

xcopy /Y/S Plugins\* ..\lib\*

xcopy /Y/S ..\lib\* ..\..\..\..\UGit\ScriptableUnreal\CppDsl\lib\*

xcopy /Y/S ..\lib\* ..\..\..\..\SVN\NB2_trunk\CppDsl\lib\*
