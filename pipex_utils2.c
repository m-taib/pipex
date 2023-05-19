/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:30:24 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/19 08:44:14 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_and_write(t_elements *ptr)
{
	if (ptr->state)
	{
		if (dup2(ptr->her[0], 0) == -1)
			ft_exit("failed to duplicate the file descriptor", ptr);
	}
	else
	{
		if (ptr->infd > 0)
		{
			if (dup2(ptr->infd, 0) == -1)
				ft_exit("failed to duplicate the file descriptor", ptr);
			close(ptr->infd);
		}
	}
	if (dup2(ptr->next[1], 1) == -1)
			ft_exit("failed to duplicate the file descriptor", ptr);
	close(ptr->next[1]);
	close(ptr->next[0]);
	if (ptr->state)
		close(ptr->her[0]);
}

void	read_and_write2(t_elements *ptr, int i)
{
	if (dup2(ptr->prev[0], 0) == -1)
			ft_exit("failed to duplicate the file descriptor", ptr);
	close(ptr->prev[1]);
	close(ptr->prev[0]);
	if (i == ptr->ac - 2)
	{
		if (ptr->outfd == -1)
			exit(1);
		if (dup2(ptr->outfd, 1) == -1)
			ft_exit("failed to duplicate the file descriptor", ptr);
		close(ptr->outfd);
	}
	else
	{
		if (dup2(ptr->next[1], 1) == -1)
			ft_exit("failed to duplicate the file descriptor", ptr);
		close(ptr->next[1]);
		close(ptr->next[0]);
	}
}

t_list	*get_commands(char *str)
{
	int		i;
	t_list	*cmds;
	int		j;

	i = 0;
	cmds = NULL;
	while (str && str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (NULL);
	i = 0;
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
			ft_lstadd_back(&cmds, splited_str(&str[i], &i));
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
