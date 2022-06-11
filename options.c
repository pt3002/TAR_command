#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "options.h"

void init_options(opts *o){
    o -> opts_c = 0;
    o -> opts_t = 0;
    o -> opts_x = 0;
    // initialising all options to 0 i.e. false
}

char *getOptions(int argc, char *argv[]){
    char *optionsstring;
    int total = 0;   //Total length of all arguments
    int i;
    int n = 0;
    for(i=1; i < argc; i++){
        total += strlen(argv[i]);
    }

    //Mallocating size for options string
    optionsstring = (char *) malloc(total * sizeof(char));

    for(i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            int j;
            for(j = 0; j < strlen(argv[i]); j++){
                optionsstring[n] = argv[i][j];
                n++;
            }
        }
    }

    if(!optionsstring[0]){
        return NULL;
    }

    optionsstring[n] = '\0';
    return optionsstring;
}

opts get_options(char *o){
    opts options;
    init_options(&options);
    int i;
    for(i = 0; i < strlen(o); i ++){
        switch(o[i]){
            case 'c':
                options.opts_c = 1;
                break;
            case 't':
                options.opts_t = 1;
                break;
            case 'x':
                options.opts_x = 1;
                break;
        }
    }
    return options;
}
