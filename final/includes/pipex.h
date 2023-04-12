/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:36:43 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/12 19:25:57 by ppimchan         ###   ########.fr       */
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
# include <errno.h>

# define ERR_ARGS "Invalid number of args.\n" 
# define ERR_PIPE "pipe"
# define ERR_FORK "fork"
# define ERR_CMD "command not found"
# define ERR_FILE "no such file or directory"

// PIPEX
typedef struct s_pipe
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	int		status;
	pid_t	pid_first_child;
	pid_t	pid_second_child;
	char	*env_path;
	char	**env_path_lists;
	char	*execute_path;
	char	**cmd_args;
}	t_pipe;

// PATH
char	*find_path(char **envp);
char	*get_execute_path(char **paths, char *cmd);

// CHILDS
void	first_child_process(t_pipe t, char **argv, char **envp);
void	second_child_process(t_pipe t, int argc, char **argv, char **envp);

// FREE
void	free_exec_args(t_pipe *t);
void	parent_free(t_pipe *t);

// ERROR
int		msg_error(char *error);
int		perror_and_exit(char *error, int status);
int		file_error_and_exit(char *filepath, int status);
void	cmd_error(t_pipe *t);

// LIB_FT
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);

#endif