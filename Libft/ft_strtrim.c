#include "libft.h"

static int	ft_inset(char c, char const *set)
{
	int	ii;

	ii = -1;
	while (set[++ii])
	{
		if (c == set[ii])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		ii;
	int		jj;
	char	*new;
	int		len;

	len = ft_strlen(s1) - 1;
	ii = 0;
	jj = 0;
	while (s1[ii] && ft_inset(s1[ii], set))
		ii++;
	while (s1[len] && ft_inset(s1[len], set))
		len--;
	len++;
	new = ft_substr(s1, ii, len - ii - jj);
	return (new);
}