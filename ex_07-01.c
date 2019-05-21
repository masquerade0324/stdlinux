#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void cat(FILE *f, int vis);

int main(int argc, char *argv[])
{
    int opt;
    int vis = 0; /* false */

    while ((opt = getopt(argc, argv, "v")) != -1) {
        switch (opt) {
        case 'v':
            vis = 1;
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-v] [FILE ...]\n", argv[0]);
            exit(1);
        }
    }

    argc -= optind;
    argv += optind;

    if (argc == 0) {
        cat(stdin, vis);
    } else {
        int i;

        for (i = 0; i < argc; i++) {
            FILE *f;

            f = fopen(argv[i],"r");
            if (!f) {
                exit(1);
            }
            cat(f, vis);
            fflush(f);
            fclose(f);
        }
    }
    return 0;
}

static void cat(FILE *f, int vis)
{
    int c;

    if (vis) {
        while ((c = fgetc(f)) != EOF) {
            if (c == '\t') {
                if (fputs("\\t", stdout) == EOF) exit(1);
            } else if (c == '\n') {
                if (fputs("$\n", stdout) == EOF) exit(1);
            } else {
                if (putchar(c) < 0) exit(1);
            }
        }
    } else {
        while ((c = fgetc(f)) != EOF) {
            if (putchar(c) < 0) exit(1);
        }
    }
}
