#include <stdio.h>
#include <stdlib.h>

static void cat(FILE *f);

int main(int argc, char *argv[])
{
    if (argc == 1) {
        cat(stdin);
    } else {
        int i;
        for (i = 1; i < argc; i++) {
            FILE *f;
            if ((f = fopen(argv[i], "r")) == NULL) {
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
    int c;

    while ((c = fgetc(f)) != EOF) {
        if (c == '\t') {
            fputs("\\t", stdout);
        } else if (c == '\n') {
            fputs("$\n", stdout);
        } else {
            putchar(c);
        }
    }
}
