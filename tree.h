
#ifndef tree_h
#define tree_h
struct node;

struct ret{
    int off, len;
};
struct node *createTree(int size);
void destroyTree(struct node *tree);
void insert(struct node *tree, int *root, unsigned char *window, int off, int len, int max);
struct ret find(struct node *tree, int root, unsigned char *window, int index, int size);
void delete(struct node *tree, int *root, unsigned char *window, int abs_sb, int max);
void updateOffset(struct node *tree, int n, int max);
void printtree(struct node *tree, int root);
#endif
