#include <stdio.h>
#include <stdlib.h>

struct tarHeader{
    char name[100];
    char mode[8];
    char uid[8];
    char gid[8];                 //sum till here 124 therefore file size offset - 124
    char size[12];
    char mtime[12];
    char checksum[8];
    char linkflag[1];
    char linkname[100];
    char pad[255];
};

/*sum of all these is 512*/

char* getFileNameFromPath(char* path);
void listOFDirectoryFiles(char *path);
void copyingfiles(char *source_file,char *filename);
void addToTar(FILE *tarFile, char *file);
void getHeaderStats (struct tarHeader *head, char *file, int contentend);
void copyFile(FILE *new, FILE *tarFile, char *file);