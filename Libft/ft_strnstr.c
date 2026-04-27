char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	ii;
	size_t	jj;

	ii = -1;
	if (little[0] == '\0')
		return ((char *) big);
	while (big[++ii] && ii < len)
	{
		jj = 0;
		while (big[ii + jj] == little[jj] && big [ii + jj] && ii + jj < len)
			jj++;
		if (little[jj] == '\0')
			return ((char *) big + ii);
	}
	return (0);
}
