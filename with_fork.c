#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    int status, pid;
    int pipe_fd[2];
    pid_t p;
    char send[] = "Hello child";
    char receive[50];
    status = pipe(pipe_fd);
    if (status == -1)
    {
        printf("Unable to create pipe\n");
        return -1;
    }
    p = fork();
    if (p < 0)
    {
        printf("Undable to fork\n");
        return -1;
    }
    else if (p == 0)
    {
        read(pipe_fd[0], receive, sizeof(receive));
        printf("Child received msg : %s\n", receive);
    }
    else
    {
        write(pipe_fd[1], send, sizeof(send));
        printf("Parent send msg : %s\n", send);
    }
    return 0;
}
