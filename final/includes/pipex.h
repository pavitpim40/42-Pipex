/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:36:43 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/10 22:05:04 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/*to perror*/
# include <stdio.h>

# include	<errno.h>

# define ERR_ARGS "Invalid number of args.\n" 

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

// FREE
void	free_exec_args(t_pipe *t);

// ERROR
int msg_error(char *error);
int	print_error(char *error);

// LIB_FT
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif