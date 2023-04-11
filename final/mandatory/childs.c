/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:01:37 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/11 20:53:35 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child_process(t_pipe t, char **argv, char **envp)
{
	int	r;
	
	r = 0;
	t.infile = open(argv[1],O_RDONLY);
	if(t.infile < 0)
		perror_and_exit(argv[1],EXIT_SUCCESS);
	close(t.pipe_fd[0]);
	dup2(t.infile,STDIN_FILENO);
	dup2(t.pipe_fd[1],STDOUT_FILENO);
	t.cmd_args = ft_split(argv[2], ' ');
	t.execute_path = get_execute_path(t.env_path_lists ,t.cmd_args[0]);
	if(!t.execute_path)
	{
		write(2,t.cmd_args[0],ft_strlen(t.cmd_args[0]));
		write(2,": ",2);
		free_exec_args(&t);
		msg_error(ERR_CMD);
		exit(127);
	}
	r = execve(t.execute_path, t.cmd_args  , envp);
	free_exec_args(&t);
	close(t.pipe_fd[1]); // need to close ?
	if(r == -1) 
		perror_and_exit("execve",1);
	exit(EXIT_SUCCESS);
}

void	second_child_process(t_pipe t,int argc, char **argv, char **envp)
{
	int r;

	r = 0;
	t.outfile  = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if(t.outfile < 0) 
		perror_and_exit(argv[argc - 1],EXIT_FAILURE);
	dup2(t.pipe_fd[0],STDIN_FILENO);
	close(t.pipe_fd[1]);
	dup2(t.outfile,STDOUT_FILENO);
	t.cmd_args = ft_split(argv[3], ' ');
	t.execute_path = get_execute_path(t.env_path_lists ,t.cmd_args[0]);
	if(!t.execute_path)
	{
		write(2,t.cmd_args[0],ft_strlen(t.cmd_args[0]));
		write(2,": ",2);
		free_exec_args(&t);
		msg_error(ERR_CMD);
		exit(127);
	}
	r = execve(t.execute_path, t.cmd_args , envp);
	free_exec_args(&t);
	close(t.pipe_fd[0]);
	if(r == -1) 
		perror_and_exit("execve",1);
	exit(EXIT_SUCCESS);
}
