#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "createoptionfns.h"

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
    tarfilename = (char *)malloc(sizeof(char)*(strlen(directory)+4));
    memcpy(tarfilename,directory,strlen(directory));
    int i = strlen(directory);
    tarfilename[i] = '.';
    tarfilename[i+1] = 't';
    tarfilename[i+2] = 'a';
    tarfilename[i+3] = 'r';
    //printf("%s\n",tarfilename);

    //CREATING NEW TAR FILE
    FILE *fp;
    fp  = fopen (tarfilename, "w+");
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
                free(currentfile);
            }
        }
        closedir(d);
    }

    if(d == NULL){
        printf("INVALID INPUT");
    }
    fclose(fp);
    return;
}