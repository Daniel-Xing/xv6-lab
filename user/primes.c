
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

    int flow[2];
    pipe(flow);
    int flow2Child[2];
    pipe(flow2Child);

    int prime = 2;
    int number[33];
    memset(number, 0, sizeof(number));
    number[0] = -1;
    number[1] = -1;

    int pid = fork();

    if (pid != 0)
    {
        close(flow[0]);
        close(flow[1]);

        write(flow2Child[1], &number, sizeof(number));

        close(flow2Child[1]);
        wait(&pid);
    }
    else
    {
    start:
        // create a new flow to send the msg
        close(flow[0]);
        close(flow[1]);

        // switch flow pipe
        flow[0] = flow2Child[0];
        flow[1] = flow2Child[1];

        pipe(flow2Child);

        close(flow[1]);

        // read the number from parent
        read(flow[0], &number, sizeof(number));

        int nextPrime = prime;
        for (int i = prime + 1; i <= 32; i++)
        {
            if (number[i] == -1)
            {
                continue;
            }

            if (i % prime == 0)
            {
                number[i] = -1;
            }

            if (i % prime != 0 && nextPrime == prime)
            {
                nextPrime = i;
            }
        }

        fprintf(1, "prime %d \n", prime);

        if (nextPrime == prime)
        {
            close(flow[0]);
            close(flow2Child[1]);
            close(flow2Child[0]);

            if (pid != 0)
            {
                wait(&pid);
            }

            exit(0);
        }

        pid = fork();
        if (pid == 0)
        {
            prime = nextPrime;
            goto start;
        }
        else
        {
            write(flow2Child[1], &number, sizeof(number));
        }

        close(flow[0]);
        close(flow2Child[1]);
        close(flow2Child[0]);

        if (pid != 0)
        {
            wait(&pid);
        }
    }

    exit(0);
}