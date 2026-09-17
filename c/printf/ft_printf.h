#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

// helper
int	printf_putchr(int c);

// c %
int	ft_printf(const char *c, ...);

// s
int	printf_s(char *str);

// x X
int	printf_x_low(unsigned long n);
int	printf_x_upper(unsigned long n);

// p
int	printf_p(void *ptr);

// d i
int	printf_d(int n);

// u
int	printf_u(unsigned int n);

#endif