/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/18 23:10:17 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd_path, t_list *args, char **env, int i, int ac, int fdd, int infd, int *fd)
{
	char	*str;
	t_list 	*tmp;
	char	**cmds;
	int		pid;
	(void)ac;
	tmp = args;
	str = NULL;
	pid = 1;
	(void)fdd;	
	while (args)
	{
		str = ft_strjoin(str ,args->content);
		if (args->next)
			str = ft_strjoin(str," ");
		args = args->next;
	}
	cmds = ft_split2(str, ' ');
	pid = fork();
	if (pid == 0)
	{
		if (i == 2)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			dup2(infd , 0);
			close(infd);
		}
		else 
		{
			dup2(fd[0] , 0);
			if (i == ac - 2)
			{
				dup2(fdd , 1);
			}
			else
				dup2(fd[1] , 1);
			close(fd[0]);
			close(fd[1]);
		}
		execve(cmd_path, cmds, env);
	}
}

int		main(int ac, char **av, char **ev)
{
	char	**args;
	int		i;
	(void)ev;
	t_list *head;
	char	*cmd;
	int		fd;
	int		fd1;
	int		arr[2];
	fd1 = open("file1",O_RDWR);	
	fd = open("file2",O_RDWR | O_TRUNC);
	i = 2;
	if (ac < 5)
		return (1);
	args = NULL;
	pipe(arr);
	while (i < ac - 1)
	{
		head = get_commands(av[i]);
		cmd = ft_strjoin(ft_strdup("/"), head->content);
		args = get_path(ev);
		args = get_cmd_paths(args, cmd);
		cmd = path(args);
		execute_command(cmd, head, ev, i, ac, fd, fd1, arr);
		i++;
	}
	return (0);
}
