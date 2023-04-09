#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>


int main ()
{
	char *cmd = "/bin/ls";
	char *args[] = {"/bin/ls", "-la", NULL};
	execve(cmd, args, NULL);
	return (0);
}