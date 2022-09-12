#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int ping[2], pong[2];
    pipe(ping);
    pipe(pong);

    char buffer[5];

    int pid = fork();

    if (pid == 0) // children
    {
        // receive the msg
        close(pong[1]);
        read(pong[0], buffer, 5);
        fprintf(1, "%d: received ping\n", getpid());
        close(pong[0]);

        // send the msg
        close(ping[0]);
        write(ping[1], "pong\n", 5);
        close(ping[1]);
    }
    else // parent
    {
        // send the msg
        close(ping[0]);
        write(ping[1], "ping\n", 5);
        close(ping[1]);

        // receive the msg
        close(pong[1]);
        read(pong[0], buffer, 5);
        close(pong[0]);

        wait(&pid);
        fprintf(1, "%d: received pong\n", getpid());
    }

    exit(0);
}