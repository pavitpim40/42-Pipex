/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:50:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/09 23:56:39 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


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
	
	if(pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	// CHILD : need to write to parent
	if (pid == 0) 
	{
		// CLOSE READ END
		close(pipe_fd[0]);
		// WRITE IN WRITE END
		// child_process(pipe_fd[1], argv[1]);
		printf("writing something from child\n");
		write(pipe_fd[1], "test\n",5);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);

	} 

	// PARENT : need to read from child
	if(pid > 0) {
		close(pipe_fd[1]);
		printf("W8 child\n");
		// wait(NULL);
		while(read(pipe_fd[0],&buf,1) >0)
		{
			write(STDOUT_FILENO,&buf,1);
		} 
		printf("already got message\n");
		close(pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
}