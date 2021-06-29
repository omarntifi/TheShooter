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
#define VOLUME_NOT_FORMAT "Error. Volum no formatat en FAT16 ni EXT2."

void info_op(int fd, int mode){
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
  }
}

void find_op(int fd){
  info_op(fd,1);
}

int main(int argc, char *argv[])
{
    
    int fd;
    int info = -1, find = -1;
    
    if (argc != 4)
    {
        printf(ERROR_ARGS);
        return -1;
    }
    
    info = strcmp(argv[1], "/info");
    find = strcmp(argv[1], "/find");
    
    if (info == 0 || find == 0)
    {
        fd = open(argv[2], O_RDONLY);

        if (fd < 0)
        {  
          printf(ERROR_FILE_FIND);
          return 1;
        }
        
        if (info == 0){
          info_op(fd, 0);
        } else if (find == 0){
          find_op(fd);
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