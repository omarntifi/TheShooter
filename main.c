//
// Created by Omar Ntifi Matarín on 13/04/2021.

#include <stdio.h>
#include <string.h>
#include <fcntl.h>



#define ERROR_ARGS "El nombre d'arguments es incorrecte.\nHas d'introduir <operacio> i <nom_volum> al executar."
#define ERROR_FILE "El fitxer no existeix o no s'ha pogut obrir."
#define ERROR_OPERATION "El programa no soporta aquesta operacio.\nOperacions disponibles:\n1./info"

int main(int argc, char *argv[])
{
   
    int fd;

    if (argc != 3)
    {
        printf(ERROR_ARGS);
        return -1;
    }
    
    if (strcmp(argv[1], "/info") == 0)
    {
        fd = open(argv[2], O_RDONLY);

        if (fd < 0)
        {
            printf(ERROR_FILE);
            return 1;
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