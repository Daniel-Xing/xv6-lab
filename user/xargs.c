#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

void run(int argc, char *argv[])
{
    int pid = fork();

    if (pid == 0)
    {
        exec(argv[0], argv);
        exit(0);
    }
    else
    {
        wait(&pid);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("xargs: args should be more than one!");
        exit(1);
    }

    char buf[MAXARG], p;
    char *newArgv[argc + 1];
    for (int j = 0; j < argc - 1; j++)
    {
        newArgv[j] = argv[j + 1];
    }
    newArgv[argc - 1] = buf;

    int i;
    i = 0;

    while (read(0, &p, 1) == sizeof(char))
    {
        if (p == '\n')
        {
            // run cmd
            buf[i] = '\0';
#ifdef DEBUG
            for (int i = 0; i < argc; i++)
            {
                printf("new args in %s \n", newArgv[i]);
            }

            printf("end. \n");
#endif

            run(argc, newArgv);

            i = 0;
            continue;
        }

        buf[i] = p;
        i++;
    }

    exit(0);
}