void encode(FILE *file, struct bitFILE *out, int la, int sb);

struct token{
    int off, len;
    char next;
};

void writecode(struct token t, struct bitFILE *out, int la_size, int sb_size);

