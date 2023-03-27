/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:33:56 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/22 17:34:17 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_list *args, int i, t_elements *ptr, int	*fd)
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
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			dup2(ptr->infd , 0);
			close(ptr->infd);
		}
		else
		{
			dup2(fd[0] , 0);
			if (i == (ptr->ac - 2))
				dup2(ptr->outfd , 1);
			else
				dup2(fd[1] , 1);
			close(fd[0]);
			close(fd[1]);
		}
		execve(ptr->cmd_path, cmds, ptr->env);
	}
}

int		main(int ac, char **av, char **ev)
{
	char	**args;
	int		i;
	t_list *head;
	char	*cmd;
	int		arr[2];
	t_elements	*ptr;

	ptr = malloc(sizeof(t_elements));
	if (!ptr)
		return (0);
	ptr->infd = open("file1",O_RDWR);
	ptr->outfd = open("file2",O_RDWR | O_TRUNC);
	i = 2;
	if (ac < 5)
		return (1);
	args = NULL;
	pipe(arr);
	ptr->ac = ac;
	while (i < ac - 1)
	{
		head = get_commands(av[i]);
		cmd = ft_strjoin(ft_strdup("/"), head->content);
		args = get_path(ev);
		args = get_cmd_paths(args, cmd);
		ptr->cmd_path = path(args);
		execute_command(head, i, ptr, arr);
		i++;
	}
	return (0);
}
