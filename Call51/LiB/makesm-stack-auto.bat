set bin=..\..\bin
cd src
del ..\small-stack-auto\*.lib
set CALL51_CC=%bin%\c51 --use-stdout --model-small --stack-auto -c
%bin%\lib51 -l ..\small-stack-auto\libfloat.lib ..\libfloat.l51
%bin%\lib51 -l ..\small-stack-auto\libint.lib ..\libint.l51
%bin%\lib51 -l ..\small-stack-auto\liblong.lib ..\liblong.l51
%bin%\lib51 -l ..\small-stack-auto\libc51.lib ..\libc51.l51
set CALL51_CC=%bin%\c51 --use-stdout --model-small --stack-auto -DUSE_FLOATS -c
%bin%\lib51 -l ..\small-stack-auto\libc51f.lib ..\libc51.l51

set CALL51_CC=
set bin=
del *.asm *.lst *.obj
cd ..
