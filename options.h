typedef struct options{
    int opts_c;
    int opts_x;
    int opts_t;
}opts;

opts get_options(char *o);                          //for finding which options
char *getOptions(int argc, char *argv[]);           //for list of options
