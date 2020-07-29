@echo off

REM  ctime -begin ray.ctm
C:\Users\rudra\Downloads\handmade_hero_source\handmade_hero_601_source\handmade_hero_day_601_source\ctime\ctime -begin ray.ctm

set CommonCompilerFlags=-D_CRT_SECURE_NO_WARNINGS -DRAY_WIN32=1 -MTd -nologo  /fp:fast -Gm- -GR- -EHa- -O2 -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4456 -wd4459 -wd4505 -FC -Z7
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib opengl32.lib

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\build

cl %CommonCompilerFlags% ..\single_file_lib\csv_reader.cpp /link %CommonLinkerFlags%
set LastError=%ERRORLEVEL%
popd

C:\Users\rudra\Downloads\handmade_hero_source\handmade_hero_601_source\handmade_hero_day_601_source\ctime\ctime -end ray.ctm %LastError%
IF NOT %LastError%==0 GOTO :end

REM  TODO: ONLY DO THIS IF COMPILATION IS SUCCESSFUL!!!
REM  pushd data
REM  ..\..\build\ray.exe
REM  start test.bmp
REM  popd

:end
