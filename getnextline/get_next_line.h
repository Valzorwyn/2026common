/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjankovi <bjankovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:33:55 by bjankovi          #+#    #+#             */
/*   Updated: 2025/08/15 18:33:55 by bjankovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

char	*get_next_line(int fd);
void	*getnext_calloc(size_t nmemb, size_t size);
void	getnext_bzero(void *s, size_t n);
char	*getnext_strjoin(char const *s1, char const *s2);
char	*getnext_strchr(const char *s, int c);
size_t	getnext_strlen(const char *s);

#endif