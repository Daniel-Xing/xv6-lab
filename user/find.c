#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int str_tail(char *path, char *pattern)
{
    char *l, *r;

    l = path + strlen(path);
    r = pattern + strlen(pattern);

    for (; l >= path && *l != '/';)
    {
        if (*l != *r)
            return -1;
        l--;
        r--;
    }

    if (r != pattern)
        return -1;

    return 0;

    // Find first character after last slash.
    // for (p = path + strlen(path); p >= path && *p != '/'; p--)
    //     ;
    // p++;

    // // Return blank-padded name.
    // if (strlen(p) >= DIRSIZ)
    //     return p;

    // memmove(buf, p, strlen(p));
    // memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));

    // return buf;
}

void find(char *path, char *patern, int isExist)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    //
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s \n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s \n", path);
        close(fd);
        return;
    }

    //
    strcpy(buf, path);

    switch (st.type)
    {
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("find: path too long\n");
            break;
        }

        p = buf + strlen(buf);
        *p++ = '/';

        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                continue;

            dprintf("DEBUG: de.name: %s \n", de.name);

            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;

            isExist = strcmp(de.name, patern);

            if (stat(buf, &st) < 0)
            {
                printf("ls: cannot stat %s\n", buf);
                continue;
            }

            find(buf, patern, isExist);
        }

        break;

    default:
        if (isExist != 0)
            break;

        printf("%s\n", buf);
        break;
    }

    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        exit(1);
    }

    find(argv[1], argv[2], -1);

    exit(0);
}