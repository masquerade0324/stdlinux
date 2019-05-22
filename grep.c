#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#define _GNU_SOURCE
#include <getopt.h>

static void do_grep(regex_t *pat, FILE *src, int v_opt);

int main(int argc, char *argv[])
{
    regex_t pat;
    int err;
    int i;
    int opt;
    int i_opt = 0;
    int v_opt = 0;

    while ((opt = getopt(argc, argv, "iv")) != -1) {
        switch (opt) {
        case 'i':
            i_opt = 1;
            break;
        case 'v':
            v_opt = 1;
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-i] [-v] [FILE ...]\n", argv[0]);
            exit(1);
        }
    }

    argc -= optind;
    argv += optind;

    if (argc < 1) {
        fputs("no pattern\n", stderr);
        exit(1);
    }

    if (i_opt) {
        err = regcomp(&pat, argv[0], REG_EXTENDED | REG_NOSUB | REG_NEWLINE | REG_ICASE);
    } else {
        err = regcomp(&pat, argv[0], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
    }

    if (err != 0) {
        char buf[1024];

        regerror(err, &pat, buf, sizeof buf);
        puts("buf");
    }

    if (argc == 1) {
        do_grep(&pat, stdin, v_opt);
    } else {
        for (i = 1; i < argc; i++) {
            FILE *f;

            f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                exit(1);
            }
            do_grep(&pat, f, v_opt);
            fclose(f);
        }
    }
    regfree(&pat);

    exit (0);
}

static void do_grep(regex_t *pat, FILE *src, int v_opt)
{
    char buf[4096];

    if (!v_opt) {
        while (fgets(buf, sizeof buf, src)) {
            if (regexec(pat, buf, 0, NULL, 0) == 0) {
                fputs(buf, stdout);
            }
        }
    } else {
        while (fgets(buf, sizeof buf, src)) {
            if (regexec(pat, buf, 0, NULL, 0) != 0) {
                fputs(buf, stdout);
            }
        }
    }
}