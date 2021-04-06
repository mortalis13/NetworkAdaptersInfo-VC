@echo off
path=%path%;c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin
call "c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"

cl ipconf.cpp Iphlpapi.lib ws2_32.lib
echo.
echo.

ipconf.exe
