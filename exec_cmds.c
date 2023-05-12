/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/04/01 19:50:54 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	reset(int  i, t_elements *ptr)
{
	if (i > 2 && ptr->prev[0])
	{
		close(ptr->prev[0]);
		close(ptr->prev[1]);
	}
	if (i >= 2 && i < ptr->ac - 1)
	{
		ptr->prev[0] = ptr->next[0];
		ptr->prev[1] = ptr->next[1];
	}
}

char	**cmd_args(t_list *head)
{
	int		i;
	t_list *tmp;
	char	**str;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (head)
	{
		str[i] = ft_strdup(head->content);
		i++;
		head = head->next;
	}
	str[i] = NULL;
	return (str);
}

void	exec_heredoc(t_elements *ptr, int pid)
{
	int	j;

	j = 0;
	pid = fork();
	if (pid == 0)
	{
		close(ptr->her[0]);
		j = 0;
		ptr->her_doc = ft_split2(ptr->str, ' ');
		while (ptr->her_doc[j])
		{
			ft_putstr(ptr->her_doc[j], ptr->her[1]);
			ft_putstr("\n",ptr->her[1]);
			j++;
		}
		close(ptr->her[1]);
		exit(0);
	}
	else
		close(ptr->her[1]);
}

void	read_and_write(t_elements *ptr)
{
	if (ptr->state)
		dup2(ptr->her[0],0);
		
	else
	{
		dup2(ptr->infd , 0);
		close(ptr->infd);
	}
	dup2(ptr->next[1], 1);
	close(ptr->next[1]);
	close(ptr->next[0]);
	if (ptr->state)
		close(ptr->her[0]);

}

void	read_and_write2(t_elements *ptr, int i)
{
	dup2(ptr->prev[0] , 0);
	close(ptr->prev[1]);
	close(ptr->prev[0]);
	if (i == ptr->ac - 2)
	{
		dup2(ptr->outfd , 1);
		close(ptr->outfd);
	}
	else
	{
		dup2(ptr->next[1] , 1);
		close(ptr->next[1]);
		close(ptr->next[0]);
	}

}

void	execute_command(t_list *args, int i, t_elements *ptr)
{
	char	**cmds;
	int		pid;

	pid = 1;
	cmds = cmd_args(args);
	if (ptr->state)
		exec_heredoc(ptr, pid);
	if (i < ptr->ac - 2)
		pipe(ptr->next);
	pid = fork();
	if (pid == 0)
	{
		if (i == 2 || ptr->state)
			read_and_write(ptr);
		else
			read_and_write2(ptr, i);
		if (execve(ptr->cmd_path, cmds, ptr->env) == -1)
			perror("execve");
		exit(127);
	}
	reset(i, ptr);
}
