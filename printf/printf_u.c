#include "ft_printf.h"

int	printf_u(unsigned int n)
{
	char	c;
	int		len;

	len = 0;
	if (n > 9)
		len += printf_u(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
	len++;
	return (len);
}
