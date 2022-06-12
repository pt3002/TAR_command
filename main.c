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

        /*-c to create, -x to extract, -t to list*/
        char *options = getOptions(argc, argv);
        if(options){

            opts selected_option = get_options(options);

            if(selected_option.opts_c && !selected_option.opts_t && !selected_option.opts_x){
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
                }

                else{
                    printf("This is a folder\n");
                    // char *filename = getFileNameFromPath(argv[2]);
                    // printf("%s\n",filename);
                    listOFDirectoryFiles(argv[2]);
                }
            }

            else if(selected_option.opts_t && !selected_option.opts_c && !selected_option.opts_x){
                printf("List files in tar file option activated!\n");
                char *tar = getFileNameFromPath(argv[2]);
                int i;
                for(i = 0; i<strlen(tar);i++){
                    if(tar[i] == '.'){
                        break;
                    }
                }
                if(tar[i+1]=='t' && tar[i+2]=='a' && tar[i+3]=='r'){
                    listofFilesinArchive(tar);
                }
                else{
                    printf("Please enter a tar file");
                    return 0;
                }
            }

            else if(selected_option.opts_x && !selected_option.opts_c && !selected_option.opts_t){
                printf("Extract files option activated!\n");
                char *tar = getFileNameFromPath(argv[2]);
                int i;
                for(i = 0; i<strlen(tar);i++){
                    if(tar[i] == '.'){
                        break;
                    }
                }
                if(tar[i+1]=='t' && tar[i+2]=='a' && tar[i+3]=='r'){
                    extractFilesFromArchive(tar);
                }
                else{
                    printf("Please enter a tar file");
                    return 0;
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