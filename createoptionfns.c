#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "createoptionfns.h"
#include "bitfilecreation.h"

void copyingfiles(char *source_file,char *filename){
    char ch;
    FILE *source;

    FILE *target;
    target  = fopen (filename, "w+");
    //printf("------------%s---%s\n",filename,source_file);

    source = fopen(source_file, "r");
     
    while( ( ch = fgetc(source) ) != EOF )
        fputc(ch, target);
     
    printf("File copied successfully.\n");
     
    fclose(source);
    fclose(target);
}

char* getFileNameFromPath(char* path){
    if(path == NULL){
        return NULL;
    }
    char* filename = NULL;
    int i;
    for(i = 0; i<strlen(path);i++){
        if(path[i]=='/'){
            int j;
            int temp = 0;
            for(j = i+1; j<strlen(path);j++){
                if(path[j]=='/'){
                    temp = 1;
                    break;
                }
            }
            if(temp == 0){
                int c = 0;
                filename = (char *)malloc(sizeof(char)*(strlen(path)-i));
                for(j = i+1; j<strlen(path); j++){
                    filename[c] = path[j];
                    //printf("%c",path[j]);
                    c+=1;
                }
                return filename;
            }
        }
    }
    if(filename == NULL){
        printf("INVALID");
        return NULL;
    }
    return NULL;
}

void listOFDirectoryFiles(char *path){

    DIR* d;
    struct dirent *dir;
    //DESKTOP - /home/prerna2002/Desktop
    d = opendir(path);
    char *directory = getFileNameFromPath(path);
    //printf("%s\n",directory);
    char *tarfilename;
    char *compressed_tarfile;
    compressed_tarfile = (char *)malloc(sizeof(char)*(strlen(directory)+6));
    tarfilename = (char *)malloc(sizeof(char)*(strlen(directory)+4));
    memcpy(tarfilename,directory,strlen(directory));
    memcpy(compressed_tarfile,directory,strlen(directory));
    int i = strlen(directory);
    tarfilename[i] = '.';
    tarfilename[i+1] = 't';
    tarfilename[i+2] = 'a';
    tarfilename[i+3] = 'r';

    compressed_tarfile[i] = '_';
    compressed_tarfile[i+1] = 'c';
    compressed_tarfile[i+2] = '.';
    compressed_tarfile[i+3] = 't';
    compressed_tarfile[i+4] = 'a';
    compressed_tarfile[i+5] = 'r';
    printf("%s\n",compressed_tarfile);

    //CREATING NEW TAR FILE
    FILE *fp;
    fp  = fopen (tarfilename, "w+");
    FILE *fpc;
    fpc = fopen(compressed_tarfile,"w+");
    //printf("Directory - %s\n",dirname);
    //printf("\n");
    if(d){
        while((dir=readdir(d)) != NULL){
            //printf("%s\n",dir->d_name);
            if(dir->d_name[0]!='.'){
                char *currentfile = (char *)malloc(sizeof(char)*(strlen(path)+strlen(dir->d_name)+1));
                memcpy(currentfile, path,strlen(path));
                currentfile[strlen(path)] = '/';
                int i;
                int c = strlen(path)+1;
                for(i = 0; i<strlen(dir->d_name);i++){
                    currentfile[c] = dir->d_name[i];
                    c+=1;
                }
                //printf("%s\n",currentfile);
                copyingfiles(currentfile,dir->d_name);
                char *bitfilename;
                bitfilename = (char *)malloc(sizeof(char)*20);
                for(i=0; i<strlen(dir->d_name);i++){
                    if(dir->d_name[i] != '.')
                        bitfilename[i] = dir->d_name[i];
                    else
                        break;
                }
                //printf("%s\n",bitfilename);
                bitfilecreation(bitfilename,dir->d_name);
                addToTar(fpc,bitfilename);
                addToTar(fp,dir->d_name);
                remove(dir->d_name);
                remove(bitfilename);
                free(bitfilename);
                free(currentfile);
            }
        }
        closedir(d);
    }

    if(d == NULL){
        printf("INVALID INPUT");
        fclose(fpc);
        fclose(fp);
        return;
    }
    fclose(fpc);
    fclose(fp);
    return;
}

void addToTar(FILE *tarFile, char *file){
    FILE *new = fopen(file, "rb");                //open the new file for reading
    if(new == NULL){
        printf("No such file in directory");
        return;
    }

    fseek(tarFile, 0L, SEEK_END);           //size of tar file
    long int lengthoftarfile = ftell(tarFile); 

    int startHeader = ftell(tarFile);

    /*copying content of new file at the end of tar file*/
    int contentstart = lengthoftarfile + 512;

    fseek(tarFile, contentstart, SEEK_SET);                    //setting pointer at end of file

    copyFile(new, tarFile, file);

    lengthoftarfile = ftell(tarFile);

    int contentend = lengthoftarfile - contentstart;            //Length of newly inserted content

    /*Adding header before the newly added content in tne 512 bytes space*/
    struct tarHeader head;
    
    /*memset - used to fill a block of memory with a particular value. eg. void *memset(void *ptr, int x, size_t n);*/
    memset(&head, 0 , sizeof( struct tarHeader));

    getHeaderStats(&head, file, contentend);
    fseek(tarFile, startHeader, SEEK_SET);
    fwrite(&head, 1, sizeof(struct tarHeader), tarFile);

    fclose(new);

}

void getHeaderStats (struct tarHeader *head, char *file, int contentend) {
    struct stat stats;
    stat(file, &stats);
    snprintf( head->name, 100, "%s", file );
    snprintf( head->size, 12, "%d", contentend );
    snprintf( head->mtime, 12, "%ld ", stats.st_mtime );
    snprintf( head->mode, 8, "%o ", stats.st_mode );
}

void copyFile(FILE *new, FILE *tarFile, char *file){
    /*
    STAT functions return information about a file, in the buffer pointed to by statbuf.
    */

    struct stat stats;
    stat(file, &stats);
    char *buffer = malloc(sizeof(char));
    while( !feof(new) ){
        buffer = (char*)malloc(stats.st_size * sizeof(char));
        size_t read = fread( buffer, 1, stats.st_size, new );
        fwrite( buffer, 1, read, tarFile);
    }
    free(buffer);
}