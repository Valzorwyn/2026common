static int	ft_iswspace(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int			ii;
	int			sign;
	int			result;

	sign = 1;
	ii = 0;
	result = 0;
	while (ft_iswspace(nptr[ii]))
		ii++;
	if (nptr[ii] == '+' || nptr[ii] == '-')
	{
		if (nptr[ii] == '-')
			sign *= -1;
		ii++;
	}
	ii--;
	while (ft_isdigit(nptr[++ii]))
		result = (result * 10) + (nptr[ii] - '0');
	return (result * sign);
}
