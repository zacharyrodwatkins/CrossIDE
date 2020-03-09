//  at89lp6440 bootloader
//  Copyright (c) 2008-2014 Jesus Calvino-Fraga
//  ~C51~  --acall-ajmp --code-loc 0xfe00 --code-size 0x200
//  Always make sure that this bootloader fits in 512 bytes

#include <at89lp6440.h>
#include <stdio.h>

#define BOOT_START 0xfe00
code unsigned char ID_STR[]="001E64FF";
#define BUFFER_SIZE 64
#define PAGE_SIZE 128

#define CLK 22118400L
#define PUSHBUTTON P4_5

#include "BootLP.c"

