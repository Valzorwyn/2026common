/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:33:50 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:33:50 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	ii;

	ii = ft_strlen(s);
	while (ii > 0 && (unsigned char)c != s[ii])
		ii--;
	if (s[ii] == (unsigned char)c)
		return ((char *)&s[ii]);
	return (0);
}
