#include "ft_printf.h"

int	printf_x_low(unsigned long n)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += printf_x_low(n / 16);
	len += printf_putchr("0123456789abcdef"[n % 16]);
	return (len);
}

int	printf_x_upper(unsigned long n)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += printf_x_upper(n / 16);
	len += printf_putchr("0123456789ABCDEF"[n % 16]);
	return (len);
}
