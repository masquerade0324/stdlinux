#include <stdio.h>
#include <stdlib.h>

static int count_line(FILE *f);

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        exit(1);
    } else {
        int i;
        for (i = 1; i < argc; i++) {
            FILE *f = fopen(argv[i], "r");
            if (!f) {
                exit(1);
            }
            int cnt = count_line(f);
            printf("number of lines: %d\n", cnt);
            fclose(f);
        }
    }
    return 0;
}

static int count_line(FILE *f)
{
    int cnt = 0;
    int flg = 0;
    int c;

    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            flg = 1;
            cnt++;
        } else {
            flg = 0;
        }
    }

    if (!flg) {
        cnt++;
    }

    return cnt;
}
