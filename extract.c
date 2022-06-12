#include "extract.h"
#include "bitio.h"
#include "lz77.h"
#include "bitfilecreation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sizeOfFile(FILE *fp, long int offset){
    char fileSize[12];
    
    long int fileSizeOffset = offset + 124;
    //printf("%ld-----offset\n",fileSizeOffset);
    int size;
    fseek(fp, fileSizeOffset, SEEK_SET);
    if(fread(fileSize, 1, 12, fp)){
        //printf("%s\n",fileSize);
        size = atoi(fileSize);
        return size;
    }
    else{
        printf("Error in reading file");
    }
    return 0;
    
}

void listofFilesinArchive(char *tar){
    FILE *fp = fopen(tar, "rb");                 //reading mode for non text files

    if(fp == NULL){
        printf("Cannot open tar file");
        return;
    }

    /*
        Syntax of fseek -> int fseek(FILE *stream, long int offset, int pos)
        SEEK_CUR - current position, SEEK_END - end of the file, SEEK_SET - beginning
    */

   fseek(fp, 0L, SEEK_END);
   long int lengthoftarfile = ftell(fp);                  //Length of tar file

   char sub[100];               //subparts of tar file
   int fileSize;
   long int offset = 0;

   while(offset < lengthoftarfile){
       fileSize = sizeOfFile(fp, offset);
       fseek(fp, offset, SEEK_SET);
       if(fread(sub, 1, 100, fp)){
            printf("%s\n", sub);
            offset = offset + 512 + fileSize;
       }  
       else{
            printf("Error");
       } 
       
   }
   fclose(fp);
}

char** extractFilesFromArchive(char *tarFile,int var) {

    char **l = (char **) malloc(10 * sizeof(char*));
    int i;
    for (int i =0 ; i < 10; ++i)
        l[i] = (char *) malloc(20 * sizeof(char));
    i = 0;

    FILE *fp = fopen(tarFile, "rb");

    fseek(fp, 0L, SEEK_END);
    long int lenOfTarFile = ftell(fp); /*Length of tar file*/

    if (fp == NULL) {
        printf("can not open tar file!");
        return NULL;
    }

    char *name;
    name = NULL;
    name = (char *)malloc(sizeof(char)*(100));
    int fileSize;
    long int offset = 0;

    while (offset < lenOfTarFile) {

        FILE *file;

        fileSize = sizeOfFile(fp, offset); /*Find a size of current file*/

        fseek(fp, offset, SEEK_SET); /*Point to position that we need*/
        if(fread(name, 1, 100, fp)){
            file = fopen(name, "wb");
            //printf("%s",name);
            memcpy(l[i], name,strlen(name));
            i+=1;

            /*Add content to a new file*/

            fseek(fp, offset + 512, SEEK_SET); /*point to the begining of content */

            char *buffer = (char*)malloc(fileSize * sizeof(char*) + 1);

            size_t bytes = fread( buffer, 1, fileSize, fp );
            fwrite( buffer, 1, bytes, file);

            free(buffer);
            free(name);
            fclose(file);
            //remove(file);
            offset = offset + 512 + fileSize; /*Offset to the next file in tar file*/
        }
        else{
            printf("Error in reading file");
        }

        

    }

    return l;
    fclose(fp);
}
