/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/17 17:49:41 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	reset(int i, t_elements *ptr)
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

void	exec_heredoc(t_elements *ptr, int pid)
{
	int	j;

	j = 0;
	pipe(ptr->her);
	pid = fork();
	if (pid == 0)
	{
		close(ptr->her[0]);
		j = -1;
		ptr->her_doc = ft_split2(ptr->str, '\n');
		while (ptr->her_doc[++j])
		{
			ft_putstr(ptr->her_doc[j], ptr->her[1]);
			ft_putstr("\n", ptr->her[1]);
		}
		free_array(ptr->her_doc, 0);
		free(ptr->str);
		free_list(ptr->head);
		free(ptr->cmd_path);
		close(ptr->her[1]);
		free(ptr);
		exit(0);
	}
	close(ptr->her[1]);
	free(ptr->str);
}

void	ft_state(t_elements *ptr, int i)
{
	if (i == 2 || ptr->state)
		read_and_write(ptr);
	else
		read_and_write2(ptr, i);
}

void	execute_command(t_list *args, int i, t_elements *ptr)
{
	int	pid;

	if (ptr->state)
		exec_heredoc(ptr, 0);
	if (i < ptr->ac - 2)
		pipe(ptr->next);
	pid = fork();
	if (pid == 0)
	{
		ptr->cmds = cmd_args(args);
		if (!ptr->cmd_path || (ptr->cmd_path && !ft_strcmp(&ptr->cmd_path[1],
					args->content)))
			exit_error(ptr->cmd_path, ptr);
		if (ptr->infd < 0 && i == 2 && !ptr->state)
			exit(1);
		ft_state(ptr, i);
		if (execve(ptr->cmd_path, ptr->cmds, ptr->env))
		{
			free_array(ptr->cmds, 0);
			perror("execve");
		}
	}
	ptr->pid[i - 2] = pid;
	reset(i, ptr);
}

void	ft_exec(t_elements *ptr, char **av, char **env)
{
	int		i;
	t_list	*head;

	ptr->state = 0;
	ptr->env = env;
	i = 2;
	while (i < ptr->ac - 1)
	{
		head = get_commands(av[i]);
		ptr->cmd_path = get_and_check_path(head, env);
		execute_command(head, i, ptr);
		free(ptr->cmd_path);
		i++;
	}
}
