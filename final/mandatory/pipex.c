/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:45:10 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/11 16:04:01 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipe *t)
{
	close(t->pipe_fd[0]);
	close(t->pipe_fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	t;
	
	if(argc != 5)
		perror_and_exit(ERR_ARGS,EXIT_FAILURE);
	t.env_path = find_path(envp);
	t.env_path_lists = ft_split(t.env_path,':');
	if(pipe(t.pipe_fd) < 0)
		perror_and_exit(ERR_PIPE, EXIT_FAILURE);
	t.pid_first_child = fork();
	if(t.pid_first_child < 0)
		perror_and_exit(ERR_FORK, EXIT_FAILURE);
	if (t.pid_first_child == 0) 
		first_child_process(t,argv,envp);
	t.pid_second_child = fork();
	if(t.pid_first_child < 0)
		perror_and_exit(ERR_FORK, EXIT_FAILURE);
	if(t.pid_second_child == 0)
		second_child_process(t,argc,argv,envp);
	close_pipes(&t);
	waitpid(t.pid_first_child, &t.status,0);
	waitpid(t.pid_second_child, &t.status,0);
	parent_free(&t);
	if (WEXITSTATUS(t.status) != 0) 
		exit(WEXITSTATUS(t.status));
	exit(EXIT_SUCCESS);
}