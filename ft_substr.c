/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:49:33 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/06 15:06:25 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(int count, int size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*ft_substr(char *s, int start, int len)
{
	unsigned char	*str;
	unsigned char	*ptr;
	int				j;
	int				i;

	ptr = (unsigned char *)s;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (ptr[i] && j < len)
	{
		str[j] = ptr[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return ((char *)str);
}
