/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:45:10 by ppimchan          #+#    #+#             */
/*   Updated: 2023/04/10 17:02:05 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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


int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd	[2];
	pid_t	pid;
	// char	buf;
	int		infile_fd;
	int		outfile_fd;
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

		// ## 1-EXECVE-HARDCODE
		// char *args[] = {"/bin/ls", "-la", NULL};
		// execve(args[0], args , NULL);

		// ## 2-ACCEPT ARGV TO EXECVE
		cmd_args = ft_split(argv[2], ' ');
		cmd = get_cmd(PATH_ARR,cmd_args[0]);
		execve(cmd, cmd_args , NULL);


		// CLOSE WRITE-END SIDE : READ-END RECEIVE EOF
		close(pipe_fd[1]);

		// GRACEFULLY EXIT
		exit(EXIT_SUCCESS);
	} 

	// PARENT : need to read from child
	if(pid > 0) {

		// TRY TO OPEN OUTFILE FILE
		outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);

		// CLOSE WRITE-END SIDE : NEED TO READ
		close(pipe_fd[1]);
		
		// NEED TO W8 ?
		printf("W8 child Process\n");
		// wait(NULL);

		// REDIRECTION STDIN TO READ END SIDE
		dup2(pipe_fd[0],STDIN_FILENO);

		// REDIRECTION STOUT TO OUTFILE
		dup2(outfile_fd,STDOUT_FILENO);



		// EXECVE ARGV TO EXECVE
		cmd_args = ft_split(argv[3], ' ');
		cmd = get_cmd(PATH_ARR,cmd_args[0]);
		execve(cmd, cmd_args , NULL);



		// CLOSE READ-END SIDE
		close(pipe_fd[0]);

		// GRACEFULLY EXIT
		exit(EXIT_SUCCESS);
	}
}