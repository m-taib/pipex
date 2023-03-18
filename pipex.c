/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/18 13:06:15 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd_path, t_list *args, char **env)
{
	char	*str;
	t_list 	*tmp;
	char	**cmds;
	int		fd[2];
	int		pid;

	tmp = args;
	str = NULL;
	while (args)
	{
		str = ft_strjoin(str ,args->content);
		if (args->next)
			str = ft_strjoin(str," ");
		args = args->next;
	}
	cmds = ft_split2(str, ' ');
	pipe(fd);
	pid = fork();
	if (pid = 0)
	{
		dup2(fd[0] , 0);
		dup2(fd[1] , 1);
		close(fd[0]);
		close(fd[1]);
		execve(cmd_path, cmds, env);
	}
}

int		main(int ac, char **av, char **ev)
{
	char	**args;
	int		i;
	(void)ev;
	t_list *head;
	char	*cmd;
	i = 0;
	if (ac < 5)
		return (1);
	args = NULL;
	head = get_commands(av[2]);
	cmd = ft_strjoin(ft_strdup("/"), head->content);
	args = get_path(ev);
	args = get_cmd_paths(args, cmd);
	cmd = path(args);
	execute_command(cmd, head, ev);
	return (0);
}
