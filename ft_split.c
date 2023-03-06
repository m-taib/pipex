/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:23:52 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/06 16:27:03 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	check(char c, char ch)
{
	if (c == ch)
		return (0);
	return (1);
}

int	count(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && !check(s[i], c))
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && check(s[i], c) && s[i] != '\'')
			i++;
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			i++;
		}
	}
	return (count);
}

int	word_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && check(s[i], c))
		i++;
	return (i);
}

char	*fill_word(char *s, int len, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(len + 1);
	if (!str)
		return (0);
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		i;

	if (!s1)
		return (0);
	i = 0;
	ptr = malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

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

char	*joined_arg(char *s)
{
	int		i;
	char	*arg;
	char 	c;
	char	*line;
	char	*s2;

	s2 = malloc(2);
	s2[1] = '\0';
	line = NULL;
	i = last_index(s);
	arg = ft_substr(s, 0, i+1);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
			c = arg[i++];
		while (arg[i] && arg[i] != c)
		{
			s2[0] = arg[i];
			line = ft_strjoin(line, s2);
			i++;
		}
		i++;
	}
	return (line);
}	

char	**ft_split3(char *s, char c)
{
	char	**str;
	int		i[2];
	char	*line;
	int		r;
	char	*ss;
	r = 0;
	line = NULL;
	if (!s)
		return (0);
	str = malloc(sizeof(char *) * (count(s, c) + 1));
	if (!str)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (s[i[0]] && i[1] < count(s, c))
	{
		while (s[i[0]] && !check(s[i[0]], c))
			i[0]++;
		if (s[i[0]] == '\'' || s[i[0]] == '"')
		{
			r = 1;
			ss = &s[i[0]];
			str[i[1]++] = joined_arg(&s[i[0]]);	
			i[0] += last_index(&s[i[0]]) + 1;
			//printf("%c",s[i[0]]);
			//exit(0);
			if (!s[i[0]])
				break;
		}
		if (r == 0)
		{
			str[i[1]] = malloc(word_len((&s[i[0]]), c) + 1);
			if (!str[i[1]])
				return (NULL);
		}
		if (s[i[0]])
		{
			if (r == 0)
			{
				str[i[1]++] = fill_word(&s[i[0]], word_len(&s[i[0]], c), c);
				i[0] += word_len(&s[i[0]], c);
			}
			r = 0;
		}
	}
	str[i[1]] = NULL;
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		i[2];

	if (!s)
		return (0);
	str = malloc(sizeof(char *) * (count(s, c) + 1));
	if (!str)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (s[i[0]] && i[1] < count(s, c))
	{
		while (s[i[0]] && !check(s[i[0]], c))
			i[0]++;
		if (s[i[0]] == '"' && s[i[0] + 1] == '\'')
		{
			c = '"';
			i[0]++;	
		}
		if (s[i[0]] == '\'' && s[i[0] - 1] != '"')
		{
			c = '\'';
			i[0]++;
		}
		str[i[1]] = malloc(word_len((&s[i[0]]), c) + 1);
		if (!str[i[1]])
			return (NULL);
		if (s[i[0]])
		{
			if (c == '\'')
			{
				while (s[i[0]] && s[i[0]] == '"')
					i[0]++;
				str[i[1]++] = fill_word(&s[i[0]], word_len(&s[i[0]], '\''), c);
			}
			else
				str[i[1]++] = fill_word(&s[i[0]], word_len(&s[i[0]], c), c);
			i[0] += word_len(&s[i[0]], c);
			while (s[i[0]] == '"' || s[i[0]] == '\'')
			   i[0]++;	
			c = ' ';
		}
	}
	str[i[1]] = NULL;
	return (str);
}
