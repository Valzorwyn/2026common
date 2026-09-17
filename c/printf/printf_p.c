#include "ft_printf.h"

int	printf_p(void *ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += printf_s("(nil)");
	else
	{
		len += printf_s("0x");
		len += printf_x_low((unsigned long)ptr);
	}
	return (len);
}
