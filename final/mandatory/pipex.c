/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:45:10 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/10 18:39:27 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	*get_execute_path(char **paths, char *cmd)
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

static void	first_child_process(t_pipe t, char **argv, char **envp)
{
	close(t.pipe_fd[0]);
	dup2(t.infile,STDIN_FILENO);
	dup2(t.pipe_fd[1],STDOUT_FILENO);

	t.cmd_args = ft_split(argv[2], ' ');
	t.execute_path =get_execute_path(t.env_path_lists ,t.cmd_args[0]);
	execve(t.execute_path, t.cmd_args  , envp);

	// NEED TO EXIT ?
	close(t.pipe_fd[1]);
	exit(EXIT_SUCCESS);
}


static void	second_child_process(t_pipe t, char **argv, char **envp)
{
	close(t.pipe_fd[1]);
	dup2(t.pipe_fd[0],STDIN_FILENO);
	dup2(t.outfile,STDOUT_FILENO);

	t.cmd_args = ft_split(argv[3], ' ');
	t.execute_path =get_execute_path(t.env_path_lists ,t.cmd_args[0]);
	execve(t.execute_path, t.cmd_args  , envp);

	// NEED TO EXIT ?
	close(t.pipe_fd[0]);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	t;

	// OPEN INFILE,OUTFILE
	t.infile = open(argv[1],O_RDONLY);
	t.outfile  = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	t.env_path = find_path(envp);
	t.env_path_lists = ft_split(t.env_path,':');

	// OPEN NEW PIPE
	if(pipe(t.pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	t.pid_first_child = fork();
	if (t.pid_first_child == 0) 
		first_child_process(t,argv,envp);

	t.pid_second_child = fork();
	if(t.pid_second_child == 0)
		second_child_process(t,argv,envp);

	waitpid(t.pid_first_child, NULL,0);
	waitpid(t.pid_second_child, NULL,0);
	return(0);
}