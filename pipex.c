/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/27 18:18:52 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	reset(int  i, t_elements *ptr)
{
	if (i > 2)
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
void	execute_command(t_list *args, int i, t_elements *ptr)
{
	char	*str;
	t_list 	*tmp;
	char	**cmds;
	int		pid;
	tmp = args;
	str = NULL;
	pid = 1;
	
	cmds = cmd_args(args);
	if (i < ptr->ac - 2)
		pipe(ptr->next);
	pid = fork();
	if (pid == 0)
	{
		if (i == 2)
		{
			dup2(ptr->next[1], 1);
			close(ptr->next[1]);
			close(ptr->next[0]);
			dup2(ptr->infd , 0);
			close(ptr->infd);
		}
		else 
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
		execve(ptr->cmd_path, cmds, ptr->env);
		exit(127);
	}
	reset(i, ptr);
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
	ptr->infd = open(av[2],O_RDWR);	
	ptr->outfd = open(av[ac-1],O_RDWR | O_TRUNC | O_CREAT);
	i = 2;
	if (ac < 5)
		return (1);
	args = NULL;
	ptr->ac = ac;
	/*while (i < ac - 1)
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
	while (++i <= ac -1)
		wait(NULL);*/
	(void)cmd;
	(void)ev;
	//while (i < ac - 1)
	//{
		head = get_commands(av[4]);
		while (head)
		{
			printf("%s\n",head->content);
			head = head->next;
		}
	//	i++;
	//}
	/*exit(0);
	cmd = ft_strjoin(ft_strdup("/"), head->content);
	args = get_path(ev);
	args = get_cmd_paths(args, cmd);
	ptr->cmd_path = path(args);
	execute_command(head, i, ptr);*/
	return (0);
}
