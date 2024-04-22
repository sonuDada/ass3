#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
int status;
int pipe_fd[2];
char send_msg[] = "Hello everyone";
char receive_msg[50];
//Without fork system call
status = pipe(pipe_fd);
if(status == -1)
{
printf("Unable to create pipe");
return -1;
}
printf("Sender Message : %s\n",send_msg);
write(pipe_fd[1],send_msg,sizeof(send_msg));
read(pipe_fd[0],receive_msg,50);
printf("Received message : %s",receive_msg);
return 0;
}