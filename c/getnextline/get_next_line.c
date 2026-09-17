/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajankov <bajankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:34:01 by bjankovi          #+#    #+#             */
/*   Updated: 2026/06/21 16:46:08 by bajankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*getnext_strchr(const char *s, int c)
{
	int	ii;

	ii = -1;
	while (s[++ii])
	{
		if (s[ii] == (char)c)
			return ((char *)&s[ii]);
	}
	if (s[ii] == (char)c)
		return ((char *)&s[ii]);
	return (0);
}

/*
	Loops calling read(fd, buf, BUFFER_SIZE) 
		and appending each chunk to the stash via getnext_strjoin
		(which frees the old stash each time,
		so you never have two copies alive at once).
	Stops as soon as a \n is found in the stash,
		or read returns 0 (EOF) or -1 (error).
*/

static char	*read_until_newline(int fd, char **stash)
{
	char	*buf;
	int		bytes_read;

	if (!*stash)
	{
		*stash = getnext_calloc(1, 1);
		if (!*stash)
			return (NULL);
	}
	buf = getnext_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (free(*stash), *stash = NULL, NULL);
	bytes_read = 1;
	while (!getnext_strchr(*stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, (size_t)BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buf), free(*stash), *stash = NULL, NULL);
		buf[bytes_read] = '\0';
		*stash = getnext_strjoin(*stash, buf);
		if (!*stash)
			return (free(buf), NULL);
	}
	return (free(buf), *stash);
}

/*
	Scans the stash to find the end of the first line
		(up to and including \n, or to \0 at EOF), 
		allocates a new string, copies those characters in, and returns it.
	The stash is untouched.
*/
static char	*extract_line(char *stash)
{
	int		len;
	int		ii;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		++len;
	if (stash[len] == '\n')
		++len;
	line = getnext_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	ii = -1;
	while (++ii < len)
		line[ii] = stash[ii];
	return (line);
}

/*
	Frees the stash and returns a fresh allocation of everything after the \n.
	That becomes the new stash for the next call.
*/

static char	*save_remaining(char *stash)
{
	char	*after;
	char	*rest;
	int		ii;

	after = stash;
	while (after && *after && *after != '\n')
		++after;
	if (!after || !*after)
		return (free(stash), NULL);
	++after;
	rest = getnext_calloc(getnext_strlen(after) + 1, sizeof(char));
	if (!rest)
		return (free(stash), NULL);
	ii = -1;
	while (after[++ii])
		rest[ii] = after[ii];
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), stash = NULL, NULL);
	stash = read_until_newline(fd, &stash);
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	line = extract_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = save_remaining(stash);
	return (line);
}
