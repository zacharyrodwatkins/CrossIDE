set bin=..\..\bin
cd src
del ..\large\*.lib
set CALL51_CC=%bin%\c51 --use-stdout --model-large -c
%bin%\lib51 -l ..\large\libfloat.lib ..\libfloat.l51
%bin%\lib51 -l ..\large\libint.lib ..\libint.l51
%bin%\lib51 -l ..\large\liblong.lib ..\liblong.l51
%bin%\lib51 -l ..\large\libc51.lib ..\libc51.l51
set CALL51_CC=%bin%\c51 --use-stdout --model-large -DUSE_FLOATS -c
%bin%\lib51 -l ..\large\libc51f.lib ..\libc51.l51

set CALL51_CC=
set bin=
del *.asm *.lst *.obj
cd ..
