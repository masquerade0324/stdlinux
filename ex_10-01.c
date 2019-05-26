#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

static void do_ls_rec(char *path);

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        fprintf(stderr, "%s: no arguments\n", argv[0]);
        exit(1);
    }

    for (i = 1; i < argc; i++) {
        do_ls_rec(argv[i]);
    }

    exit(0);
}

static void do_ls_rec(char *path)
{
    DIR *d;
    struct dirent *ent;
    struct stat st;
    char child[1024];

    d = opendir(path);
    if (!d) {
        perror(path);
        exit(1);
    }

    while (ent = readdir(d)) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

        sprintf(child, "%s/%s", path, ent->d_name);

        if (lstat(child, &st) < 0) {
            perror(child);
            exit(1);
        }

        if (!S_ISLNK(st.st_mode) && S_ISDIR(st.st_mode)) {
            do_ls_rec(child);
        } else {
            printf("%s\n", ent->d_name);
        }
    }
    closedir(d);
}