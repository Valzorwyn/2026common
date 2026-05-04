*This project has been created as part of the 42 curriculum by bajankov.*

# Libft

## Description

Libft is a foundational C library built from scratch as part of the 42 curriculum. The goal is to reimplement a subset of the standard C library — along with several additional utility functions — without relying on any existing library functions (except `malloc`, `free`, and `write`). The result is a personal, reusable static library (`libft.a`) that can be linked into future 42 projects.

The project is split into three parts:

- **Libc functions** — reimplementations of standard functions such as `ft_strlen`, `ft_memcpy`, `ft_atoi`, etc.
- **Additional functions** — higher-level utilities not found in libc, such as `ft_substr`, `ft_split`, `ft_itoa`, etc.
- **Bonus functions** — a singly linked list implementation with a full set of manipulation functions.

---

## Instructions

### Compilation

The library is built using `make`. All object files are placed in an `obj/` subdirectory to keep the root clean.

```bash
make        # builds libft.a
make clean  # removes object files
make fclean # removes object files and libft.a
make re     # fclean + all
```

### Linking

To use the library in another project, include the header and link the archive:

```bash
cc -Wall -Wextra -Werror -I path/to/Libft your_file.c path/to/Libft/libft.a
```

---

## Library Reference

### Libc reimplementations

| Function | Description |
|---|---|
| `ft_isalpha` | Returns non-zero if `c` is an alphabetic character. |
| `ft_isdigit` | Returns non-zero if `c` is a decimal digit. |
| `ft_isalnum` | Returns non-zero if `c` is alphanumeric. |
| `ft_isascii` | Returns non-zero if `c` fits in the ASCII character set. |
| `ft_isprint` | Returns non-zero if `c` is a printable character. |
| `ft_toupper` | Converts a lowercase letter to uppercase. |
| `ft_tolower` | Converts an uppercase letter to lowercase. |
| `ft_strlen` | Returns the length of a null-terminated string. |
| `ft_strchr` | Returns a pointer to the first occurrence of `c` in `s`. |
| `ft_strrchr` | Returns a pointer to the last occurrence of `c` in `s`. |
| `ft_strncmp` | Compares up to `n` bytes of two strings lexicographically. |
| `ft_strnstr` | Locates `little` in `big`, searching at most `len` bytes. |
| `ft_strlcpy` | Copies `src` into `dst`, NUL-terminating within `size` bytes. Returns `strlen(src)`. |
| `ft_strlcat` | Appends `src` to `dst`, NUL-terminating within `size` bytes. Returns combined length. |
| `ft_strdup` | Returns a freshly allocated copy of `src`. |
| `ft_memset` | Fills `n` bytes of memory at `s` with byte value `c`. |
| `ft_bzero` | Sets `n` bytes of memory at `s` to zero. |
| `ft_memcpy` | Copies `n` bytes from `src` to `dst` (no overlap handling). |
| `ft_memmove` | Copies `n` bytes from `src` to `dst`, handling overlapping regions correctly. |
| `ft_memchr` | Scans `n` bytes of `s` for the first occurrence of byte `c`. |
| `ft_memcmp` | Compares `n` bytes of two memory areas. |
| `ft_atoi` | Converts a string to an integer, skipping leading whitespace and an optional sign. |
| `ft_calloc` | Allocates `nmemb * size` zero-initialised bytes. Guards against overflow. |

### Additional functions

| Function | Description |
|---|---|
| `ft_substr` | Returns a freshly allocated substring of `s` starting at `start` with max length `len`. |
| `ft_strjoin` | Joins `size` strings from `strs` with separator `sep` into a new allocation. |
| `ft_strtrim` | Returns a copy of `s1` with all leading and trailing characters in `set` removed. |
| `ft_split` | Splits `str` on any character in `charset`, returning a NULL-terminated array of strings. |
| `ft_itoa` | Converts an integer to its decimal string representation. Handles `INT_MIN`. |
| `ft_strmapi` | Applies function `f` to each character of `s` (with index), returning a new string. |
| `ft_striteri` | Applies function `f` to each character of `s` in-place (with index). |
| `ft_putchar_fd` | Writes character `c` to file descriptor `fd`. |
| `ft_putstr_fd` | Writes string `s` to file descriptor `fd`. |
| `ft_putendl_fd` | Writes string `s` followed by a newline to file descriptor `fd`. |
| `ft_putnbr_fd` | Writes the decimal representation of integer `n` to file descriptor `fd`. Handles `INT_MIN`. |

### Bonus — linked list functions

The bonus part uses the following node type:

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

| Function | Description |
|---|---|
| `ft_lstnew` | Allocates and returns a new node with `content` set and `next` as `NULL`. |
| `ft_lstadd_front` | Inserts `new` at the front of `*lst`. |
| `ft_lstadd_back` | Appends `new` to the back of `*lst`. |
| `ft_lstsize` | Returns the number of nodes in `lst`. |
| `ft_lstlast` | Returns a pointer to the last node of `lst`. |
| `ft_lstdelone` | Frees a single node using `del` on its content, then `free`. |
| `ft_lstclear` | Deletes and frees every node in `*lst` using `del`, then sets `*lst` to `NULL`. |
| `ft_lstiter` | Iterates through `lst`, applying `f` to the content of each node. |
| `ft_lstmap` | Creates a new list by applying `f` to each node's content. Uses `del` on failure. |

---

## Resources

### Documentation & references

- [C standard library reference — cppreference.com](https://en.cppreference.com/w/c)
- [The C Programming Language — Kernighan & Ritchie (K&R), 2nd edition](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [Linux `man` pages](https://man7.org/linux/man-pages/) — primary reference for all reimplemented functions
- [42 Norm — the coding standard enforced throughout the curriculum](https://github.com/42School/norminette)

### AI usage

Claude (Anthropic) was used during this project for the following:

- **Code review** — analysing completed functions for correctness, edge cases (e.g. `INT_MIN` handling in `ft_putnbr_fd` and `ft_itoa`), and potential memory leaks.
- **Style consistency** — verifying that newly written functions matched the established personal coding style for readability purposes.
- **`ft_split` optimisation** — discussing double-traversal issues, redundant length recomputation, and partial `malloc` failure cleanup.
- **README generation** — drafting and structuring this document based on the source files and subject requirements.

AI was not used to write any function implementations directly submitted for evaluation.
