#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	ii;

	ii = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[ii] && ii < size - 1)
	{
		dest[ii] = src[ii];
		ii++;
	}
	dest[ii] = '\0';
	return (ft_strlen(src));
}
