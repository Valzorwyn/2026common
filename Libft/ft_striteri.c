void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	ii;

	ii = 0;
	while (s[++ii])
		(*f)(ii, &s[ii]);
}
