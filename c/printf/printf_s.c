#include "ft_printf.h"

int	printf_s(char *str)
{
	int	ii;

	ii = -1;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else
	{
		while (str[++ii])
			write(1, &str[ii], 1);
		return (ii);
	}
}
