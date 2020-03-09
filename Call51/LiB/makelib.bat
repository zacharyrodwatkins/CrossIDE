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

del ..\medium\*.lib
set CALL51_CC=%bin%\c51 --use-stdout --model-medium -c
%bin%\lib51 -l ..\medium\libfloat.lib ..\libfloat.l51
%bin%\lib51 -l ..\medium\libint.lib ..\libint.l51
%bin%\lib51 -l ..\medium\liblong.lib ..\liblong.l51
%bin%\lib51 -l ..\medium\libc51.lib ..\libc51.l51
set CALL51_CC=%bin%\c51 --use-stdout --model-medium -DUSE_FLOATS -c
%bin%\lib51 -l ..\medium\libc51f.lib ..\libc51.l51

del ..\large\*.lib
set CALL51_CC=%bin%\c51 --use-stdout --model-large -c
%bin%\lib51 -l ..\large\libfloat.lib ..\libfloat.l51
%bin%\lib51 -l ..\large\libint.lib ..\libint.l51
%bin%\lib51 -l ..\large\liblong.lib ..\liblong.l51
%bin%\lib51 -l ..\large\libc51.lib ..\libc51.l51
set CALL51_CC=%bin%\c51 --use-stdout --model-large -DUSE_FLOATS -c
%bin%\lib51 -l ..\large\libc51f.lib ..\libc51.l51

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
