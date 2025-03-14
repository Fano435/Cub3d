/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:43:19 by jrasamim          #+#    #+#             */
/*   Updated: 2025/02/11 10:05:46 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, const char *s2);
char	*gnl_strchr(char *str, int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*get_next_line(int fd);

#endif