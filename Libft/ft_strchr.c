char	*ft_strchr(const char *s, int c)
{
	int	ii;

	ii = 0;
	while (s[ii] && c != s[ii])
		ii++;
	if (s[ii] == c)
		return ((char *)s[ii]);
	return (0);
}
