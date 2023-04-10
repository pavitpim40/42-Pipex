/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:36:43 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/10 18:23:33 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	<sys/wait.h>
# include	<fcntl.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<errno.h>

// PIPEX
typedef struct s_pipe
{
	pid_t	pid_in;
	pid_t	pid_out;
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	pid_t	pid_first_child;
	pid_t	pid_second_child;
	char	*env_path;
	char	**env_path_lists;
	char	*execute_path;
	char	**cmd_args;
} t_pipe;

// LIB_FT
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif