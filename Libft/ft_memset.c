void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (0 < n--)
		*ptr++ = c;
	return (s);
}