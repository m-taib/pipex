/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:22:30 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/16 10:37:25 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	if (!s2)
		return (0);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_strncmp(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < len)
		i++;
	return (s1[i] - s2[i]);
}

char	**get_path(char **ev)
{
	int		i;
	char	**path;
	char	*str;

	str = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin: \
			/usr/local/munki: \
			/Library/Frameworks/Mono.framework/Versions/Current/Commands";
	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp(ev[i], "PATH", 3))
		{
			path = ft_split2(ev[i], ':');
			return (path);	
		}
		i++;
	}
	path = ft_split2(str, ':');
	return (path);
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (0);

}

char 	**get_cmd_paths(char **args, char *cmd)
{
	int	i;
	char	**paths;

	i = 0;
	while (args[i])
		i++;
	paths = malloc(sizeof(char *) * ++i);
	if (!paths)
		return (0);
	i = 0;
	paths[i] = ft_strjoin(ft_strdup(ft_strchr(args[i], '/')), cmd);
	++i;
	while (args[i])
	{
		paths[i] = ft_strjoin(args[i], cmd);
		i++;
	}
	paths[i] = NULL;
	return (paths);
}

char	*path(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!access(args[i], F_OK | X_OK))
			return (args[i]);
		i++;
	}
	return (0);
}
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}
