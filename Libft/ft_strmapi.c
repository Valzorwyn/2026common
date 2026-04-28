/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:33:32 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:33:32 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		ii;

	result = malloc((ft_strlen(s) * sizeof(char)) + 1);
	if (!result)
		return (NULL);
	ii = -1;
	while (s[++ii])
		result[ii] = (*f)(ii, s[ii]);
	result[ii] = '\0';
	return (result);
}
