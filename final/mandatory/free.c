/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:01:39 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/10 23:20:39 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_exec_args(t_pipe *t)
{
	int	i;

	i = 0;
	while (t->cmd_args[i])
	{
		free(t->cmd_args[i]);
		i++;
	}
	free(t->cmd_args);
	free(t->execute_path);
}

void	parent_free(t_pipe *t)
{
	int	i;

	i = 0;
	close(t->infile);
	close(t->outfile);
	while (t->cmd_args[i])
	{
		free(t->cmd_args[i]);
		i++;
	}
	free(t->execute_path);
}