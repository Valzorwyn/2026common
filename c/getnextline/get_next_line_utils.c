/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:34:06 by bjankovi          #+#    #+#             */
/*   Updated: 2026/06/21 16:45:58 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*getnext_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	getnext_bzero(ptr, nmemb * size);
	return (ptr);
}

void	getnext_bzero(void *s, size_t n)
{
	size_t	ii;
	char	*ptr;

	ptr = (char *)s;
	ii = 0;
	while (ii < n)
	{
		ptr[ii] = 0;
		++ii;
	}
}

static void	getnext_concat(char *dst, char const *src, size_t start)
{
	int	ii;

	ii = -1;
	while (src[++ii])
		dst[start + ii] = src[ii];
}

char	*getnext_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	newsize;
	size_t	s1len;

	if (!s1 && !s2)
		return (NULL);
	s1len = 0;
	newsize = 0;
	if (s1)
		s1len = getnext_strlen(s1);
	if (s2)
		newsize = getnext_strlen(s2);
	newsize += s1len;
	new = malloc(newsize + 1);
	if (!new)
		return (free((void *)s1), NULL);
	if (s1)
		getnext_concat(new, s1, 0);
	if (s2)
		getnext_concat(new, s2, s1len);
	new[newsize] = '\0';
	free((void *)s1);
	return (new);
}

size_t	getnext_strlen(const char *s)
{
	size_t	ii;

	ii = 0;
	while (s[ii])
		++ii;
	return (ii);
}
