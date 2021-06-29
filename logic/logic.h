#ifndef _LOGIC_H
#define _LOGIC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>


#define FILE_SYSTEM_INFO "------ Filesystem Information ------\n\n"

typedef struct
{
	char BS_jmpBoot[3];
	char BS_OEMName[8];
	uint16_t BPB_BytesPerSec;
	uint8_t BPB_SecPerClus;
	uint16_t BPB_RsvdSecCnt;
	uint8_t BPB_NumFATs;
	uint16_t BPB_RootEntCnt;
	uint16_t BPB_TotSec16;
	uint8_t BPB_Media;
	uint16_t BPB_FATSz16;
	uint16_t BPB_SecPerTrk;
	uint16_t BPB_NumHeads;
	uint32_t BPB_HiddSec;
	uint32_t BPB_TotSec32;
} Bpb;

typedef struct
{
	uint8_t BS_DrvNum;
	uint8_t BS_Reserved1;
	uint8_t BS_BootSig;
	uint32_t BS_VolID;
	char BS_VolLab[11];
	char BS_FilSysType[8];
} Bs;

void printFat16(Bpb fat, Bs bs);
int analyzeFAT16(int fd);

int analyzeEXT2(int fd);

#endif