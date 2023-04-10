/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:50:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/10 15:00:44 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 	<stdlib.h>
#include 	<unistd.h>
#include 	<stdio.h>
#include 	<string.h>
# include	<fcntl.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count * size < count && count * size < size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}

static	int	should_free_mem(char **array_word, size_t k, size_t len)
{
	if (k != len)
	{
		len -= 1;
		while (len > 0)
		{
			free(array_word[len]);
			len--;
		}
		free(array_word);
		return (1);
	}
	return (0);
}

static int	write_word(char **array_word, char const *s, char c, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*word;

	i = 0;
	j = 0;
	k = 0;
	while (k < len)
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[j] != c && s[j] != '\0')
			j++;
		word = ft_calloc(j - i + 1, sizeof(char));
		if (word == NULL)
			break ;
		j = 0;
		while (s[i] != c && s[i] != '\0')
			word[j++] = s[i++];
		array_word[k] = word;
		k++;
	}
	return (should_free_mem(array_word, k, len));
}

static	int	count_word(char const *s, char c)
{
	size_t	len;
	size_t	end_word;

	len = 0;
	end_word = 0;
	if (!*s)
		return (0);
	while (*s == c)
		s++;
	if (!*s)
		return (0);
	while (*s != '\0')
	{
		if (*s != c && end_word == 1)
		{
			len++;
			end_word = 0;
		}
		else if (*s == c && end_word == 0)
			end_word = 1;
		s++;
	}
	if (s[ft_strlen(s)] == c && c != '\0')
		len--;
	return (len + 1);
}

char	**ft_split(char const *s, char c)
{
	size_t	num_word;
	char	**array_word;

	if (!s)
		return (NULL);
	num_word = count_word(s, c);
	array_word = malloc((num_word + 1) * sizeof(char *));
	if (array_word == NULL)
		return (NULL);
	array_word[num_word] = NULL;
	if (write_word(array_word, s, c, num_word) == 1)
		return (NULL);
	return (array_word);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			break ;
		i ++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	len1;
	size_t	len2;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (0);
	while (i < len1)
	{
		res[i] = s1[i];
		i ++;
	}
	while (i < len1 + len2)
	{
		res[i] = s2[i - len1];
		i ++;
	}
	res[i] = '\0';
	return (res);
}


char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	*get_cmd(char **paths, char *cmd)
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

void child_process(int f1,char *cmd1)
{

}

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd	[2];
	pid_t	pid;
	char	buf;
	int		infile_fd;
	char	*PATH;
	char	*cmd;
	char	**cmd_args;
	
	printf("ARGV-1 : %s\n", argv[1]);
	printf("ARGV-2 : %s\n", argv[2]);

	// GET ENV:PATH -> SINGLE STRING
	PATH = find_path(envp);

	// GET ENV-PATH AFTER SPLIT BY ":" --> GOT ARRAY
	char **PATH_ARR = ft_split(PATH,':');

	// OPEN NEW PIPE
	if(pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	// CHILD : need to write to parent
	if (pid == 0) 
	{
		// TRY TO OPEN INFILE FILE
		infile_fd = open(argv[1],O_RDONLY);
		// HANDLE ERROR WHEN CANNOT OPEN FILE

		// CLOSE READ-END SIDE
		close(pipe_fd[0]);

		// # REDIRECTION STDIN TO INFILE_FILE
		dup2(infile_fd,STDIN_FILENO);
		// # FIND CMD FOR STDIN BEFORE EXECUTE IN EXECVE
		
		// # WRITE IN WRITE-END : STDOUT -> WRITE-END
		// ## REDIRECTION STDOUT TO WRITE-END SIDE
		dup2(pipe_fd[1],STDOUT_FILENO);
		
		// ## 1
		// child_process(pipe_fd[1], argv[1]);

		// ## 2 : HARD CODE PRINT
		// printf("writing something from child\n");
		// write(pipe_fd[1], argv[1],strlen(argv[1]));

		// ## 3-USE EXECVE
		cmd_args = ft_split(argv[2], ' ');
		cmd = get_cmd(PATH_ARR,cmd_args[0]);
		// printf("CMD : %s", cmd);
		execve(cmd, cmd_args , NULL);

		// ## 4-USE EXECVE-HARDCODE
		// char *args[] = {"/bin/ls", "-la", NULL};
		// execve(args[0], args , NULL);

		// CLOSE WRITE-END SIDE : READ-END RECEIVE EOF
		close(pipe_fd[1]);

		// GRACEFULLY EXIT
		exit(EXIT_SUCCESS);
	} 

	// PARENT : need to read from child
	if(pid > 0) {
		close(pipe_fd[1]);
		printf("W8 child\n");
		wait(NULL);
		while(read(pipe_fd[0],&buf,1) >0)
		{
			write(STDOUT_FILENO,&buf,1);
		} 
		printf("\nalready got message\n");
		close(pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
}