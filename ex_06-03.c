#include <stdio.h>
#include <stdlib.h>

#define SIZE  256
#define NMEMB 4

static void cat(FILE *f);

int main(int argc, char *argv[])
{
    if (argc == 1) {
        cat(stdin);
    } else {
        int i;
        for (i = 1; i < argc; i++) {
            FILE *f = fopen(argv[i], "r");
            if (!f) {
                exit(1);
            }
            cat(f);
            fclose(f);
        }
    }
    return 0;
}

static void cat(FILE *f)
{
    char buf[SIZE];
    size_t n;
    while ((n = fread(buf, 1, NMEMB, f)) == NMEMB) {
        fwrite(buf, 1, NMEMB, stdout);
    }

    if (ferror(f)) {
        exit(1);
    } else {
        fwrite(buf, 1, n, stdout);
    }
}
