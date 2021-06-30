#include "logic.h"

Bpb bpb;
ext2_super_block super_block;

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
    printf("Blocs grup: %d\n", info.s_blocks_per_group);
    printf("Frags grup: %d\n", info.s_clusters_per_group);

    printf("\nINFO VOLUM\n");
    printf("Nom volum: %s\n", info.s_volume_name);
    printf("Ultima comprov: %s", timestamp_to_date(info.s_lastcheck));
    printf("Ultim muntatge: %s", timestamp_to_date(info.s_mtime));
    printf("Ultima escriptura: %s", timestamp_to_date(info.s_wtime));
}



void getExt2Info(int fd){

  lseek(fd,(1024+0), SEEK_SET);
  read(fd, &(super_block.s_inodes_count), sizeof(unsigned int));
  read(fd, &(super_block.s_blocks_count), sizeof(unsigned int));
  read(fd, &(super_block.s_r_blocks_count), sizeof(unsigned int));
  read(fd, &(super_block.s_free_blocks_count), sizeof(unsigned int));
  read(fd, &(super_block.s_free_inodes_count), sizeof(unsigned int));
  read(fd, &(super_block.s_first_data_block), sizeof(unsigned int));
  read(fd, &(super_block.s_log_block_size), sizeof(unsigned int));

  lseek(fd, (1024+32), SEEK_SET);
  read(fd, &(super_block.s_blocks_per_group), sizeof(unsigned int));
  read(fd, &(super_block.s_clusters_per_group), sizeof(unsigned int));
  read(fd, &(super_block.s_inodes_per_group), sizeof(unsigned int));

  lseek(fd, (1024+48), SEEK_SET);
  read(fd, &(super_block.s_wtime),	sizeof(unsigned int));

  lseek(fd, (1024+64),	SEEK_SET);
  read(fd, &(super_block.s_lastcheck),	sizeof(unsigned int));

  lseek(fd, (1024+44),SEEK_SET);
  read(fd, &(super_block.s_mtime),	sizeof(unsigned int));

  lseek(fd, (1024+84),	SEEK_SET);
  read(fd, &(super_block.s_first_ino), sizeof(unsigned int));
  read(fd, &(super_block.s_inode_size),	sizeof(unsigned int));

  lseek(fd, (1024+120), SEEK_SET);
  read(fd, &(super_block.s_volume_name), 16 );
  super_block.s_log_block_size =  1024 << super_block.s_log_block_size;

}

/*****************************************************
*
* Function analyzes EXT2 files
* Args: fd = file descriptor
* Return: 1 if file_type == ext2 else 0
*
*****************************************************/
int analyzeEXT2(int fd, int mode){
  

  lseek(fd, (off_t) 1024, SEEK_SET);
  read(fd, &super_block, sizeof(ext2_super_block));

  if (super_block.s_magic == EXT2_SUPER_MAGIC) {
    if (mode == 0){
      getExt2Info(fd);
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

void findFAT16(int fd, char *filename, int mode, int offset_directory){
  
 
  int FirstRootDirSecNum = 0;
  FirstRootDirSecNum = (bpb.BPB_RsvdSecCnt * bpb.BPB_BytesPerSec) + (bpb.BPB_NumFATs * bpb.BPB_FATSz16 * bpb.BPB_BytesPerSec) + offset_directory;
  char name[8];
  int size;
  int found = 0;
  unsigned char atribute = 0;
  for (int i = 0; i < bpb.BPB_RootEntCnt; i++){
    
    pread(fd, &name, 8, FirstRootDirSecNum);
    if (strcmp(name,"") != 0){
      printf("Names:-%s-%s-\n", name, filename);
    }
    if (strcmp(filename,name) == 0){
      if (mode == 1){
        unsigned char delete_flag = (unsigned char) 0xE5;
        lseek(fd, FirstRootDirSecNum, SEEK_SET);
        write(fd,&delete_flag,1);
        printf(FILE_DELETED, filename);
      } else {
        int aux = FirstRootDirSecNum+29;
        pread(fd, &size, 4, aux);
        printf(FILE_FOUND, size);
        
      }
      found = 1;
      break;
    }
    
    pread(fd, &atribute, 1, FirstRootDirSecNum+11);
    
    //Si es directorio buscamos dentro
    if((atribute & 0x10) == 0x10 && found == 0 && strcmp(name,"") != 0){
      int offset;
      pread(fd, &offset, 2, FirstRootDirSecNum+26);
      printf("Directori: %s\n", name);
      printf("Offset: %d\n", offset);
      findFAT16(fd, filename, 0, offset+1); 
      printf("\nAcaba directorio\n");           
    }
    
    FirstRootDirSecNum += 32;
  }
  
  if(found == 0){
    printf(FILE_NOT_FOUND);
  }

 
}



unsigned long searchInodeAddress(int fd, ext2_super_block super_block, int n_inode){
    unsigned long address;
    unsigned long n_block = (unsigned long) n_inode / super_block.s_inodes_per_group;
    n_inode= n_inode - (super_block.s_inodes_per_group * n_block);

    //unsigned long block_size = super_block.s_blocks_per_group * super_block.s_log_block_size;
    unsigned long block_size = super_block.s_blocks_per_group * 1024;
    unsigned long group_table_position = 0;
    unsigned long table_position = 0;
    unsigned long inode_position = 0;
    
    //group_table_position = super_block.s_log_block_size * (super_block.s_first_data_block + 1);
    group_table_position = 1024 * (super_block.s_first_data_block + 1);

    lseek(fd, group_table_position + 8, SEEK_SET);
    read(fd, &table_position, 4);

    //inode_position = table_position * super_block.s_log_block_size;
    
    inode_position = table_position * 1024;
    
    address = (block_size * n_block) + inode_position + (n_inode - 1) * super_block.s_inode_size;
    return address;
}

Inode getInode(int fd, unsigned long address){
    Inode inode;
    lseek(fd, address, SEEK_SET);
    read(fd, &inode.i_mode, 2);
    read(fd, &inode.i_uid, 2);
    read(fd, &inode.i_size, 4);
    read(fd, &inode.i_atime, 4);
    read(fd, &inode.i_ctime, 4);
    read(fd, &inode.i_mtime, 4);
    read(fd, &inode.i_dtime, 4);
    read(fd, &inode.i_gid, 2);
    read(fd, &inode.i_links_count, 2);
    read(fd, &inode.i_blocks, 4);
    read(fd, &inode.i_flags, 4);
    read(fd, &inode.i_osd1, 4);

    
    for(int i = 0; i < 15; i++) {
      inode.i_block[i] = 0;
      read(fd, &inode.i_block[i], 4);
    }
    
    read(fd, &inode.i_generation, 4);
    read(fd, &inode.i_file_acl, 4);
    read(fd, &inode.i_dir_acl, 4);
    read(fd, &inode.i_faddr, 4);
    read(fd, &inode.i_osd2, 12);

    return inode;
}

DirectoryEntry getDE(int fd, unsigned long data_block_pos){

    DirectoryEntry directory;

    lseek(fd, data_block_pos, SEEK_SET);
    read(fd, &directory.inode, sizeof(uint32_t));
    read(fd, &directory.rec_len, sizeof(uint16_t));
    read(fd, &directory.name_len, sizeof(uint8_t));
    read(fd, &directory.file_type, sizeof(uint8_t));
    read(fd, &directory.name, directory.name_len);
    //Reset lseek
    lseek(fd, data_block_pos, SEEK_SET);

    return directory;
}

/*****************************************************
*
* Function find a file in EXT2
* Args: fd = file descriptor
* Return: void
*
*****************************************************/

void findEXT2(int fd, char *filename, int mode){
  
	int found = 0;
  unsigned long address = searchInodeAddress(fd, super_block, 1) + 128;
  
  unsigned long total_block = 0;
  unsigned long address_directory = 0;
  

	Inode inode = getInode(fd, address);
  Inode aux;
	DirectoryEntry directory_entry;

	for (int i=0; i<15; i++ ) {
		if ( inode.i_block[i] == 0 ) {
      break;
		}
		address_directory = inode.i_block[i] * 1024;
		do {
			directory_entry = getDE(fd, address_directory);

			if ( directory_entry.inode != 0) {
          printf("-%s-", directory_entry.name);
  				if ( strcmp(directory_entry.name, filename) == 0 ) {

            aux = getInode(fd, searchInodeAddress(fd, super_block, directory_entry.inode));
            printf("\n");
            printf(FILE_FOUND, aux.i_size);
            found = 1;
            break;

  				}
        
			}

			address_directory += directory_entry.rec_len;
			total_block  += directory_entry.rec_len;

		} while (total_block < 1024);
	}

  printf("%d", mode);
  if(found == 0){
    printf(FILE_NOT_FOUND);
  }

 
}
