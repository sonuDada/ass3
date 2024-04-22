#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    int status1, status2;
    int pipe_fd1[2], pipe_fd2[2];
    pid_t p;
    char child_send[] = "hello form child process";
    char parent_send[] = "hello from parent process";
    char reader[50];
    status1 = pipe(pipe_fd1);
    if (status1 == -1)
    {
        printf("Unable to create pipe1\n");
        return -1;
    }
    status2 = pipe(pipe_fd2);
    if (status2 == -1)
    {
        printf("Unable to create pipe2\n");
        return -1;
    }
    p = fork();
    if (p < 0)
    {
        printf("Unable to fork\n");
        return -1;
    }
    else if (p == 0)
    {
        close(pipe_fd1[1]);
        close(pipe_fd2[0]);
        read(pipe_fd1[0], reader, sizeof(reader));
        printf("Child : %s \n", reader);
        printf("Child process sending msg \n");
        write(pipe_fd2[1], child_send, sizeof(child_send));
    }
    else
    {
        close(pipe_fd1[0]);
        close(pipe_fd2[1]);
        printf("Parend process sending msg \n");
        write(pipe_fd1[1], parent_send, sizeof(parent_send));
        read(pipe_fd2[0], reader, sizeof(reader));
        printf("Parent : %s\n", reader);
    }
    return 0;
}
