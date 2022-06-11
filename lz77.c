#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitio.h"
#include "tree.h"
#include "lz77.h"

#define DEFAULT_LA_SIZE 15      /* lookahead size */
#define DEFAULT_SB_SIZE 4095    /* search buffer size */
#define N 3
#define MAX_BIT_BUFFER 16
struct token match(bt tree, int root, unsigned char *window, int la, int la_size);

void encode(FILE *file, struct bitFILE *out, int la, int sb)
{
    /* variables */
    int i, root = -1;
    int eof;
    bt tree;
    struct token t;
    unsigned char *window;
    int la_size, sb_size = 0;    /* actual lookahead and search buffer size */
    int buff_size;
    int sb_index = 0, la_index = 0;
    int LA_SIZE, SB_SIZE, WINDOW_SIZE;
    
    LA_SIZE = (la == -1) ? DEFAULT_LA_SIZE : la;
    SB_SIZE = (sb == -1) ? DEFAULT_SB_SIZE : sb;
    WINDOW_SIZE = (SB_SIZE * N) + LA_SIZE;
    
    window = calloc(WINDOW_SIZE, sizeof(unsigned char));
    

    createTree(SB_SIZE, &tree);
    
    bitIO_write(out, &SB_SIZE, MAX_BIT_BUFFER);
    bitIO_write(out, &LA_SIZE, MAX_BIT_BUFFER);
    
    /* fill the lookahead with the first LA_SIZE bytes or until EOF is reached */
    buff_size = fread(window, 1, WINDOW_SIZE, file);
    if(ferror(file)) {
        printf("Error loading the data in the window.\n");
        return;
   	}
    
    eof = feof(file);
    
    /* set lookahead's size */
    la_size = (buff_size > LA_SIZE) ? LA_SIZE : buff_size;
    
	while(buff_size > 0){
		
        /* find the longest match of the lookahead in the tree*/
        t = match(tree, root, window, la_index, la_size);
        
        /* write the token in the output file */
        writecode(t, out, LA_SIZE, SB_SIZE);
        
        /* read as many bytes as matched in the previuos iteration */
        for(i = 0; i < t.len + 1; i++){
            
            
            sb_size++;
            
            insert(tree, &root, window, la_index, la_size, SB_SIZE);
            la_index++;
            
            if (eof == 0){
                /* scroll backward the buffer when it is almost full */
                if (sb_index == SB_SIZE * (N - 1)){
                    memmove(window, &(window[sb_index]), sb_size+la_size);
                    
                    updateOffset(tree, sb_index, SB_SIZE);
                    
                    sb_index = 0;
                    la_index = sb_size;
                    
                    buff_size += fread(&(window[sb_size+la_size]), 1, WINDOW_SIZE-(sb_size+la_size), file);
                    if(ferror(file)) {
                        printf("Error loading the data in the window.\n");
                        return;
                    }
                    eof = feof(file);
                }
            }
            
            buff_size--;
            /* case where we hit EOF before filling lookahead */
            la_size = (buff_size > LA_SIZE) ? LA_SIZE : buff_size;
        }
	}
    destroyTree(tree);
    free(window);
}

struct token match(struct node *tree, int root, unsigned char *window, int la, int la_size)
{
    /* variables */
    struct token t;
    struct ret r;
    
    /* find the longest match */
    r = find(tree, root, window, la, la_size);
    
    /* create the token */
    t.off = r.off;
    t.len = r.len;
    t.next = window[la+r.len];
    
    return t;
}

void writecode(struct token t, struct bitFILE *out, int la_size, int sb_size)
{
    bitIO_write(out, &t.off, bitof(sb_size));
    bitIO_write(out, &t.len, bitof(la_size));
    bitIO_write(out, &t.next, 8);
}
