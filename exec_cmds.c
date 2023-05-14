/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/14 14:43:57 by mtaib            ###   ########.fr       */
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
		str[i] = head->content;
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

void	exit_error(char *cmd)
{
	char	*str;

	str = "pipex: command not found: ";
	write(2, str, ft_strlen(str));
	if (cmd)
		write(2, &cmd[1], ft_strlen(cmd));
	write(2, "\n", 1);
	exit(127);
}
void	execute_command(t_list *args, int i, t_elements *ptr)
{
	char	**cmds;
	int		pid;

	if (i < ptr->ac - 2)
		pipe(ptr->next);
	pid = fork();
	if (pid == 0)
	{
		cmds = cmd_args(args);
		if (!ptr->cmd_path ||
				(ptr->cmd_path && !ft_strcmp(&ptr->cmd_path[1] , args->content)))
			exit_error(ptr->cmd_path);
		if (i == 2)
		{
			if (ptr->infd < 0)
				exit(1);
			read_and_write(ptr);
		}
		else
		{
			if (ptr->outfd < 0)
				exit(1);
			read_and_write2(ptr, i);
		}
		if (execve(ptr->cmd_path, cmds, ptr->env))
		{
			free_array(cmds, 0);
			perror("execve");
		}
	}
	ptr->pid[i-2] = pid;
	reset(i, ptr);
}

void	ft_exec(t_elements *ptr, char **av, char **env)
{
	int		i;
	t_list	*head;

	ptr->env = env;
	i = 2;
	while (i < ptr->ac - 1)
	{
		head = get_commands(av[i]);
		ptr->cmd_path = get_and_check_path(head, env);
		execute_command(head, i, ptr);
		free(ptr->cmd_path);
		free_list(head);
		i++;
	}

}
