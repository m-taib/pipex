/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/06 15:32:32 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		main(int ac, char **av, char **ev)
{
	char	**args;
	int		i;
	i = 0;
	if (ac != 5)
		return (1);
	args = NULL;
	/*if (args[i])
	{
		while (args[i])
		{
			printf("%s\n",args[i]);
			i++;
		}
	}
	exit(0);
	free_array(args);*/
	//exit(0);
	//printf("%s\n",av[2]);
	char *cmd;
	printf("%d",count(av[2], ' ' ));
	exit(0);
	args = ft_split3((av[2]), ' ');
	if (args[i])
	{
		while (args[i])
		{
			printf("%s\n",args[i]);
			i++;
		}
	}
	exit(0);
	cmd = ft_strjoin(ft_strdup("/"), args[0]);
	args = get_path(ev);
	i = 0;
	args = get_cmd_paths(args, cmd);
	while (args[i])
	{
		printf("%s\n",args[i]);
		i++;
	}
	i = 0;
	return (0);
}
