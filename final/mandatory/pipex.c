/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:45:10 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/10 18:25:01 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	get_execute_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}


int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;

	// OPEN INFILE,OUTFILE
	pipex.infile = open(argv[1],O_RDONLY);
	pipex.outfile  = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	pipex.env_path = find_path(envp);
	pipex.env_path_lists = ft_split(pipex.env_path,':');

	// OPEN NEW PIPE
	if(pipe(pipex.pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pipex.pid_first_child = fork();
	if (pipex.pid_first_child == 0) 
	{
		close(pipex.pipe_fd[0]);
		dup2(pipex.infile,STDIN_FILENO);
		dup2(pipex.pipe_fd[1],STDOUT_FILENO);

		pipex.cmd_args = ft_split(argv[2], ' ');
		pipex.execute_path =get_execute_path(pipex.env_path_lists ,pipex.cmd_args[0]);
		execve(pipex.execute_path, pipex.cmd_args  , NULL);

		close(pipex.pipe_fd[1]);
		exit(EXIT_SUCCESS);
	} 

	pipex.pid_second_child = fork();
	if(pipex.pid_second_child == 0) {

		close(pipex.pipe_fd[1]);
		dup2(pipex.pipe_fd[0],STDIN_FILENO);
		dup2(pipex.outfile,STDOUT_FILENO);

		pipex.cmd_args = ft_split(argv[3], ' ');
		pipex.execute_path =get_execute_path(pipex.env_path_lists ,pipex.cmd_args[0]);
		execve(pipex.execute_path, pipex.cmd_args  , NULL);

		close(pipex.pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
	waitpid(pipex.pid_first_child, NULL,0);
	waitpid(pipex.pid_second_child, NULL,0);
	return(0);
}