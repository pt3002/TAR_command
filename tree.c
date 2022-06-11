#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void createTree(int size, bt *binaryarray)
{
    bt tree = calloc(size, sizeof(node));
    *binaryarray = tree;
    return;
}

void destroyTree(bt tree)
{
    free(tree);
}

void insert(bt tree, int *root, unsigned char *window, int abs_off, int len, int max)
{
    int i, tmp;
    int off = abs_off % max;    /* from absolute index to relative index (array) */
    
    if (*root == -1){
        *root = off;
        tree[*root].parent = -1;
    }else{
        i = *root;
        
        while (1){
            tmp = i;
            if (memcmp(&(window[abs_off]), &(window[tree[i].off]), len) < 0){
                /* go to the left child */
                i = tree[i].left;
                if (i == -1){
                    /* set parent-child relation */
                    tree[tmp].left = off;
                    tree[off].parent = tmp;
                    
                    break;
                }
            }else{
                /* go to the right child */
                i = tree[i].right;
                if (i == -1){
                    /* set parent-child relation */
                    tree[tmp].right = off;
                    tree[off].parent = tmp;
                
                    break;
                }
            }
        }
    }
    
    /* set other parameters */
    tree[off].off = abs_off;
    tree[off].len = len;
    tree[off].left = -1;
    tree[off].right = -1;
    
}


struct ret find(bt tree, int root, unsigned char *window, int index, int size)
{
    /* variables */
    int i, j;
    struct ret off_len;
    
    /* initialize as non-match values */
    off_len.off = 0;
    off_len.len = 0;
    
    if (root == -1)
        return off_len;
    j = root;
    
    /* flow the tree finding the longest match node */
    while (1){
        
        /* look for how many characters are equal between the lookahead and the node */
        for (i = 0; window[index+i] == window[tree[j].off + i] && i < size-1; i++){}
        
        /* if the new match is better than the previous one, save the values */
        if (i > off_len.len){
            off_len.off = index - tree[j].off;
            off_len.len = i;
        }
        
        if (window[index+i] < window[tree[j].off + i] && tree[j].left != -1)
            j = tree[j].left;
        else if (window[index+i] > window[tree[j].off + i] && tree[j].right != -1)
            j = tree[j].right;
        else break;
    }
    
    return off_len;
}

void updateOffset(bt tree, int n, int max)
{
    int i;
    
    for (i = 0; i < max; i++){
        if (tree[i].off != -1)
            tree[i].off -= n;
    }
}
