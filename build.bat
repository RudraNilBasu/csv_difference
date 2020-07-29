@echo off

set CommonCompilerFlags=-D_CRT_SECURE_NO_WARNINGS -DRAY_WIN32=1 -MTd -nologo  /fp:fast -Gm- -GR- -EHa- -O2 -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4456 -wd4459 -wd4505 -FC -Z7
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib opengl32.lib

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\build

cl %CommonCompilerFlags% ..\single_file_lib\csv_reader.cpp /link %CommonLinkerFlags%
set LastError=%ERRORLEVEL%
popd

IF NOT %LastError%==0 GOTO :end

:end
