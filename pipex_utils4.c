/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 07:34:03 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/17 16:26:00 by mtaib            ###   ########.fr       */
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

int	open_file(char *file_name, char *file_type, int state)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(file_type, "in") && !state)
		fd = open(file_name, O_RDONLY);
	else
	{
		if (state)
			fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (fd < 0)
	{
		write(2, "pipex : ", 9);
		write(2, file_name, ft_strlen(file_name));
		perror(" ");
	}
	return (fd);
}

void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->content)
			free(head->content);
		free(head);
		head = tmp;
	}
	free(head);
}

char	*check_path(char **env, char *cmd)
{
	int		i;
	char	*str;

	str = NULL;
	i = -1;
	while (env[++i])
	{
		str = ft_strjoin(env[i], cmd);
		if (!access(str, F_OK | X_OK))
		{
			free_array(env, i + 1);
			free(cmd);
			return (str);
		}
		free(str);
	}
	free(env[i]);
	free(env);
	return (cmd);
}

char	*get_and_check_path(t_list *head, char **env)
{
	int		i;
	char	**path;
	char	*str;
	char	*cmd;

	if (!head)
		return (NULL);
	if (!access(head->content, F_OK | X_OK))
	{
		cmd = ft_strdup(head->content);
		return (cmd);
	}
	cmd = ft_strjoin(ft_strdup("/"), head->content);
	str = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	i = -1;
	path = NULL;
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 3))
		{
			path = ft_split2(&env[i][5], ':');
			return (check_path(path, cmd));
		}
	}
	return (check_path(ft_split2(str, ':'), cmd));
}
