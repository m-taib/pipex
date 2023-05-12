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

void	ft_heredoc(t_elements *ptr, char **av)
{
	char	*s;
	
	s = NULL;
	pipe(ptr->her);
	ptr->state = 1;
	s = get_line();
	while (1)
	{
		if (!ft_strcmp(av[2], s))
		{
			if (!ptr->str)
				ptr->str = ptr->str;
			break ;
		}
		ptr->str = ft_strjoin(ptr->str, s);
		ptr->str = ft_strjoin(ptr->str, " ");
		s = get_line();
	}
}

void	ft_parsing(t_elements *ptr, char **av, int *i, char **ev)
{
	char	**args;
	char	*cmd;

	args = NULL;
	ptr->state = 0;
	if (!ft_strcmp(av[1], "here_doc") && *i == 2)
	{
		ft_heredoc(ptr, av);
		(*i)++;
	}
	ptr->head = get_commands(av[*i]);
	cmd = ft_strjoin(ft_strdup("/"), ptr->head->content);
	if (av[*i][0] == '.' && av[*i][1] == '/')
		ptr->cmd_path = cmd_path(av[*i]);
	else if (av[*i][0] == '/')
	{
		ptr->cmd_path = cmd_path(av[*i]);
		ptr->cmd_path = path(&av[*i]);
	}
	else
	{	
		args = get_path(ev);
		args = get_cmd_paths(args, cmd);
		ptr->cmd_path = path(args);
	}
}

void	ft_close(t_elements *ptr)
{
	close(ptr->infd);
	close(ptr->outfd);
	close(ptr->next[0]);
	close(ptr->next[1]);
	close(ptr->prev[0]);
	close(ptr->prev[1]);
	close(ptr->her[0]);
	close(ptr->her[1]);
}

int	main(int ac, char **av, char **ev)
{
	int		i;
	t_elements	*ptr;

	ptr = malloc(sizeof(t_elements));
	if (!ptr)
		return (0);
	ptr->infd = open(av[1], O_RDWR);
	ptr->outfd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT);
	i = 2;
	if (ac < 5)
		return (1);
	ptr->ac = ac;
	ptr->str = NULL;
	ptr->head = NULL;
	while (i < ac - 1)
	{
		ft_parsing(ptr, av, &i, ev);
		execute_command(ptr->head, i, ptr);
		i++;
	}
	i = -1;
	ft_close(ptr);
	while(++i <= ac -1)
		wait(NULL);
	return (0);
}
