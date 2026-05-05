#include "ft_printf.h"

int	printf_d(int n)
{
	char	c;
	int		len;

	len = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		len++;
	}
	if (n > 9)
		len += printf_d(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
	len++;
	return (len);
}
