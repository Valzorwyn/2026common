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
