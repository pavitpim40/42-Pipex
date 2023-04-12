

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
# define ERR_PIPE "pipe"
# define ERR_FORK "fork"
# define ERR_CMD "command not found"


typedef struct s_pipe {

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
	
} t_pipe;

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
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

void	print_lists(t_pipe *t)
{

		printf("%s\n",t->env_path_lists[0]);
	
	

}
 


void	first_child_process(t_pipe t, char **argv, char **envp)
{
		
		printf("I'm Child\n");
		
		printf("ARRAY ADD IN C : %p\n", t.env_path_lists);
		printf("ITEM ADD IN C : %p\n", t.env_path_lists[0]);
		print_lists(&t);
		// manipulate_list(&t);
		t.env_path_lists[0] = "gg";
		printf("I'm Child-After Manipulate\n");
		printf("ARRAY ADD IN C-AF : %p\n", t.env_path_lists);
		printf("ITEM ADD IN C-AF : %p\n", t.env_path_lists[0]);
		print_lists(&t);
		sleep(3);
		
}

int main (int ac, char **av, char **envp)
{
	t_pipe t;
	t.env_path = find_path(envp);
	t.env_path_lists = ft_split(t.env_path,':');
	t.pid_first_child = fork();
	if (t.pid_first_child == 0) 
		first_child_process(t,av,envp);
	if (t.pid_first_child > 0)
	{
		waitpid(t.pid_first_child,&t.status,0);
		printf("I'm Parent\n");
		printf("ARRAY ADD IN P : %p\n", t.env_path_lists);
		printf("ITEM ADD IN P : %p\n", t.env_path_lists[0]);
		print_lists(&t);
	}
		

}