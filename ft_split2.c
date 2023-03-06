/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:29:17 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/06 08:29:26 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static int	check(char c, char ch)
{
	if (c == ch)
		return (0);
	return (1);
}

int	count2(char *s, char c)
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
		while (s[i] && check(s[i], c))
			i++;
	}
	return (count);
}

char	**ft_split2(char *s, char c)
{
	char	**str;
	int		i[2];

	if (!s)
		return (0);
	str = malloc(sizeof(char *) * (count2(s, c) + 1));
	if (!str)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (s[i[0]] && i[1] < count2(s, c))
	{
		while (s[i[0]] && !check(s[i[0]], c))
			i[0]++;
		str[i[1]] = malloc(word_len((&s[i[0]]), c) + 1);
		if (!str[i[1]])
			return (NULL);
		if (s[i[0]])
		{
			ft_strlcpy(str[i[1]++], &s[i[0]], word_len(&s[i[0]], c) + 1);
			i[0] += word_len(&s[i[0]], c);
		}
	}
	str[i[1]] = NULL;
	return (str);
}
