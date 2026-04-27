#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
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

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		ii;
	int		sum_len;
	char	*res;

	if (size == 0)
		return (ft_calloc(1, 1));
	if (size < 0)
		return (NULL);
	ii = -1;
	sum_len = 0;
	while (++ii < size)
		sum_len += ft_strlen(strs[ii]);
	sum_len += (ft_strlen(sep) * (size - 1));
	res = ft_calloc((sum_len + 1), sizeof(char));
	ii = -1;
	while (++ii < size)
	{
		ft_strcat(res, strs[ii]);
		if (ii < size - 1)
			ft_strcat(res, sep);
	}
	return (res);
}
