@echo off

if not exist ..\build\ mkdir ..\build\

pushd %~dp0\..\build\
cmake .. -DNOX_BUILD_EXAMPLE=ON
popd
pause
