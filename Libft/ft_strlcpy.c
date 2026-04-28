/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:33:24 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:33:24 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	ii;

	ii = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[ii] && ii < size - 1)
	{
		dest[ii] = src[ii];
		ii++;
	}
	dest[ii] = '\0';
	return (ft_strlen(src));
}
