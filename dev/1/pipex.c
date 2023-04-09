#include <stdlib.h>

typedef struct s_pipex {
	pid_t	pid_in;
	pid_t	pid_out;
	int		status;
	int	end[2];
}	t_pipex;

void first_child(t_pipex pipex, char **argc, char **envp)
{

}
int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	// envp : environment variable pass
	if(argc != 5) {
		// RETURN ERROR MSG
	}

	pipex.pid_in = fork();
	if(pipex.pid_in == 0)
		first_child(pipex,argv,envp);

	// CLOSE PIPE
	waitpid(pipex.pid_in, &pipex.status,0);
	// FREE PARENT

	if(WEXITSTATUS(pipex.status) != 0)
		exit(WEXITSTATUS(pipex.status));

	exit(EXIT_SUCCESS);
}