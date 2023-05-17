/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:24:21 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/17 16:07:00 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(char *cmd, t_elements *ptr)
{
	char	*str;

	str = "pipex: command not found: ";
	write(2, str, ft_strlen(str));
	if (cmd)
		write(2, &cmd[1], ft_strlen(cmd));
	write(2, "\n", 1);
	free_list(ptr->head);
	free(ptr->cmds);
	free(ptr->cmd_path);
	free(ptr->pid);
	free(ptr);
	exit(127);
}

int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	i;

	i = 0;
	if (!src || dstsize <= 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
