/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:32:57 by bajankov          #+#    #+#             */
/*   Updated: 2026/04/28 17:32:57 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_is_sep(char c, char delimiter)
{
	if (c == delimiter)
		return (1);
	return (0);
}

static int	ft_split_sep_count(char const *str, char c)
{
	int	ii;
	int	sep_count;

	sep_count = 0;
	ii = 0;
	while (str[ii])
	{
		if (!ft_split_is_sep(str[ii], c))
		{
			sep_count++;
			while (str[ii] && !ft_split_is_sep(str[ii], c))
				ii++;
		}
		else
		{
			ii++;
		}
	}
	return (sep_count);
}

static char	*ft_split_strdup(char const *src, char c)
{
	int		src_len;
	int		ii;
	char	*word;

	src_len = 0;
	while (src[src_len] && !ft_split_is_sep(src[src_len], c))
		src_len++;
	word = malloc((src_len + 1) * sizeof (char));
	if (!word)
		return (NULL);
	ii = -1;
	while (++ii < src_len)
		word[ii] = src[ii];
	return (word[src_len] = '\0', word);
}

char	**ft_split(char const *str, char c)
{
	int		ii;
	int		jj;
	int		sep_count;
	char	**res;

	sep_count = ft_split_sep_count(str, c);
	ii = 0;
	jj = 0;
	res = malloc((sep_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (str[ii])
	{
		while (str[ii] && ft_split_is_sep(str[ii], c))
			++ii;
		while (str[ii] && !ft_split_is_sep(str[ii], c))
		{
			res[jj++] = ft_split_strdup(&str[ii], c);
			while (str[ii] && !ft_split_is_sep(str[ii], c))
				++ii;
		}
	}
	return (res[jj] = NULL, res);
}
