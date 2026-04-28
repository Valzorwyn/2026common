/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:33:07 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:33:07 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*res;

	res = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, src, ft_strlen(src) + 1);
	return (res);
}
