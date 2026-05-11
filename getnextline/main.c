#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	fd = open("test.txt", O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		++count;
		printf("[%d]:%s", count, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
