#include "pipex.h"
#include <fcntl.h>
int		main(int ac, char **av, char **env)
{
		
	char	*path;
	char	**cmd;
	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = malloc(10);
	cmd[1] = malloc(10);
	//pipe(fd);
	path = "/bin/ls";
	cmd[0] = "ls";
	cmd[1] = "-a";
	int		fd = open("file1",O_RDWR);
	dup2(fd, 1);
	execve(path , cmd, env);
	return (0);	
}
