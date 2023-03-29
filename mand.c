/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:33:56 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/28 23:10:12 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_list *args, int i, t_elements *ptr)
{
	char	*str;
	t_list 	*tmp;
	char	**cmds;
	int		pid;
	tmp = args;
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

int		main(int ac, char **av, char **ev)
{
	char	**args;
	int		i;
	t_list *head;
	char	*cmd;
	t_elements	*ptr;

	ptr = malloc(sizeof(t_elements));
	if (!ptr)
		return (0);
	ptr->infd = open(av[1],O_RDWR);
	ptr->outfd = open(av[ac-1],O_RDWR | O_TRUNC | O_CREAT);
	i = 2;
	if (ac < 5)
		return (1);
	args = NULL;
	pipe(ptr->fd);
	ptr->ac = ac;
	while (i < ac - 1)
	{
		head = get_commands(av[i]);
		cmd = ft_strjoin(ft_strdup("/"), head->content);
		args = get_path(ev);
		args = get_cmd_paths(args, cmd);
		ptr->cmd_path = path(args);
		execute_command(head, i, ptr);
		i++;
	}
	i = -1;
	while (++i < 2)
		wait(NULL);	
	return (0);
}
