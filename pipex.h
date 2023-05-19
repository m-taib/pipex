/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:15:34 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/19 08:45:12 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include  <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void				ft_putstr(char *s, int fd);
char				*joined_arg(char *s, int *j);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, int len);
char				**ft_split2(char *s, char c);
int					count(char *s, char c);
char				**ft_split(char *s, char c);
void				free_array(char **str, int i);
int					ft_strlen(char *s);
int					word_len(char *s, char c);
int					ft_strlcpy(char *dst, char *src, int dstsize);
char				*ft_strdup(char *s1);

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_elements
{
	int				infd;
	int				outfd;
	int				ac;
	char			*cmd_path;
	char			**env;
	int				prev[2];
	int				next[2];
	int				fd[2];
	char			*str;
	int				her[2];
	int				state;
	char			**her_doc;
	int				*pid;
	char			**cmds;
	t_list			*head;
}					t_elements;

void				execute_child(t_list *args, int i, t_elements *ptr);
void				ft_exit(char *str, t_elements *ptr);
void				open_files(char **av, t_elements *ptr, int ac);
void				read_and_write(t_elements *ptr);
void				read_and_write2(t_elements *ptr, int i);
void				exit_error(char *cmd, t_elements *ptr);
void				exec_heredoc(t_elements *ptr, int pid);
char				*splited_str(char *str, int *j);
char				**cmd_args(t_list *head);
void				free_list(t_list *head);
char				*check_path(char **env, char *cmd);
char				*get_and_check_path(t_list *head, char **env);
int					open_file(char *file_name, char *file_type, int state);
void				ft_exec(t_elements *ptr, char **av, char **env);
int					ft_strcmp(char *s1, char *s2);
int					check_newline(char *str);
char				*get_str(int i, char *line);
char				*get_line(void);
void				execute_command(t_list *args, int i, t_elements *ptr);
t_list				*get_commands(char *str);
t_list				*ft_lstnew(char *content);
void				ft_lstadd_back(t_list **head, char *str);
#endif
