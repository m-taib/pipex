/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:15:34 by mtaib             #+#    #+#             */
/*   Updated: 2023/03/06 15:06:00 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		last_index(char *s);
char	*joined_arg(char *s);
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
#endif
