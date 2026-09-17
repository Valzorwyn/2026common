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
	return (c == delimiter);
}

static int	ft_split_sep_count(char const *str, char c)
{
	int	count;
	int	new_word;

	count = 0;
	new_word = 0;
	while (*str)
	{
		if (!ft_split_is_sep(*str, c) && !new_word)
		{
			new_word = 1;
			count++;
		}
		else if (ft_split_is_sep(*str, c))
			new_word = 0;
		str++;
	}
	return (count);
}

static char	*ft_split_strdup(char const *src, char c)
{
	int		src_len;
	int		ii;
	char	*word;

	src_len = 0;
	while (src[src_len] && !ft_split_is_sep(src[src_len], c))
		src_len++;
	word = malloc((src_len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ii = 0;
	while (ii < src_len)
	{
		word[ii] = src[ii];
		ii++;
	}
	word[src_len] = '\0';
	return (word);
}

static char	**ft_split_free(char **res, int n)
{
	while (n--)
		free(res[n]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		ii;
	int		jj;

	res = malloc((ft_split_sep_count(str, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	ii = 0;
	jj = 0;
	while (str[ii])
	{
		while (str[ii] && ft_split_is_sep(str[ii], c))
			ii++;
		if (str[ii] && !ft_split_is_sep(str[ii], c))
		{
			res[jj] = ft_split_strdup(&str[ii], c);
			if (!res[jj])
				return (ft_split_free(res, jj));
			jj++;
			while (str[ii] && !ft_split_is_sep(str[ii], c))
				ii++;
		}
	}
	return (res[jj] = NULL, res);
}
