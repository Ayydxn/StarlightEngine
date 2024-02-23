@echo off

echo Generating Visual Studio projects files...

call Engine\ThirdParty\Premake\Windows\premake5.exe vs2022
PAUSE