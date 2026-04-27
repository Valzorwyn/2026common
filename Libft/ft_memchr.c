void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	cc;

	cc = c;
	ptr = (unsigned char *)s;
	while (n--)
	{
		if (*ptr == cc)
			return (ptr);
		ptr++;
	}
	return (0);
}