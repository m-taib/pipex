/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/17 18:15:40 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_heredoc(t_elements *ptr, char **av)
{
	char	*s;

	s = NULL;
	ptr->state = 1;
	s = get_line();
	while (1)
	{
		if (!ft_strcmp(av[2], s))
		{
			if (ptr->str)
				free(s);
			break ;
		}
		ptr->str = ft_strjoin(ptr->str, s);
		ptr->str = ft_strjoin(ptr->str, "\n");
		free(s);
		s = get_line();
	}
}

void	ft_parsing(t_elements *ptr, char **av, int *i, char **ev)
{
	ptr->str = NULL;
	if (!ft_strcmp(av[1], "here_doc") && *i == 2)
	{
		ft_heredoc(ptr, av);
		(*i)++;
	}
	ptr->head = get_commands(av[*i]);
	ptr->cmd_path = get_and_check_path(ptr->head, ev);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return ((void *)(str));
}

int	wait_processes(t_elements *ptr)
{
	int	y;
	int	i;

	y = 0;
	i = -1;
	while (++i < ptr->ac - 1 && ptr->pid != 0)
		waitpid(ptr->pid[i], &y, 0);
	close(ptr->infd);
	close(ptr->outfd);
	free(ptr->pid);
	free(ptr);
	return (y >> 8);
}

int	main(int ac, char **av, char **ev)
{
	int			i;
	t_elements	*ptr;

	ptr = malloc(sizeof(t_elements));
	if (!ptr)
		return (0);
	open_files(av, ptr, ac);
	i = 2;
	ptr->ac = ac;
	ptr->pid = malloc(sizeof(int) * ac);
	if (!ptr->pid)
		return (0);
	ft_memset(ptr->pid, 0, sizeof(int) * ac);
	while (i < ac - 1)
	{
		ptr->head = NULL;
		ptr->state = 0;
		ft_parsing(ptr, av, &i, ev);
		execute_command(ptr->head, i, ptr);
		free(ptr->cmd_path);
		free_list(ptr->head);
		i++;
	}
	return (wait_processes(ptr));
}
