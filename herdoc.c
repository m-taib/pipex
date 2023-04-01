/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:14:46 by mtaib             #+#    #+#             */
/*   Updated: 2023/04/01 19:50:54 by mtaib            ###   ########.fr       */
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

void	reset(int  i, t_elements *ptr)
{
	if (i > 2)
	{
		close(ptr->prev[0]);
		close(ptr->prev[1]);
	}
	if (i >= 2 && i < ptr->ac - 1)
	{	
		ptr->prev[0] = ptr->next[0];
		ptr->prev[1] = ptr->next[1];
	}
}

char	**cmd_args(t_list *head)
{
	int		i;
	t_list *tmp;
	char	**str;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (head)
	{
		str[i] = ft_strdup(head->content);
		i++;
		head = head->next;
	}
	str[i] = NULL;
	return (str);
}
void	execute_command(t_list *args, int i, t_elements *ptr)
{
	t_list 	*tmp;
	char	**cmds;
	int		pid;
	int		j;

	j = 0;
	tmp = args;
	pid = 1;
	cmds = cmd_args(args);
	if (ptr->state)
		{
			pid = fork();
			if (pid == 0)
			{
				close(ptr->her[0]);
				j = 0;
				ptr->her_doc = ft_split(ptr->str, ' ');
				while (ptr->her_doc[j])
				{
					ft_putstr(ptr->her_doc[j], ptr->her[1]);
					ft_putstr("\n",ptr->her[1]);
					j++;
				}
				close(ptr->her[1]);
				exit(0);
			}
			else
			{
				close(ptr->her[1]);
			}
		}
	if (i < ptr->ac - 2)
		pipe(ptr->next);
	pid = fork();
	if (pid == 0)
	{
		if (i == 2 || ptr->state)
		{
			if (ptr->state)
			{
				//ft_putstr("ffff",1);
				//close(ptr->her[1]);	
				dup2(ptr->her[0],0);
			}
			else
			{
				dup2(ptr->infd , 0);
				close(ptr->infd);
			}
			dup2(ptr->next[1], 1);
			close(ptr->next[1]);
			close(ptr->next[0]);
			if (ptr->state)
				close(ptr->her[0]);	
		}
		else 
		{
			dup2(ptr->prev[0] , 0);
			close(ptr->prev[1]);
			close(ptr->prev[0]);
			if (i == ptr->ac - 2)
			{
				dup2(ptr->outfd , 1);
				close(ptr->outfd);
			}
			else
			{
				dup2(ptr->next[1] , 1);
				close(ptr->next[1]);
				close(ptr->next[0]);
			}
		}
		if (execve(ptr->cmd_path, cmds, ptr->env) == -1)
			perror("execve");
		exit(127);
	}
	reset(i, ptr);
}

char	*cmd_path(char	*str)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	s = malloc(i+1);
   	if (!s)
		return (0);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		s[i] = str[i];
		i++;
	}	
	return (s);
}

int		ft_strcmp(char	*s1, char	*s2)
{
	int		i;

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

int		main(int ac, char **av, char **ev)
{
	char	**args;
	int		i;
	t_list *head;
	char	*cmd;
	t_elements	*ptr;
	char	*s;
	ptr = malloc(sizeof(t_elements));
	if (!ptr)
		return (0);	
	ptr->infd = open(av[1],O_RDWR);	
	ptr->outfd = open(av[ac-1],O_RDWR | O_TRUNC | O_CREAT);
	i = 2;
	if (ac < 5)
		return (1);
	args = NULL;
	ptr->ac = ac;
	s = NULL;
	ptr->str = NULL;
	while (i < ac - 1)
	{
		ptr->state = 0;
		if (!ft_strcmp(av[1],"here_doc") && i == 2)
		{
			pipe(ptr->her);
			ptr->state = 1;
			s = get_line();
			while (1)
			{
				if (!ft_strcmp(av[2],s))
				{
					if (!ptr->str)
						ptr->str = ptr->str;
					break;
				}
				ptr->str = ft_strjoin(ptr->str, s);
				ptr->str = ft_strjoin(ptr->str, " ");
				s = get_line();
			}
			i++;
		}
		head = get_commands(av[i]);
		cmd = ft_strjoin(ft_strdup("/"), head->content);
		if (av[i][0] == '.' && av[i][1] == '/')
			ptr->cmd_path = cmd_path(av[i]);
		else if (av[i][0] == '/')
		{
			ptr->cmd_path = cmd_path(av[i]);
			ptr->cmd_path = path(&av[i]);
		}
		else
		{	
			args = get_path(ev);
			args = get_cmd_paths(args, cmd);
			ptr->cmd_path = path(args);
		}
		execute_command(head, i, ptr);
		i++;
	}
	i = -1;
	close(ptr->infd);
	close(ptr->outfd);
	close(ptr->next[0]);
	close(ptr->next[1]);
	close(ptr->prev[0]);
	close(ptr->prev[1]);
	close(ptr->her[0]);
	close(ptr->her[1]);
	while (++i <= ac -1)
		wait(NULL);
	//(void)cmd;
	//(void)ev;
	//while (i < ac - 1)
	//{
		/*head = get_commands(av[2]);
		while (head)
		{
			printf("%s\n",head->content);
			head = head->next;
		}*/
	//	i++;
	//}
	/*exit(0);
	cmd = ft_strjoin(ft_strdup("/"), head->content);
	args = get_path(ev);
	args = get_cmd_paths(args, cmd);
	ptr->cmd_path = path(args);
	execute_command(head, i, ptr);*/
	return (0);
}
