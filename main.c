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
#include "bitfilecreation.h"
#include "extract.h"
#include <dirent.h>
#include <errno.h>

//Function to find out whether path entered is a file or folder
int is_regular_file(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char *argv[]){

    /*If number of arguments less than 3
    First arg - ./tar , second arg - to create/extract/list , third arg - file or folder name*/
    if(argc < 3){
        printf("Please enter a specific option");
        return 0;
    }

    else{

        /*-c to create, -x to extract, -t to list, -d to decode a file*/
        char *options = getOptions(argc, argv);
        if(options){

            opts selected_option = get_options(options);

            if(selected_option.opts_c && !selected_option.opts_t && !selected_option.opts_x && !selected_option.opts_d){
                printf("Create file option activated!\n");

                if(is_regular_file(argv[2])){
                    printf("This is a file\n");
                    char *filename = getFileNameFromPath(argv[2]);

                    char *bitfilename;
                    bitfilename = (char *)malloc(sizeof(char)*20);
                    int i;
                    for(i=0; i<strlen(filename);i++){
                        if(filename[i] != '.')
                            bitfilename[i] = filename[i];
                        else
                            break;
                    }

                    //printf("%s\n",filename);
                    copyingfiles(argv[2], filename);
                    bitfilecreation(bitfilename, filename);
                    remove(filename);
                }

                else{

                    DIR* dir = opendir(argv[2]);

                    if (dir) {
                        /* Directory exists. */
                        printf("This is a folder\n");
                        // char *filename = getFileNameFromPath(argv[2]);
                        // printf("%s\n",filename);
                        listOFDirectoryFiles(argv[2]);
                        closedir(dir);
                    } else if (ENOENT == errno) {
                        printf("This path does not exist!\n");
                        return 0;
                        /* Directory does not exist. */
                    } else {
                        /* opendir() failed for some other reason. */
                        printf("Error!\n");
                        return 0;
                    }
                    
                }
            }

            else if(selected_option.opts_t && !selected_option.opts_c && !selected_option.opts_x && !selected_option.opts_d){
                printf("List of files in tar file option activated!\n");
                if(is_regular_file(argv[2])){
                    char *tar = getFileNameFromPath(argv[2]);
                    int i;
                    
                    for(i = 0; i<strlen(tar);i++){
                        if(tar[i] == '.'){
                            break;
                        }
                    }
                    //printf("%ld--%d",strlen(tar),i+6);
                    if(tar[i-2]!='_'&& tar[i+1]=='t' && tar[i+2]=='a' && tar[i+3]=='r' && (i+4)==strlen(tar)){
                        printf("This is not a compressed tar file\n");
                        listofFilesinArchive(tar);
                    }
                    else if(tar[i-2]=='_' && tar[i-1]=='c' && tar[i+1]=='t' && tar[i+2]=='a' && tar[i+3]=='r' && (i+4)==strlen(tar)){
                        printf("This is a compressed tar file\n");
                        listofFilesinArchive(tar);
                    }
                    else{
                        printf("Please enter a tar file");
                        return 0;
                    }
                }
                else{
                    printf("This is not a file\n");
                }
            }

            else if(selected_option.opts_x && !selected_option.opts_c && !selected_option.opts_t && !selected_option.opts_d){
                printf("Extract files option activated!\n");
                if(is_regular_file(argv[2])){
                    char *tar = getFileNameFromPath(argv[2]);
                    int i;
                    for(i = 0; i<strlen(tar);i++){
                        if(tar[i] == '.'){
                            break;
                        }
                    }
                    if(tar[i-2]!='_'&& tar[i+1]=='t' && tar[i+2]=='a' && tar[i+3]=='r' && (i+4)==strlen(tar)){
                        printf("This is not a compressed tar file\n");
                        extractFilesFromArchive(tar,0);
                    }
                    else if(tar[i-2]=='_' && tar[i-1]=='c' && tar[i+1]=='t' && tar[i+2]=='a' && tar[i+3]=='r' && (i+4)==strlen(tar)){
                        printf("This is a compressed tar file\n");
                        char **l = extractFilesFromArchive(tar,1);
                        int i = 0;
                        while(l[i][0]!='\0'){
                            decodingfn(l[i]);
                            //printf("%s--\n",l[i]);
                            i+=1;
                        }
                    }
                    else{
                        printf("Please enter a tar file");
                        return 0;
                    }
                }
                else{
                    printf("This is not a file\n");
                }
            }

            else if(!selected_option.opts_x && !selected_option.opts_c && !selected_option.opts_t && selected_option.opts_d){
                printf("Decoding option activated!\n");
                if(is_regular_file(argv[2])){
                    char *d = getFileNameFromPath(argv[2]);
                    decodingfn(d);
                }
                else{
                    printf("No such file exists!");
                }

            }

            else{
                printf("Only one option can be specified at a time\n");
            }
        }

        else{
            printf("Please specify options!");
            return 0;
        }
    }

    return 0;
}