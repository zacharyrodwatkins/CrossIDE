# Linux CrossIDE

For all y'all suckers trying to do CPEN 312 with a Linux machine, 
heres and installation of the CrossIDE assembly compiler with 
linux support. This was done on Ubuntu-18.04, but should work for other 
distros.

## Prerequisites

You need to have wine installed to run CrossIDE and the assembly compiler

```
sudo apt-get install wine64
```

You also need quartus installed, but y'all should have already done that. 

## Usage

You can use the CrossIDE text editor if you want, and can open up CrossIDE 
by just running 

```
wine CrossIDE.exe
```

The thing is that the built in options for build and flash won't work. You may as well use whatever text editor you like.
To compile or flash the FPGA you can use the functions in cross_ide.sh. 

```
source scripts/cross_ide.sh
hexcompile <assembly file>
flash  <compiled file>
``` 

If you want to use these all the time just add source scripts/cross_ide.sh to your
~/.bashrc
