set bin=..\..\bin
cd src
del ..\small\*.lib
set CALL51_CC=%bin%\c51 --use-stdout --model-small -c
%bin%\lib51 -l ..\small\libfloat.lib ..\libfloat.l51
%bin%\lib51 -l ..\small\libint.lib ..\libint.l51
%bin%\lib51 -l ..\small\liblong.lib ..\liblong.l51
%bin%\lib51 -l ..\small\libc51.lib ..\libc51.l51
set CALL51_CC=%bin%\c51 --use-stdout --model-small -DUSE_FLOATS -c
%bin%\lib51 -l ..\small\libc51f.lib ..\libc51.l51

set CALL51_CC=
set bin=
del *.asm *.lst *.obj
cd ..
