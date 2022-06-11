#include <stdlib.h>

typedef struct node{
    int len, off;
    int parent;
    int left, right;
}node;

typedef node *bt;

struct ret{
    int off, len;
};

void createTree(int size, bt* binaryarray);
void destroyTree(struct node *tree);
void insert(struct node *tree, int *root, unsigned char *window, int off, int len, int max);
struct ret find(struct node *tree, int root, unsigned char *window, int index, int size);
void updateOffset(struct node *tree, int n, int max);
