//  at89lp828 bootloader
//  Copyright (c) 2008-2012 Jesus Calvino-Fraga
//  ~C51~  --acall-ajmp --code-loc 0x1e00 --code-size 0x200
//  Always make sure that this bootloader fits in 512 bytes

#include <at89lp828.h>

#define BOOT_START 0x1e00
code unsigned char ID_STR[]="001E42FF";
#define BUFFER_SIZE 64
#define PAGE_SIZE 64

#include "BootLP.c"
