#include "logic.h"


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

int analyzeFAT16(int fd){
  unsigned char *fileInfo = malloc(512);
  read(fd, fileInfo, 512);

  unsigned char *aux = malloc(32);
  int j = 0;
  for (int i = 35; i < 61; i++){
    aux[j] = fileInfo[i];
    j++;
  }

  Bs bs;
  memcpy(&(bs), aux, sizeof(Bs));
  Bpb bpb;
    
  //CHECK FAT TYPE IS FAT16
  if (strstr(bs.BS_FilSysType, "FAT16") != NULL ){   
    memcpy(&(bpb), fileInfo, sizeof(Bpb));  
    printFat16(bpb, bs);
    return 1;
  }
  
  return 0;
}

/*****************************************************
*
* Function analyzes EXT2 files
* Args: fd = file descriptor
* Return: 1 if file_type == ext2 else 0
*
*****************************************************/
int analyzeEXT2(int fd){
  printf("%d", fd);
  return 0;
}
