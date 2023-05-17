/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:33:56 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/17 18:18:11 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int			i;
	t_elements	ptr;

	i = 0;
	if (ac != 5)
	{
		write(2, "Invalid Number of arguments\n", 29);
		return (1);
	}
	ptr.infd = open_file(av[1], "in", 0);
	ptr.outfd = open_file(av[ac - 1], "out", 0);
	ptr.ac = ac;
	ft_exec(&ptr, av, env);
	ptr.pid = malloc(sizeof(int) * 2);
	if (!ptr.pid)
		return (0);
	waitpid(ptr.pid[0], &i, 0);
	waitpid(ptr.pid[1], &i, 0);
	free(ptr.pid);
	return (i >> 8);
}
