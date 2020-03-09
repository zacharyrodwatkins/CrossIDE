:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: CrossIde support batch file for C51
::
@echo off
:: NOTE: Modify 'ToolDir', 'Bin', and 'Include' below to reflect your installation.
:: WARNING: This names are case sensitive for crosside
set ToolDir=c:\source\call51
set Bin=c:\source\call51\bin
set Inc=c:\source\call51\include
set COpt= --use-stdout
set LOpt= %COpt%
set OOpt=obj

if "%1"=="cc" goto docc
if "%1"=="ld" goto dold
echo Don't know what to do with %1
goto end

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Compile a C file with c51
::
:docc
echo %2.c:1: Compiling
%Bin%\c51 %LOpt% -c %2.c
if errorlevel 1 goto c51error
goto end
:c51error
::This error message is used by crosside to prevent linking
echo **** "%2" has errors! ****
goto end

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Link object files and libraries using call51
::
:dold
set tgt=%2
echo %tgt%.hex:1: Linking to...
::Read the possible large number of object files
set obj=
:getobj1
shift
if "%2"=="" goto done1
set obj=%obj% %2
goto getobj1
:done1
::
:: The linker
::echo %Bin%\c51 %COpt% %LOpt% %obj%
%Bin%\c51 %COpt% %LOpt% %obj%
echo Crosside_Action Set_Hex_File %tgt%.hex
echo Done!
goto end

:end

set CodeLoc=
set ToolDir=
set Bin=
set Inc=
set COpt=
set LOpt=
set OOpt=