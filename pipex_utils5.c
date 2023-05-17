/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:05:57 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/17 18:14:27 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(char **av, t_elements *ptr, int ac)
{
	if (ft_strcmp(av[1], "here_doc"))
		ptr->infd = open_file(av[1], "in", 0);
	if (!ft_strcmp(av[1], "here_doc"))
		ptr->outfd = open_file(av[ac - 1], "out", 1);
	else
		ptr->outfd = open_file(av[ac - 1], "out", 0);
}

char	*joined_utils(char *s, char *s2, char *str, int *i)
{
	char	c;
	char	*line;

	c = s[(*i)++];
	line = str;
	while (s[*i] && s[*i] != c)
	{
		s2[0] = s[*i];
		if (s[*i] && s[*i] != c)
			line = ft_strjoin(line, s2);
		(*i)++;
	}
	return (line);
}

char	*joined_arg(char *s, int *j)
{
	int		i;
	char	*line;
	char	*s2;

	s2 = malloc(2);
	s2[1] = '\0';
	line = NULL;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
			line = joined_utils(s, s2, line, &i);
		else
		{
			if (s[i])
			{
				s2[0] = s[i];
				line = ft_strjoin(line, s2);
			}
		}
	}
	*j = i;
	return (free(s2), line);
}

void	decale_index(char *str, int *sw, int *i)
{
	if (str[*i] == str[*i + 1])
	{
		*sw = 1;
		*i += 2;
	}
}

char	*splited_str(char *str, int *j)
{
	int		i;
	char	*s;
	int		sw;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	s = malloc(i + 1);
	if (!s)
		return (0);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		sw = 0;
		if (str[i] == '\'' || str[i] == '"')
			decale_index(str, &sw, &i);
		if (sw == 1)
			s[i - 2] = str[i];
		else
			s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	*j = *j + i;
	return (s);
}
