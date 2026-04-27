#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	ii;

	ii = 0;
	while (s[ii])
		ii++;
	return (ii);
}
