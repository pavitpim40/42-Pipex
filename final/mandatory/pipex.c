/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:45:10 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/12 13:18:43 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipe *t)
{
	close(t->pipe_fd[0]);
	close(t->pipe_fd[1]);
}

static	void create_pipe_error(t_pipe *t)
{
	parent_free(t);
	perror_and_exit(ERR_PIPE, EXIT_FAILURE);
}

static	void create_fork_error(t_pipe *t)
{
	if (t->pid_first_child > 0)
		waitpid(t->pid_first_child, &t->status, 0);	
	close_pipes(t);
	parent_free(t);
	perror_and_exit(ERR_FORK, EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	t;
	
	if (argc != 5)
		perror_and_exit(ERR_ARGS, EXIT_FAILURE);
	t.env_path = find_path(envp);
	t.env_path_lists = ft_split(t.env_path,':');
	if (pipe(t.pipe_fd) < 0)
		create_pipe_error(&t);
	t.pid_first_child = fork();
	if (t.pid_first_child < 0)
		create_fork_error(&t); 
	if (t.pid_first_child == 0)
		first_child_process(t, argv, envp); // current check point
	t.pid_second_child = fork();
	if (t.pid_second_child < 0)
		create_fork_error(&t);
	if (t.pid_second_child == 0)
		second_child_process(t, argc, argv, envp);
	close_pipes(&t);
	waitpid(t.pid_first_child, &t.status, 0);
	waitpid(t.pid_second_child, &t.status, 0);
	parent_free(&t);
	exit(WEXITSTATUS(t.status));
}
