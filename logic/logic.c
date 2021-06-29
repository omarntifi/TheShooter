#include "logic.h"

Bpb bpb;

/*****************************************************
*
* Function print FAT16 info
* Args: bpb, bs
* Return: void
*
*****************************************************/

void printFat16(Bpb fat, Bs bs){
    printf(FILE_SYSTEM_INFO);
    printf("Filesystem: %s\n", bs.BS_FilSysType);
    printf("SystemName: %s\n", fat.BS_OEMName);
    printf("Mida del sector: %d\n", fat.BPB_BytesPerSec);
    printf("Sectors Per Cluster: %d\n", fat.BPB_SecPerClus);
    printf("Sectors reservats: %d\n", fat.BPB_RsvdSecCnt);
    printf("Numero de FATs: %d\n", fat.BPB_NumFATs);
    printf("MaxRootEntries: %d\n", fat.BPB_RootEntCnt);
    printf("Sectors per FAT: %d\n", fat.BPB_TotSec16);
    printf("Label: %s\n\n", bs.BS_VolLab);
}


/*****************************************************
*
* Function analyzes FAT16 files
* Args: fd = file descriptor
* Return: 1 if file_type == fat16 else 0
*
*****************************************************/

int analyzeFAT16(int fd, int mode){
  
  Bs bs;
  pread(fd, bs.BS_VolLab, 11, 43);
  pread(fd, bs.BS_FilSysType, 8, 54);
  //CHECK FAT TYPE IS FAT16
  if (strstr(bs.BS_FilSysType, "FAT16") != NULL ){   
    pread(fd, &(bpb.BPB_BytesPerSec), 2, 11);
    pread(fd, &(bpb.BPB_SecPerClus), 1, 13);
    pread(fd, &(bpb.BPB_RsvdSecCnt), 2, 14);
    pread(fd, &(bpb.BPB_NumFATs), 1, 16);
    pread(fd, &(bpb.BPB_RootEntCnt), 2, 17);
    pread(fd, &(bpb.BPB_TotSec16), 2, 19);
    pread(fd, &(bpb.BPB_Media), 1, 21);
    pread(fd, &(bpb.BPB_FATSz16), 2, 22);
    pread(fd, &(bpb.BS_OEMName), 6, 3);
    if (mode == 0){
      printFat16(bpb, bs);
    }
    return 1;
  }
  
  return 0;
}


char *timestamp_to_date(time_t rawtime) {
  struct tm * timeinfo;
  timeinfo = localtime (&rawtime);
  return asctime(timeinfo);
}


/*****************************************************
*
* Function print Ext2 info
* Args: ext2_super_block
* Return: void
*
*****************************************************/

void printExt2(ext2_super_block info){
    printf(FILE_SYSTEM_INFO);
    printf("Filesystem: %s\n", "EXT2");
    printf("\nINFO INODE\n");
    printf("Mida Inode: %d\n", info.s_inode_size);
    printf("Num Inodes: %d\n", info.s_inodes_count);
    printf("Primer Inode: %d\n", info.s_first_ino);
    printf("Inodes Grup: %d\n", info.s_inodes_per_group);
    printf("Inodes Lliures: %d\n", info.s_free_inodes_count);

    printf("\nINFO BLOC\n");
    printf("Mida Bloc: %d\n", info.s_log_block_size);
    printf("Blocs Reservats: %d\n", info.s_r_blocks_count);
    printf("Blocs Lliures: %d\n", info.s_free_blocks_count);
    printf("Total Blocs: %d\n", info.s_blocks_count);
    printf("Primer Bloc: %d\n", info.s_first_data_block);
    printf("Blocs grup: %d\n", info.s_block_group_nr);
    printf("Frags grup: %d\n", info.s_clusters_per_group);

    printf("\nINFO VOLUM\n");
    printf("Nom volum: %s\n", info.s_volume_name);
    printf("Ultima comprov: %s", timestamp_to_date(info.s_lastcheck));
    printf("Ultim muntatge: %s", timestamp_to_date(info.s_mtime));
    printf("Ultima escriptura: %s", timestamp_to_date(info.s_wtime));
}



/*****************************************************
*
* Function analyzes EXT2 files
* Args: fd = file descriptor
* Return: 1 if file_type == ext2 else 0
*
*****************************************************/
int analyzeEXT2(int fd, int mode){
  ext2_super_block super_block;

  lseek(fd, (off_t) 1024, SEEK_SET);
  read(fd, &super_block, sizeof(ext2_super_block));

  if (super_block.s_magic == EXT2_SUPER_MAGIC) {
    if (mode == 0){
      printExt2(super_block);
    }
    return 1;
  }
    
  return 0;
}

/*****************************************************
*
* Function find a file in FAT16
* Args: fd = file descriptor
* Return: void
*
*****************************************************/

void findFAT16(int fd, char *filename){
  
 
  int FirstRootDirSecNum = 0;
  FirstRootDirSecNum = (bpb.BPB_RsvdSecCnt * bpb.BPB_BytesPerSec) + (bpb.BPB_NumFATs * bpb.BPB_FATSz16 * bpb.BPB_BytesPerSec);
  char name[8];
  char size;
  for (int i = 0; i < bpb.BPB_RootEntCnt; i++){
    
    pread(fd, &name, 8, FirstRootDirSecNum);
    
    if (strcmp(filename,name) == 0){
      pread(fd, &size, 1, FirstRootDirSecNum+11);
      printf(FILE_FOUND, 457);
    }
    FirstRootDirSecNum += 32;
  }
  
  

  
  

 
}
