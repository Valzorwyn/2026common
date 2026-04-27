#include "libft.h"

static int	ft_intlen(int n)
{
	long	ln;
	int		len;

	ln = n;
	len = 0;
	if (ln < 0)
	{
		ln *= -1;
		len++;
	}
	if (ln == 0)
		len++;
	while (ln > 0)
	{
		len++;
		ln /= 10;
	}
	return (len);
}

static void	ft_bzerochar(void *s, size_t n)
{
	size_t	ii;
	char	*ptr;

	ptr = (char *)s;
	ii = 0;
	while (ii < n)
	{
		ptr[ii] = '0';
		ii++;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		ii;
	long	ln;

	ln = n;
	len = ft_intlen(ln);
	result = malloc((len * sizeof(char)) + 1);
	if (!result)
		return (NULL);
	ft_bzerochar(result, len);
	if (!result)
		return (NULL);
	if (ln < 0)
		ln *= -1;
	ii = len - 1;
	while (ln != 0)
	{
		result[ii] = (ln % 10) + '0';
		ln /= 10;
		ii--;
	}
	if (n < 0)
		result[0] = '-';
	return (result[len] = '\0', result);
}