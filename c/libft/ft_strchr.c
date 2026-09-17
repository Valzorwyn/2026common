/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:33:03 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:33:03 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	ii;

	ii = 0;
	while (s[ii] && (unsigned char)c != s[ii])
		ii++;
	if (s[ii] == (unsigned char)c)
		return ((char *)&s[ii]);
	return (0);
}
