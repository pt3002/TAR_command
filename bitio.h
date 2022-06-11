#define BIT_IO_W 0
#define BIT_IO_R 1

struct bitFILE;

int bitof(int n);
int bitIO_feof(struct bitFILE *bitF);
int bitIO_ferror(struct bitFILE *bitF);
struct bitFILE* bitIO_open(const char *path, int mode);
int bitIO_close(struct bitFILE *bitF);
int bitIO_write(struct bitFILE *bitF, void *info, int nbit);