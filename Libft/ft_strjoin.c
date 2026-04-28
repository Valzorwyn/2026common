/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:33:15 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:33:15 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char const *src)
{
	int	ii;
	int	jj;

	ii = -1;
	while (dest[++ii])
		;
	jj = -1;
	while (src[++jj])
	{
		dest[ii] = src[jj];
		++ii;
	}
	return (dest[ii] = '\0', dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		ii;
	int		sum_len;
	char	*res;

	sum_len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc((sum_len + 1), sizeof(char));
	ii = -1;
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	return (res);
}
