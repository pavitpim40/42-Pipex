/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:45:10 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/11 13:45:16 by ppimchan         ###   ########.fr       */
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
	int r;
	
	r = 0;
	close(t.pipe_fd[0]);
	dup2(t.infile,STDIN_FILENO);
	dup2(t.pipe_fd[1],STDOUT_FILENO);
	
	t.cmd_args = ft_split(argv[2], ' ');
	t.execute_path = get_execute_path(t.env_path_lists ,t.cmd_args[0]);
	
	if(!t.execute_path)
	{
		// FREE CHILD
		free_exec_args(&t);
		msg_error("Command not found\n");
		exit(127);
	}
	// printf("1st child can execve\n");
	execve(t.execute_path, t.cmd_args  , envp);
	free_exec_args(&t);
	close(t.pipe_fd[1]);
	
	if(r == -1) 
		print_error("execve");
	// NEED TO EXIT ?
	exit(EXIT_SUCCESS);
}

static void	second_child_process(t_pipe t, char **argv, char **envp)
{
	// printf("I'm second child\n");
	int r;

	r = 0;
	dup2(t.pipe_fd[0],STDIN_FILENO);
	
	close(t.pipe_fd[1]);
	
	dup2(t.outfile,STDOUT_FILENO);
		// printf("END DEBUG\n");
	t.cmd_args = ft_split(argv[3], ' ');
		// printf("2nd child split\n");
	t.execute_path = get_execute_path(t.env_path_lists ,t.cmd_args[0]);
	if(!t.execute_path)
	{
		free_exec_args(&t);
		msg_error("Command not found\n");
		exit(127); // WHY 127
	}
	r = execve(t.execute_path, t.cmd_args , envp);
	free_exec_args(&t);
	// NEED TO EXIT ?
	close(t.pipe_fd[0]);
	if(r == -1) 
		print_error("execve");
	exit(EXIT_SUCCESS);
}

void	close_pipes(t_pipe *t)
{
	close(t->pipe_fd[0]);
	close(t->pipe_fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	t;
	
	if(argc != 5)
		return msg_error(ERR_ARGS);

	// INFILE
	t.infile = open(argv[1],O_RDONLY);
	if(t.infile < 0)
		perror_and_exit(argv[1],EXIT_SUCCESS);
	
	// OUTFILE 
	t.outfile  = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if(t.outfile < 0) 
		perror_and_exit(argv[argc - 1],EXIT_FAILURE);
	
	// ENV
	t.env_path = find_path(envp);
	t.env_path_lists = ft_split(t.env_path,':');
	if(pipe(t.pipe_fd) < 0)
		perror_and_exit("pipe", EXIT_FAILURE);

	t.pid_first_child = fork();
	if(t.pid_first_child < 0)
		perror_and_exit("fork", EXIT_FAILURE);


	if (t.pid_first_child == 0) 
		first_child_process(t,argv,envp);

	t.pid_second_child = fork();
	if(t.pid_second_child == 0)
		second_child_process(t,argv,envp);

	close_pipes(&t);
	waitpid(t.pid_first_child, &t.status,0);
	waitpid(t.pid_second_child, &t.status,0);
	// close(t.infile);
	// close(t.outfile);
		// parent_free(&t);
	if (WEXITSTATUS(t.status) != 0) {

	// printf("STATUS : %d\n",t.status);
	exit(WEXITSTATUS(t.status));
	}
	

	exit(EXIT_SUCCESS);
}