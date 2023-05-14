/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:33:56 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/14 14:55:58 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	waitpid(ptr.pid[0], &i, 0);	
	waitpid(ptr.pid[1], &i, 0);
	return (i >> 8);
}
