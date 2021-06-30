#ifndef _LOGIC_H
#define _LOGIC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

#define FILE_SYSTEM_INFO "------ Filesystem Information ------\n\n"
#define EXT2_SUPER_MAGIC 0xEF53
#define EXT2_LABEL_LEN 16
#define EXT2_OFFSET 1024
#define FILE_FOUND "Fitxer trobat. Ocupa %d bytes.\n"
#define FILE_NOT_FOUND "Error. Fitxer no trobat.\n"
#define FILE_DELETED "El fitxer %s ha estat eliminat.\n"

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

typedef struct
{
	uint32_t s_inodes_count;			/* Inodes count */
	uint32_t s_blocks_count;			/* Blocks count */
	uint32_t s_r_blocks_count;			/* Reserved blocks count */
	uint32_t s_free_blocks_count;		/* Free blocks count */
	uint32_t s_free_inodes_count;		/* Free inodes count */
	uint32_t s_first_data_block;		/* First Data Block */
	uint32_t s_log_block_size;			/* Block size */
	uint32_t s_log_cluster_size;		/* Allocation cluster size */
	uint32_t s_blocks_per_group;		/* # Blocks per group */
	uint32_t s_clusters_per_group;		/* # Fragments per group */
	uint32_t s_inodes_per_group;		/* # Inodes per group */
	uint32_t s_mtime;					/* Mount time */
	uint32_t s_wtime;					/* Write time */
	uint16_t s_mnt_count;				/* Mount count */
	int16_t s_max_mnt_count;			/* Maximal mount count */
	uint16_t s_magic;					/* Magic signature */
	uint16_t s_state;					/* File system state */
	uint16_t s_errors;					/* Behaviour when detecting errors */
	uint16_t s_minor_rev_level;			/* minor revision level */
	uint32_t s_lastcheck;				/* time of last check */
	uint32_t s_checkinterval;			/* max. time between checks */
	uint32_t s_creator_os;				/* OS */
	uint32_t s_rev_level;				/* Revision level */
	uint16_t s_def_resuid;				/* Default uid for reserved blocks */
	uint16_t s_def_resgid;				/* Default gid for reserved blocks */
	uint32_t s_first_ino;				/* First non-reserved inode */
	uint16_t s_inode_size;				/* size of inode structure */
	uint16_t s_block_group_nr;			/* block group # of this superblock */
	uint32_t s_feature_compat;			/* compatible feature set */
	uint32_t s_feature_incompat;		/* incompatible feature set */
	uint32_t s_feature_ro_compat;		/* readonly-compatible feature set */
	uint8_t s_uuid[16];					/* 128-bit uuid for volume */
	char s_volume_name[EXT2_LABEL_LEN]; /* volume name */
	char s_last_mounted[64];			/* directory where last mounted */

} ext2_super_block;

typedef struct {
    uint16_t i_mode;
    uint16_t i_uid;
    uint32_t i_size;
    uint32_t i_atime;
    uint32_t i_ctime;
    uint32_t i_mtime;
    uint32_t i_dtime;
    uint16_t i_gid;
    uint16_t i_links_count;
    uint32_t i_blocks;
    uint32_t i_flags;
    uint32_t i_osd1;
    uint32_t i_block[15];
    uint32_t i_generation;
    uint32_t i_file_acl;
    uint32_t i_dir_acl;
    uint32_t i_faddr;
    unsigned long i_osd2;
} Inode;

typedef struct {
    uint32_t inode;
    uint16_t rec_len;
    uint8_t name_len;
    uint8_t file_type;
    char name[255];
} DirectoryEntry;


void printFat16(Bpb fat, Bs bs);
int analyzeFAT16(int fd, int mode);
char *timestamp_to_date(time_t rawtime);
void printExt2(ext2_super_block info);
int analyzeEXT2(int fd, int mode);
int findFAT16(int fd, char *filename, int mode, int offset_directory);
void findEXT2(int fd, char *filename, int mode);
#endif