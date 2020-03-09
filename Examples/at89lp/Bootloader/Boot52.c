//  at89lp52 bootloader
//  Copyright (c) 2008-2012 Jesus Calvino-Fraga
//  ~C51~  --acall-ajmp --code-loc 0x1e00 --code-size 0x200
//  Always make sure that this bootloader fits in 512 bytes

#include <at89lp52.h>
#include <stdio.h>

#define BOOT_START 0x1e00
code unsigned char ID_STR[]="001E5406";
#define BUFFER_SIZE 64
#define PAGE_SIZE 128

#define CLK 22118400L
#define PUSHBUTTON PSEN

#include "BootLP.c"

