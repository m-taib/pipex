/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:30:24 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/27 18:25:52 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		last_index(char *s)
{
	int		i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == '\'' || s[i] == '"')
			return (i);
		i--;
	}
	return (-1);
}

char	*joined_arg(char *s,int		*j)
{
	int		i;
	char 	c;
	char	*line;
	char	*s2;

	s2 = malloc(2);
	s2[1] = '\0';
	line = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			c = s[i++];
			while (s[i] && s[i] != c)
			{
				s2[0] = s[i];
				if (s[i] != c)
					line = ft_strjoin(line, s2);
				i++;
			}
		}
		/*else
		{
			if (s[i])
			{
				s2[0] = s[i];
				line = ft_strjoin(line,s2);
			}
		}*/
		i++;

	}
	*j = i;
	return (line);
}

char	*splited_str(char	*str, int 	*j)
{
	int		i;
	char	*s;
	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	s = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		s[i] = str[i];
		i++;
	}
	*j = *j + i;
	return (s);
}

t_list	*get_commands(char	*str)
{
	int		i;
	int		start;
	t_list	*cmds;
	int		j;

	start = 0;
	i = 0;
	cmds = NULL;
	while (str[i])
	{
		j = 0;
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
		{
			ft_lstadd_back(&cmds, joined_arg(&str[i], &j));	
			i = i + j;
		}
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] != '\'' && str[i] != '"')
		{
			ft_lstadd_back(&cmds, splited_str(&str[i], &i));
		}
	}
	return (cmds);
}

t_list	*ft_lstnew(char *content)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (0);
	newnode->content = content;
	newnode->next = 0;
	return (newnode);
}

void	ft_lstadd_back(t_list **head, char *str)
{
	t_list	*newnode;
	t_list	*tmp;

	tmp = *head;
	newnode = ft_lstnew(str);
	if (!*head)
	{
		*head = newnode;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newnode;
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int				j;
	int				i;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
