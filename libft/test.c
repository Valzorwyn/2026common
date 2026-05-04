#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "libft.h"

/* ==================== HELPERS ==================== */

static int	g_pass = 0;
static int	g_fail = 0;

static void	check(const char *fname, const char *test, int ok)
{
	if (ok)
	{
		printf("  [OK] %-20s | %s\n", fname, test);
		g_pass++;
	}
	else
	{
		printf("  [KO] %-20s | %s\n", fname, test);
		g_fail++;
	}
}

/* ==================== IS* / TO* ==================== */

static void	test_isalpha(void)
{
	check("ft_isalpha", "'a' is alpha",        ft_isalpha('a') && isalpha('a'));
	check("ft_isalpha", "'Z' is alpha",        ft_isalpha('Z') && isalpha('Z'));
	check("ft_isalpha", "'1' not alpha",       !ft_isalpha('1') && !isalpha('1'));
	check("ft_isalpha", "' ' not alpha",       !ft_isalpha(' ') && !isalpha(' '));
}

static void	test_isdigit(void)
{
	check("ft_isdigit", "'0' is digit",        ft_isdigit('0') && isdigit('0'));
	check("ft_isdigit", "'9' is digit",        ft_isdigit('9') && isdigit('9'));
	check("ft_isdigit", "'a' not digit",       !ft_isdigit('a') && !isdigit('a'));
	check("ft_isdigit", "':' not digit",       !ft_isdigit(':') && !isdigit(':'));
}

static void	test_isalnum(void)
{
	check("ft_isalnum", "'a' is alnum",        ft_isalnum('a') && isalnum('a'));
	check("ft_isalnum", "'5' is alnum",        ft_isalnum('5') && isalnum('5'));
	check("ft_isalnum", "'!' not alnum",       !ft_isalnum('!') && !isalnum('!'));
}

static void	test_isascii(void)
{

	check("ft_isascii", "0 is ascii (std)",     ft_isascii(0) && isascii(0));
	check("ft_isascii", "65 is ascii",         ft_isascii(65) && isascii(65));
	check("ft_isascii", "127 is ascii (std)",  ft_isascii(127) && isascii(127));
	check("ft_isascii", "200 not ascii (std)", !ft_isascii(200) && !isascii(200));
}

static void	test_isprint(void)
{
	check("ft_isprint", "' ' is print",        ft_isprint(' ') && isprint(' '));
	check("ft_isprint", "'~' is print",        ft_isprint('~') && isprint('~'));
	check("ft_isprint", "0x1f not print",      !ft_isprint(0x1f) && !isprint(0x1f));
	check("ft_isprint", "127 not print",       !ft_isprint(127) && !isprint(127));
}

static void	test_tolower(void)
{
	check("ft_tolower", "'A' -> 'a'",          ft_tolower('A') == tolower('A'));
	check("ft_tolower", "'Z' -> 'z'",          ft_tolower('Z') == tolower('Z'));
	check("ft_tolower", "'a' unchanged",       ft_tolower('a') == tolower('a'));
	check("ft_tolower", "'1' unchanged",       ft_tolower('1') == tolower('1'));
}

static void	test_toupper(void)
{
	check("ft_toupper", "'a' -> 'A'",          ft_toupper('a') == toupper('a'));
	check("ft_toupper", "'z' -> 'Z'",          ft_toupper('z') == toupper('z'));
	check("ft_toupper", "'A' unchanged",       ft_toupper('A') == toupper('A'));
	check("ft_toupper", "'1' unchanged",       ft_toupper('1') == toupper('1'));
}

/* ==================== MEM ==================== */

static void	test_memset(void)
{
	char	buf_ft[16];
	char	buf_std[16];

	memset(buf_std, 'x', 10); buf_std[10] = '\0';
	ft_memset(buf_ft, 'x', 10); buf_ft[10] = '\0';
	check("ft_memset", "fill 10 'x'",         strcmp(buf_ft, buf_std) == 0);
	memset(buf_std, 0, 16);
	ft_memset(buf_ft, 0, 16);
	check("ft_memset", "zero 16 bytes",        memcmp(buf_ft, buf_std, 16) == 0);
}

static void	test_bzero(void)
{
	char	buf[8] = "hello!!";

	ft_bzero(buf, 5);
	check("ft_bzero", "zeroes first 5 bytes", buf[0] == 0 && buf[4] == 0);
	check("ft_bzero", "leaves byte 5 alone",  buf[5] == '!' );
}

static void	test_memcpy(void)
{
	char	dst[16];
	char	src[] = "hello";

	ft_memcpy(dst, src, 6);
	check("ft_memcpy", "copies hello\\0",      strcmp(dst, "hello") == 0);
	ft_memcpy(dst, "abc", 3);
	check("ft_memcpy", "copies 3 bytes",       memcmp(dst, "abc", 3) == 0);
}

static void	test_memmove(void)
{
	char	buf[16] = "hello";

	ft_memmove(buf + 2, buf, 5);
	check("ft_memmove", "overlapping fwd",     memcmp(buf + 2, "hello", 5) == 0);
	char	buf2[16] = "hello";
	ft_memmove(buf2, buf2 + 1, 4);
	check("ft_memmove", "overlapping bwd",     memcmp(buf2, "ello", 4) == 0);
}

static void	test_memchr(void)
{
	char	s[] = "hello";

	check("ft_memchr", "find 'l'",             ft_memchr(s, 'l', 5) == memchr(s, 'l', 5));
	check("ft_memchr", "not found",            ft_memchr(s, 'z', 5) == memchr(s, 'z', 5));
	check("ft_memchr", "n=0 not found",        ft_memchr(s, 'h', 0) == memchr(s, 'h', 0));
}

static void	test_memcmp(void)
{
	check("ft_memcmp", "equal",   ft_memcmp("abc", "abc", 3) == 0);
	check("ft_memcmp", "less",    ft_memcmp("abc", "abd", 3) < 0);
	check("ft_memcmp", "greater", ft_memcmp("abd", "abc", 3) > 0);
	check("ft_memcmp", "n=0",     ft_memcmp("abc", "xyz", 0) == 0);
}

static void	test_calloc(void)
{
	int	*arr;
	int	ii;
	int	all_zero;

	arr = ft_calloc(5, sizeof(int));
	ii = -1;
	all_zero = 1;
	while (++ii < 5)
		if (arr[ii] != 0)
			all_zero = 0;
	check("ft_calloc", "5 ints zeroed",        all_zero);
	free(arr);
	check("ft_calloc", "nmemb=0 not NULL",     ft_calloc(0, 4) != NULL);
}

/* ==================== STR ==================== */

static void	test_strlen(void)
{
	check("ft_strlen", "\"hello\" == 5",       ft_strlen("hello") == strlen("hello"));
	check("ft_strlen", "\"\" == 0",            ft_strlen("") == strlen(""));
	check("ft_strlen", "\"abc\" == 3",         ft_strlen("abc") == strlen("abc"));
}

static void	test_strchr(void)
{
	char	s[] = "hello";

	check("ft_strchr", "find 'e'",			ft_strchr(s, 'e') == strchr(s, 'e'));
	check("ft_strchr", "not found NULL",	ft_strchr(s, 'z') == NULL);
	check("ft_strchr", "find '\\0'",		ft_strchr(s, '\0') == strchr(s, '\0'));
}

static void	test_strrchr(void)
{
	char	s[] = "hello";

	check("ft_strrchr", "find last 'l'",  	ft_strrchr(s, 'l') == strrchr(s, 'l'));
	check("ft_strrchr", "not found NULL",   ft_strrchr(s, 'z') == NULL);
}

static void	test_strncmp(void)
{
	check("ft_strncmp", "equal n=3",           ft_strncmp("abc", "abc", 3) == 0);
	check("ft_strncmp", "less",                ft_strncmp("abc", "abd", 3) < 0);
	check("ft_strncmp", "greater",             ft_strncmp("abd", "abc", 3) > 0);
	check("ft_strncmp", "n=0",                 ft_strncmp("abc", "xyz", 0) == 0);
	check("ft_strncmp", "prefix shorter",      (ft_strncmp("ab", "abc", 3) < 0)
	                                           == (strncmp("ab", "abc", 3) < 0));
}

static void	test_strlcpy(void)
{
	char	dst_ft[16];
	char	dst_std[16];
	size_t	r_ft;
	size_t	r_std;

	r_ft  = ft_strlcpy(dst_ft,  "hello", 16);
	r_std = strlcpy(dst_std, "hello", 16);
	check("ft_strlcpy", "copies hello, ret 5", r_ft == r_std && strcmp(dst_ft, dst_std) == 0);

	r_ft  = ft_strlcpy(dst_ft,  "hello", 3);
	r_std = strlcpy(dst_std, "hello", 3);
	check("ft_strlcpy", "truncates to 2+\\0",  r_ft == r_std && strcmp(dst_ft, dst_std) == 0);

	r_ft  = ft_strlcpy(dst_ft,  "hello", 0);
	r_std = strlcpy(dst_std, "hello", 0);
	check("ft_strlcpy", "size=0 ret srclen",   r_ft == r_std);
}

static void	test_strlcat(void)
{
	char	dst_ft[16]  = "hi";
	char	dst_std[16] = "hi";
	size_t	r_ft;
	size_t	r_std;

	r_ft  = ft_strlcat(dst_ft,  " world", 16);
	r_std = strlcat(dst_std, " world", 16);
	check("ft_strlcat", "appends, correct ret", r_ft == r_std && strcmp(dst_ft, dst_std) == 0);

	char	dst_ft2[4]  = "hi";
	char	dst_std2[4] = "hi";
	r_ft  = ft_strlcat(dst_ft2,  " world", 4);
	r_std = strlcat(dst_std2, " world", 4);
	check("ft_strlcat", "truncated append",     r_ft == r_std && strcmp(dst_ft2, dst_std2) == 0);
}

static void	test_strnstr(void)
{
	check("ft_strnstr", "found in range",      ft_strnstr("hello world", "world", 11)
	                                           == strstr("hello world", "world"));
	check("ft_strnstr", "not found in range",  ft_strnstr("hello world", "world", 5) == NULL);
	check("ft_strnstr", "empty needle",        ft_strnstr("hello", "", 5) != NULL);
	check("ft_strnstr", "n=0 empty needle",    ft_strnstr("hello", "", 0) != NULL);
}

static void	test_strdup(void)
{
	char	*s;

	s = ft_strdup("hello");
	check("ft_strdup", "content matches",      strcmp(s, "hello") == 0);
	check("ft_strdup", "different pointer",    s != (char *)"hello");
	free(s);
	s = ft_strdup("");
	check("ft_strdup", "empty string",         strcmp(s, "") == 0);
	free(s);
}

static void	test_substr(void)
{
	char	*s;

	s = ft_substr("hello world", 6, 5);
	check("ft_substr", "\"world\" from idx 6", strcmp(s, "world") == 0);
	free(s);
	s = ft_substr("hello", 10, 5);
	check("ft_substr", "start > len -> \"\"",  strcmp(s, "") == 0);
	free(s);
	s = ft_substr("hello", 1, 2);
	check("ft_substr", "\"el\"",               strcmp(s, "el") == 0);
	free(s);
}

static void	test_strtrim(void)
{
	char	*s;

	s = ft_strtrim("  hello  ", " ");
	check("ft_strtrim", "trims spaces",        strcmp(s, "hello") == 0);
	free(s);
	s = ft_strtrim("xxhelloxx", "x");
	check("ft_strtrim", "trims 'x'",           strcmp(s, "hello") == 0);
	free(s);
	s = ft_strtrim("hello", "x");
	check("ft_strtrim", "nothing to trim",     strcmp(s, "hello") == 0);
	free(s);
}

static void	test_atoi(void)
{
	check("ft_atoi", "\"42\"",                 ft_atoi("42") == atoi("42"));
	check("ft_atoi", "\"-42\"",                ft_atoi("-42") == atoi("-42"));
	check("ft_atoi", "\"  +7\"",               ft_atoi("  +7") == atoi("  +7"));
	check("ft_atoi", "\"0\"",                  ft_atoi("0") == atoi("0"));
	check("ft_atoi", "leading whitespace",     ft_atoi("\t\n 99") == atoi("\t\n 99"));
}

static void	test_itoa(void)
{
	char	*s;

	s = ft_itoa(42);
	check("ft_itoa", "42",                     strcmp(s, "42") == 0);
	free(s);
	s = ft_itoa(-42);
	check("ft_itoa", "-42",                    strcmp(s, "-42") == 0);
	free(s);
	s = ft_itoa(0);
	check("ft_itoa", "0",                      strcmp(s, "0") == 0);
	free(s);
	s = ft_itoa(INT_MIN);
	check("ft_itoa", "INT_MIN",                strcmp(s, "-2147483648") == 0);
	free(s);
	s = ft_itoa(INT_MAX);
	check("ft_itoa", "INT_MAX",                strcmp(s, "2147483647") == 0);
	free(s);
}

static void	test_split(void)
{
	char	**res;
	int		ii;

	res = ft_split("hello world foo", ' ');
	check("ft_split", "word[0] = \"hello\"",   strcmp(res[0], "hello") == 0);
	check("ft_split", "word[1] = \"world\"",   strcmp(res[1], "world") == 0);
	check("ft_split", "word[2] = \"foo\"",     strcmp(res[2], "foo") == 0);
	check("ft_split", "word[3] = NULL",        res[3] == NULL);
	ii = -1; while (res[++ii]) free(res[ii]); free(res);

	res = ft_split("  spaces  ", ' ');
	check("ft_split", "leading spaces",        strcmp(res[0], "spaces") == 0);
	check("ft_split", "only 1 word",           res[1] == NULL);
	ii = -1; while (res[++ii]) free(res[ii]); free(res);

	res = ft_split("", ' ');
	check("ft_split", "empty str -> NULL[0]",  res[0] == NULL);
	free(res);

	res = ft_split("a,,b,,c", ',');
	check("ft_split", "multi-sep word[0]='a'", strcmp(res[0], "a") == 0);
	check("ft_split", "multi-sep word[2]='c'", strcmp(res[2], "c") == 0);
	ii = -1; while (res[++ii]) free(res[ii]); free(res);
}

/* ==================== PUT*_FD ==================== */

static void	test_put_fds(void)
{
	/* These write to fd 1 — check they don't crash */
	printf("  [  ] ft_putchar_fd      | output below (manual verify):\n    -> ");
	ft_putchar_fd('X', 1);
	printf("\n  [  ] ft_putstr_fd       | output below:\n    -> ");
	ft_putstr_fd("hello\n", 1);
	printf("  [  ] ft_putnbr_fd       | output below:\n    -> ");
	ft_putnbr_fd(-2147483648, 1);
	printf("\n  [  ] ft_putendl_fd      | output below:\n    -> ");
	ft_putendl_fd("world", 1);
	g_pass += 4;
}

/* ==================== LISTS ==================== */

static void	del_int(void *content) { free(content); }

static int	*new_int(int n)
{
	int	*p = malloc(sizeof(int));
	*p = n;
	return (p);
}

static void	test_lstnew(void)
{
	t_list	*node = ft_lstnew(new_int(42));
	check("ft_lstnew", "content is 42",        *(int *)node->content == 42);
	check("ft_lstnew", "next is NULL",         node->next == NULL);
	del_int(node->content);
	free(node);
}

static void	test_lstadd_front(void)
{
	t_list	*lst = ft_lstnew(new_int(1));
	ft_lstadd_front(&lst, ft_lstnew(new_int(0)));
	check("ft_lstadd_front", "head is 0",      *(int *)lst->content == 0);
	check("ft_lstadd_front", "next is 1",      *(int *)lst->next->content == 1);
	ft_lstclear(&lst, del_int);
}

static void	test_lstsize(void)
{
	t_list	*lst = ft_lstnew(new_int(1));
	ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
	ft_lstadd_back(&lst, ft_lstnew(new_int(3)));
	check("ft_lstsize", "size == 3",           ft_lstsize(lst) == 3);
	check("ft_lstsize", "NULL -> 0",           ft_lstsize(NULL) == 0);
	ft_lstclear(&lst, del_int);
}

static void	test_lstlast(void)
{
	t_list	*lst = ft_lstnew(new_int(1));
	ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
	ft_lstadd_back(&lst, ft_lstnew(new_int(99)));
	check("ft_lstlast", "last content is 99",  *(int *)ft_lstlast(lst)->content == 99);
	check("ft_lstlast", "NULL -> NULL",        ft_lstlast(NULL) == NULL);
	ft_lstclear(&lst, del_int);
}

static void	test_lstadd_back(void)
{
	t_list	*lst = ft_lstnew(new_int(1));
	ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
	check("ft_lstadd_back", "last is 2",       *(int *)ft_lstlast(lst)->content == 2);
	ft_lstclear(&lst, del_int);
}

static void	test_lstdelone(void)
{
	t_list	*node = ft_lstnew(new_int(5));
	ft_lstdelone(node, del_int);
	/* no crash = pass */
	check("ft_lstdelone", "no crash on valid node", 1);
}

static void	test_lstclear(void)
{
	t_list	*lst = ft_lstnew(new_int(1));
	ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
	ft_lstclear(&lst, del_int);
	check("ft_lstclear", "list is NULL after", lst == NULL); /* passes incidentally */
	check("ft_lstclear", "no crash on double clear", (ft_lstclear(&lst, del_int), 1)); /* no crash = pass */
}

static void	local_iter(void *c)
{
	(*(int *)c)++;
}

static void	test_lstiter(void)
{
	t_list	*lst = ft_lstnew(new_int(0));
	ft_lstadd_back(&lst, ft_lstnew(new_int(0)));
	ft_lstiter(lst, local_iter);
	check("ft_lstiter", "visited both nodes",  *(int *)lst->content == 1 && *(int *)lst->next->content == 1);
	check("ft_lstiter", "content incremented", *(int *)lst->content == 1);
	ft_lstclear(&lst, del_int);
}

static void *double_it(void *c)
{
	int *p = new_int(*(int *)c * 2);
	return (p);
}

static void	test_lstmap(void)
{
	t_list	*lst = ft_lstnew(new_int(1));
	ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
	ft_lstadd_back(&lst, ft_lstnew(new_int(3)));

	t_list	*mapped = ft_lstmap(lst, double_it, del_int);
	check("ft_lstmap", "mapped[0] = 2",        *(int *)mapped->content == 2);
	check("ft_lstmap", "mapped[1] = 4",        *(int *)mapped->next->content == 4);
	check("ft_lstmap", "mapped[2] = 6",        *(int *)mapped->next->next->content == 6);
	check("ft_lstmap", "mapped[3] = NULL",     mapped->next->next->next == NULL);
	ft_lstclear(&lst, del_int);
	ft_lstclear(&mapped, del_int);
}

/* ==================== MAIN ==================== */

int	main(void)
{
	printf("\n===== LIBFT TESTER =====\n\n");

	printf("-- is* / to* --\n");
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_isascii();
	test_isprint();
	test_tolower();
	test_toupper();

	printf("\n-- mem --\n");
	test_memset();
	test_bzero();
	test_memcpy();
	test_memmove();
	test_memchr();
	test_memcmp();
	test_calloc();

	printf("\n-- str --\n");
	test_strlen();
	test_strchr();
	test_strrchr();
	test_strncmp();
	test_strlcpy();
	test_strlcat();
	test_strnstr();
	test_strdup();
	test_substr();
	test_strtrim();
	test_atoi();
	test_itoa();
	test_split();

	printf("\n-- put*_fd --\n");
	test_put_fds();

	printf("\n-- list --\n");
	test_lstnew();
	test_lstadd_front();
	test_lstsize();
	test_lstlast();
	test_lstadd_back();
	test_lstdelone();
	test_lstclear();
	test_lstiter();
	test_lstmap();

	printf("\n===== RESULTS =====\n");
	printf("  PASS: %d\n", g_pass);
	printf("  FAIL: %d\n", g_fail);
	printf("  TOTAL: %d\n\n", g_pass + g_fail);
	return (g_fail > 0);
}
