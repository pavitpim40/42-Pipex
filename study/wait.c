// #include<stdio.h>
// #include<stdlib.h>
// #include<sys/wait.h>
// #include<unistd.h>
 
// int main()
// {
//     pid_t cpid;
//     if (fork()== 0) {
// 		printf("I'm child\n");
// 		exit(0);           /* terminate child */
// 	}
     
//     else
//         cpid = wait(NULL); /* reaping parent */
//     printf("Parent pid = %d\n", getpid());
//     printf("Child pid = %d\n", cpid);
 
//     return 0;
// }

// EX2 

// C program to demonstrate working of wait()
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
 
int main()
{
    if (fork()== 0)
        printf("HC: hello from child\n");
    else
    {
        printf("HP: hello from parent\n");
        wait(NULL);
        printf("CT: child has terminated\n");
    }
 
    printf("Bye\n");
    return 0;
}