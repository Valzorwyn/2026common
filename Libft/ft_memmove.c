/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:32:27 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:32:27 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	if (ptr_dst < ptr_src)
		while (0 < len--)
			*ptr_dst++ = *ptr_src++;
	else
	{
		ptr_dst += len;
		ptr_src += len;
		while (0 < len--)
			*(--ptr_dst) = *(--ptr_src);
	}
	return (dst);
}
