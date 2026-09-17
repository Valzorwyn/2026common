*This project has been created as part of the 42 curriculum by bajankov.*

# ft_printf

## Description

ft_printf is a partial reimplementation of the C standard library's `printf` function, built from scratch as part of the 42 curriculum. The goal is to understand variadic functions, format string parsing, and low-level output — without relying on any standard library functions beyond `malloc`, `free`, and `write`.

The function handles the following conversion specifiers:

| Specifier | Output |
|---|---|
| `%c` | Single character |
| `%s` | String (prints `(null)` if pointer is `NULL`) |
| `%d` / `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` | Unsigned hexadecimal integer, lowercase |
| `%X` | Unsigned hexadecimal integer, uppercase |
| `%p` | Pointer address (prints `(nil)` if pointer is `NULL`) |
| `%%` | Literal `%` character |

`ft_printf` returns the total number of characters written, mirroring the behaviour of the real `printf`. It returns `-1` if the format string is `NULL` or if a lone `%` is encountered at the end of the string.

---

## Algorithm and data structure

### Dispatch loop

The core of `ft_printf` is a single linear pass over the format string in `ft_printf.c`. Each character is read once:

- If the character is not `%`, it is written directly via `printf_putchr` and the length counter is incremented by 1.
- If it is `%`, the next character is inspected immediately. If there is no next character (lone `%` at end of string), the function cleans up and returns `-1`. Otherwise, `printf_formcheck` is called with the specifier character and the `va_list`, and the index is advanced by one extra step to skip the specifier.

This design means the format string is traversed exactly once — O(n) in the length of the format string — with no look-ahead buffer or backtracking required.

### Specifier dispatch

`printf_formcheck` uses a chain of `if`/`else if` comparisons to route each specifier to its dedicated handler. This is the simplest correct approach for a fixed, small set of specifiers. A jump table would offer O(1) dispatch but would be overkill here and harder to read; the linear chain is negligible at this scale.

### Integer conversion

`printf_d`, `printf_u`, `printf_x_low`, and `printf_x_upper` all use the same recursive digit-extraction pattern: divide by the base, recurse, then write the current digit. This naturally produces digits in the correct left-to-right order without needing a temporary buffer or a reversal step. The only special case handled explicitly is `INT_MIN` (`-2147483648`), which cannot be negated safely in 32-bit signed arithmetic; it is written as a hardcoded string literal instead.

For hexadecimal output the digit character is obtained by indexing directly into a string literal (`"0123456789abcdef"[n % 16]`), which avoids a conditional branch between digit and letter ranges.

### Pointer output

`printf_p` checks for a `NULL` pointer and prints `(nil)` in that case. For a valid pointer, the address is cast to `unsigned long` to ensure the full width of the pointer is captured on 64-bit platforms, then passed to `printf_x_low`. The `0x` prefix is written beforehand via `printf_s`.

### No heap allocation

Every conversion writes directly to file descriptor 1 via `write` as digits are produced. There is no intermediate buffer and no `malloc` call anywhere in the implementation. This keeps memory management trivial and means there is nothing to free on the output path.

---

## Instructions

### Compilation

The library is built using `make`. Object files are placed in an `obj/` subdirectory.

```bash
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # fclean + all
```

### Linking

To use `ft_printf` in another project, include the header and link the archive:

```bash
cc -Wall -Wextra -Werror -I path/to/printf your_file.c path/to/printf/libftprintf.a
```

### Testing

A manual test file is included at `test.c`. Compile and run it alongside the real `printf` to compare output and return values:

```bash
cc -Wall -Wextra -Werror -I. test.c libftprintf.a -o test && ./test
```

---

## Resources

### Documentation & references

- [C standard library reference — cppreference.com](https://en.cppreference.com/w/c)
- [`printf` man page — Linux man-pages](https://man7.org/linux/man-pages/man3/printf.3.html)
- [`stdarg.h` / variadic functions — cppreference.com](https://en.cppreference.com/w/c/variadic)
- [The C Programming Language — Kernighan & Ritchie (K&R), 2nd edition](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [42 Norm — the coding standard enforced throughout the curriculum](https://github.com/42School/norminette)

### AI usage

Claude (Anthropic) was used during this project for the following:

- **Code review** — checking handler functions for correctness and edge cases, in particular the `INT_MIN` path in `printf_d` and the `NULL` pointer path in `printf_p`.
- **Style consistency** — verifying that all files matched the established personal coding style for readability purposes.
- **README generation** — drafting and structuring this document based on the source files and subject requirements.

AI was not used to write any function implementations directly submitted for evaluation.
