IF EXIST W:\ray\ GOTO :launch_vim

subst w: d:\Projects
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

:launch_vim
@echo off
start "" /max "C:\Program Files (x86)\Vim\vim81\gvim.exe" w:\single_file_lib -c "source w:\vimrc_global"

