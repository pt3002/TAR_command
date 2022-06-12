#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "options.h"
#include "createoptionfns.h"
#include "bitio.h"
#include "lz77.h"

void bitfilecreation(char *bitfilename, char *filename){

    int la_size = -1, sb_size = -1; /* default size */

    FILE *b;
    b = fopen(bitfilename,"w");
    fclose(b);
    //printf("%s\n",bitfilename);
    FILE *file = NULL;
    struct bitFILE *bitF = NULL;
    file = fopen(filename, "rb");
    bitF = bitIO_open(bitfilename, BIT_IO_W);
    encode(file, bitF, la_size, sb_size);
    fclose(file);
    bitIO_close(bitF);    
}