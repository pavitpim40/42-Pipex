/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:44:54 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/11 13:36:25 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int msg_error(char *error)
{
	write(2,error,ft_strlen(error));
	return (1);
}

int	print_error(char *error)
{
	perror(error);
	exit(1);
}

int	perror_and_exit(char *error,int status)
{
	perror(error);
	exit(status);
}