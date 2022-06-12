#include <stdlib.h>
#include <stdio.h>

void listofFilesinArchive(char *tar);
int sizeOfFile(FILE *fp, long int offset);
char ** extractFilesFromArchive(char *tarFile, int var);