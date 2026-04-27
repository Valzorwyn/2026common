#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*res;

	res = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strcpy(res, src);
	return (res);
}