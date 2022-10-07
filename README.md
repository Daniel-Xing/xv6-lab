# Mit 6.s081 Lab

## Lab1: Xv6 and Unix utilities
Lab1 contains serveral small tasks, most of them is quiet easy. We need implement some utilities using system calls provide by the Xv6.

### sleep

Xv6 already has a sleep system call, meaning that we just need to parse command line arguments and call the function.

```c
    int time;
    time = atoi(argv[1]);
    sleep(time);
```

### pingpong

Pinpong requires us using syscall fork() and Pipe() to send the message between two process.


