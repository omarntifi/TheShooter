//
// Created by Omar Ntifi Matarín on 13/04/2021.

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h> 
#include "logic/logic.h"


#define ERROR_ARGS "Error. Nombre de parametres incorrecte.\n"
#define ERROR_FILE_FIND "Error. Volum no trobat.\n"
#define ERROR_OPERATION "El programa no soporta aquesta operacio.\nOperacions disponibles:\n1./info\n2./find\n"
#define FILE_NOT_IN_DOMAIN "Sistema d arxius no es ni EXT2 ni FAT16.\n"
#define VOLUME_NOT_FORMAT "Error. Volum no formatat en FAT16 ni EXT2.\n"

int info_op(int fd, int mode){
  int is_fat16 = 0, is_ext2 = 0;
  
  is_fat16 = analyzeFAT16(fd, mode);
        
  if(is_fat16 != 1){
    is_ext2 = analyzeEXT2(fd, mode);
  }
  
  if (is_fat16 == 0 && is_ext2 == 0) {
    if (mode == 0){
      printf(FILE_NOT_IN_DOMAIN);
    } else {
      printf(VOLUME_NOT_FORMAT);
    }
  } else if (is_fat16 == 1){
    //TYPE FAT16 FIND
    return 1;
  } else {
    //TYPE EXT2 FIND
    return 2;  
  }
  return 0;
}

void find_op(int fd, char *filename){
  int type_system = 0;
  type_system = info_op(fd,1);
  
  if (type_system == 1){
    findFAT16(fd, filename, 0);
   ;
  } else if(type_system == 2){
    //TODO: find en ext2
    findEXT2(fd, filename, 0);
  }
  
}

void delete_op(int fd, char *filename){
  int type_system = 0;
  type_system = info_op(fd,1);
  
  if (type_system == 1){
    findFAT16(fd, filename, 1);
   ;
  } else if(type_system == 2){
    //TODO: find en ext2
  }
  
}

int main(int argc, char *argv[])
{
    
    int fd;
    int info = -1, find = -1, deletef = -1;
    
    if (argc != 4)
    {
        printf(ERROR_ARGS);
        return -1;
    }
    
    info = strcmp(argv[1], "/info");
    find = strcmp(argv[1], "/find");
    deletef = strcmp(argv[1], "/delete");
    
    if (info == 0 || find == 0 || deletef == 0)
    {
        fd = open(argv[2], O_RDWR);

        if (fd < 0)
        {  
          printf(ERROR_FILE_FIND);
          return 1;
        }
        
        if (info == 0){
          info_op(fd, 0);
        } else if (find == 0){
          find_op(fd, argv[3]);
        } else if (deletef == 0){
          delete_op(fd, argv[3]);
        }
        
        
        close(fd);
        
    }
    
    else
    {
        printf(ERROR_OPERATION);
        return -1;
    }

    return 0;
}