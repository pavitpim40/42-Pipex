/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:50:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/10 12:07:53 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 	<stdlib.h>
#include 	<unistd.h>
#include 	<stdio.h>
#include 	<string.h>
# include	<fcntl.h>

//	Utility function for write
// void	writestr(int fd, const char *str)
// {
// 	write(fd, str, strlen(str));
// }

void child_process(int f1,char *cmd1)
{

}

int	main(int argc, char **argv)
{
	int	pipe_fd	[2];
	pid_t	pid;
	char	buf;
	int		infile_fd;
	
	if(pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	// CHILD : need to write to parent
	if (pid == 0) 
	{
		// TRY TO OPEN INFILE FILE
		infile_fd = open(argv[1],O_RDONLY);
		// HANDLE ERROR WHEN CANNOT OPEN FILE

		// CLOSE READ-END SIDE
		close(pipe_fd[0]);

		// REDIRECTION STDIN TO INFILE_FILE
		dup2(infile_fd,STDIN_FILENO);
		
		// # WRITE IN WRITE-END : STDOUT TO WRITE-END
		// ## REDIRECTION STDOUT TO WRITE-END SIDE
		dup2(pipe_fd[1],STDOUT_FILENO);
		
		// ## 1
		// child_process(pipe_fd[1], argv[1]);

		// ## 2 : HARD CODE PRINT
		// printf("writing something from child\n");
		// write(pipe_fd[1], argv[1],strlen(argv[1]));

		// ## 3-USE EXECVE
		char *args[] = {"/bin/ls", "-la", NULL};
		execve(args[0], args, NULL);

		// CLOSE WRITE-END SIDE : READ-END RECEIVE EOF
		close(pipe_fd[1]);

		// GRACEFULLY EXIT
		exit(EXIT_SUCCESS);
	} 

	// PARENT : need to read from child
	if(pid > 0) {
		close(pipe_fd[1]);
		printf("W8 child\n");
		wait(NULL);
		while(read(pipe_fd[0],&buf,1) >0)
		{
			write(STDOUT_FILENO,&buf,1);
		} 
		printf("\nalready got message\n");
		close(pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
}