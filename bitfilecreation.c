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
    return;
}

void bitfileextraction(char *bitfilename, char *filename){
    FILE *file = NULL;
    struct bitFILE *bitF = NULL;
    file = fopen(filename, "w");
    bitF = bitIO_open(bitfilename, BIT_IO_R);
    decode(bitF, file);
    fclose(file);
    bitIO_close(bitF);
    return;
}

void decodingfn(char *d){
    char *out = NULL;
    out = (char *)malloc(sizeof(char)*(strlen(d)+4));
    int i=strlen(d);
    memcpy(out,d,strlen(d));
    out[i] = '.';
    out[i+1] = 't';
    out[i+2] = 'x';
    out[i+3] = 't';
    out[i+4] = '\0';
    printf("File successfully decoded in %s\n",out);
    FILE *filename;
    filename = fopen(out,"w+");
    struct bitFILE *bitF = NULL;
    bitF = bitIO_open(d, BIT_IO_R);
    decode(bitF,filename);
    bitIO_close(bitF);
    free(out);
    fclose(filename);
    return;
}