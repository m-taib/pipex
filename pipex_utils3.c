/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/17 15:30:54 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	check_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*get_str(int i, char *line)
{
	char	*buffer;

	buffer = malloc(2);
	buffer[0] = '\0';
	while (i && check_newline(buffer))
	{
		i = read(0, buffer, 1);
		if (i < 0)
		{
			free(buffer);
			return (0);
		}
		if (buffer)
			buffer[i] = '\0';
		line = ft_strjoin(line, buffer);
		if (!buffer[0])
		{
			free(buffer);
			free(line);
			return (0);
		}
	}
	free(buffer);
	return (line);
}

char	*get_line(void)
{
	char	*buffer;
	char	*line;
	int		i;

	i = 1;
	buffer = malloc(2);
	buffer[0] = '\0';
	line = NULL;
	line = get_str(i, line);
	if (!line)
	{
		free(buffer);
		free(line);
		return (0);
	}
	i = ft_strlen(line) - 1;
	line[i] = '\0';
	free(buffer);
	return (line);
}

char	**cmd_args(t_list *head)
{
	int		i;
	t_list	*tmp;
	char	**str;

	i = 0;
	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (head)
	{
		str[i] = head->content;
		i++;
		head = head->next;
	}
	str[i] = NULL;
	return (str);
}
