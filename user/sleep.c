#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: sleep seconds...\n");
        exit(1);
    }

    int time;
    time = atoi(argv[1]);

#ifdef DEBUG
    fprintf(1, "sleep");
#endif

    sleep(time);

#ifdef DEBUG
    fprintf(1, "sleep end");
#endif

    exit(0);
}