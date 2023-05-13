/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:33:56 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/13 18:08:46 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command1(t_list *args, int i, t_elements *ptr)
{
	char	*str;
	char	**cmds;
	int		pid;
	str = NULL;
	pid = 1;

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
			dup2(ptr->fd[1], 1);
			close(ptr->fd[1]);
			close(ptr->fd[0]);
			dup2(ptr->infd , 0);
			close(ptr->infd);
		}
		else
		{
			dup2(ptr->fd[0] , 0);
			dup2(ptr->outfd , 1);
			close(ptr->outfd);
			close(ptr->fd[0]);
			close(ptr->fd[1]);
		}
		execve(ptr->cmd_path, cmds, ptr->env);
		exit(127);
	}
}

int		main(int ac, char **av, char **env)
{
	int		i;
	t_elements	ptr;

	i = 0;
	if (ac != 5)
	{	
		write(2,"Invalid Number of arguments\n",29);
		return (1);
	}
	ptr.infd = open_file(av[1], "in");
	ptr.outfd = open_file(av[ac-1],"out");
	ptr.ac = ac;
	ft_exec(&ptr, av, env);
	//waitpid(ptr.pid[0], &i, 0);	
	//waitpid(ptr.pid[1], &i, 0);	
	return (i);
}
