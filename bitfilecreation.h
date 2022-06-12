#define MIN_LA_SIZE 2       /* min lookahead size */
#define MAX_LA_SIZE 255     /* max lookahead size */
#define MIN_SB_SIZE 0       /* min search buffer size */
#define MAX_SB_SIZE 65535   /* max search buffer size */

void bitfilecreation(char *bitfilename, char *filename);
void bitfileextraction(char *bitfilename, char *filename);