int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	ii;

	ii = 0;
	while (ii < n && s1[ii] && s2[ii] && s1[ii] == s2[ii])
		ii++;
	if (ii == n)
		return (0);
	return ((unsigned char)(s1[ii]) - (unsigned char)(s2[ii]));
}
