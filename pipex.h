/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:15:34 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/30 15:11:43 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <wait.h>

int		last_index(char *s);
char	*joined_arg(char *s, int	*j);
void	*ft_calloc(int count, int size);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split3(char *s, char c);
int		ft_strncmp(char *s1, char *s2, int len);
char	**ft_split2(char *s, char c);
int		count(char *s, char c);
char	**ft_split(char *s, char c);
void	free_array(char **str);
int		ft_strlen(char *s);
int		word_len(char *s, char c);
int		ft_strlcpy(char *dst, char *src, int dstsize);
char	**get_path(char **ev);
char    **get_cmd_paths(char **args, char *cmd);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, int start, int len);
char	*path(char **args);
typedef struct s_list 
{
	char	*content;
	struct s_list *next;
} t_list;
typedef struct s_elements
{
	int		infd;
	int		outfd;
	int		ac;
	char	*cmd_path;
	char	**env;
	int		prev[2];
	int		next[2];
	int		fd[2];
	char	*str;
	int		her[2];
	int		state;
	char	**her_doc;
	t_list	*head;
}	t_elements;
int	ft_strcmp(char *s1, char *s2);
int	check_newline(char *str);
char	*get_str(int i, char *line);
char	*get_line(void);
char	*cmd_path(char	*str);
void    execute_command(t_list *args, int i, t_elements *ptr);
void    execute_command1(t_list *args, int i, t_elements *ptr);
t_list	*get_commands(char	*str);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **head, char *str);
#endif
