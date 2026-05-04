/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:33:20 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:33:20 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	ii;

	dest_len = 0;
	src_len = ft_strlen(src);
	ii = 0;
	while ((dest_len < size) && (dst[dest_len] != '\0'))
		dest_len++;
	if (dest_len == size)
		return (size + src_len);
	while (ii < size - dest_len - 1 && src[ii] != '\0')
	{
		dst[dest_len + ii] = src[ii];
		ii++;
	}
	dst[dest_len + ii] = '\0';
	return (dest_len + src_len);
}
