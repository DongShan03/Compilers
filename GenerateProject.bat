@echo off
call premake5 gmake2
cd build
make clean
make -j10
cd Debug
Compilers.exe
