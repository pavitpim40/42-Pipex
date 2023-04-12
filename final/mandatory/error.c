/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:44:54 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/12 19:18:19 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	msg_error(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

void	cmd_error(t_pipe *t)
{
	if (ft_strchr(t->cmd_args[0], '/') != 0)
	{
		msg_error(ERR_FILE);
		write(2, ": ", 2);
		write(2, t->cmd_args[0], ft_strlen(t->cmd_args[0]));
	}
	else
	{
		write(2, t->cmd_args[0], ft_strlen(t->cmd_args[0]));
		write(2, ": ", 2);
		msg_error(ERR_CMD);
	}
	write(2, "\n", 1);
	free_exec_args(t);
	exit(127);
}

int	perror_and_exit(char *error, int status)
{
	perror(error);
	exit(status);
}

int	file_error_and_exit(char *filepath, int status)
{
	msg_error(ERR_FILE);
	write(2, ": ", 2);
	write(2, filepath, ft_strlen(filepath));
	write(2, "\n", 1);
	exit(status);
}
