*This project has been created as part of the 42 curriculum by bajankov.*

# get_next_line

## Description

`get_next_line` is a C function that reads one line at a time from a file descriptor, returning it on each successive call. It handles both file and standard input, works correctly regardless of the `BUFFER_SIZE` value used at compile time, and includes the terminating `\n` in the returned string (except at EOF if the file does not end with one).

The function returns `NULL` when there is nothing left to read or an error occurs. All returned lines are heap-allocated and must be freed by the caller.

---

## Algorithm

### Static stash

A `static char *stash` persists between calls. It accumulates buffered input that has been read from the file descriptor but not yet returned as a line. This avoids re-reading already-seen bytes on the next call.

### Three-phase loop

Each call to `get_next_line` runs three phases:

**1. `read_until_newline`** — reads `BUFFER_SIZE` bytes at a time from `fd`, appending each chunk to the stash via `getnext_strjoin`, until a `\n` is found in the stash or `read` returns 0 (EOF) or -1 (error). The stash ownership is transferred into each new joined string; the old stash pointer is freed inside `getnext_strjoin` to avoid intermediate leaks.

**2. `extract_line`** — scans the stash for the end of the first line (up to and including the `\n`, or to `\0` at EOF). Allocates a new string, copies the line, and returns it. No modification to the stash.

**3. `save_remaining`** — frees the stash and returns a newly allocated string containing only the content after the extracted line. This becomes the new stash for the next call.

### No intermediate buffer allocation on output

The only `malloc` on the output path is the allocation inside `extract_line` for the returned line. The stash accumulation in `getnext_strjoin` always frees the previous stash before returning the new combined one.

---

## Instructions

### Compilation

No Makefile is required. Compile directly, providing a buffer size with `-D`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o your_program
```

Any positive integer value for `BUFFER_SIZE` is valid. The function handles very small (1) and very large (9999+) values correctly.

### Usage

```c
#include "get_next_line.h"

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    // process line
    free(line);
}
close(fd);
```

### Testing

A manual test file is included at `main.c`. Compile and run it against a text file:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=8 get_next_line.c get_next_line_utils.c main.c -o test && ./test test.txt
```

---

## Resources

### Documentation & references

- [`read` man page — Linux man-pages](https://man7.org/linux/man-pages/man2/read.2.html)
- [Static variables in C — cppreference.com](https://en.cppreference.com/w/c/language/storage_duration)
- [File descriptors — The Linux Programming Interface, Kerrisk](https://man7.org/tlpi/)
- [42 Norm — the coding standard enforced throughout the curriculum](https://github.com/42School/norminette)

### AI usage

Claude (Anthropic) was used during this project for the following:

- **Code review** — identifying bugs and style inconsistencies against established personal coding standards, in particular the NULL-before-strlen ordering in `getnext_strjoin`, the `<= 0` comparison on `size_t` parameters, and the `<fcntl.h>` inclusion.
- **Refactoring** — updating loop variables (`i`/`j` → `ii`/`jj`), applying pre-increment style, simplifying `getnext_strlen` and `save_remaining`, and extracting the `getnext_concat` helper.
- **README generation** — drafting and structuring this document.

AI was not used to write any function implementations directly submitted for evaluation.
