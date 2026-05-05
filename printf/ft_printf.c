#include "ft_printf.h"

int	printf_putchr(int c);
int	printf_formcheck(const char format_specifier, va_list args);

int	ft_printf(const char *form, ...)
{
	int		ii;
	int		lensum;
	va_list	args;

	if (!form)
		return (-1);
	va_start (args, form);
	ii = -1;
	lensum = 0;
	while (form[++ii])
	{
		if (form[ii] != '%')
			lensum += printf_putchr(form[ii]);
		else
		{
			if (form[ii + 1] == '\0')
				return (va_end(args), -1);
			lensum += printf_formcheck(form[ii + 1], args);
			ii++;
		}
	}
	va_end(args);
	return (lensum);
}

int	printf_putchr(int c)
{
	write(1, &c, 1);
	return (1);
}

int	printf_formcheck(const char format_specifier, va_list args)
{
	int	len;

	len = 0;
	if (format_specifier == 'c')
		len += printf_putchr(va_arg(args, int));
	else if (format_specifier == 's')
		len += printf_s(va_arg(args, char *));
	else if (format_specifier == 'p')
		len += printf_p(va_arg(args, void *));
	else if (format_specifier == 'd' || format_specifier == 'i')
		len += printf_d(va_arg(args, int));
	else if (format_specifier == 'u')
		len += printf_u(va_arg(args, unsigned int));
	else if (format_specifier == 'x')
		len += printf_x_low(va_arg(args, unsigned int));
	else if (format_specifier == 'X')
		len += printf_x_upper(va_arg(args, unsigned int));
	else if (format_specifier == '%')
		len += printf_putchr('%');
	else
		return (0);
	return (len);
}
