#include "libft.h"

static size_t	ft_sublen(char const *s, unsigned int start, size_t len)
{
	size_t	ii;
	size_t	sublen;

	ii = 0;
	sublen = 0;
	while (s[ii] && ii < start)
		ii++;
	while (s[ii] && sublen < len)
	{
		ii++;
		sublen++;
	}
	return (sublen);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	sublen;
	size_t	ii;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	ii = 0;
	sublen = ft_sublen(s, start, len);
	sub = malloc((sizeof(char) * sublen) + 1);
	if (!sub)
		return (NULL);
	while (s[start + ii] && ii < sublen)
	{
		sub[ii] = s[start + ii];
		ii++;
	}
	sub[ii] = '\0';
	return (sub);
}