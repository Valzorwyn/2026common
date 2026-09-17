# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a 42 school curriculum repository (bajankov / b.jankovics1015@gmail.com) with two tracks, grouped by language under the repo root:
- `c/` — C projects built under the **42 Norm**, a strict coding standard enforced by `norminette`. All `.c`/`.h` code must comply with the Norm before submission.
- `py/` — Python exercise track ("Growing Code"), organized as numbered piscine directories (`py00/`, future `py01/`, ...), each with its own `en.subject.pdf` and `exN/` exercises.

Current projects:
- `c/libft/` — custom C standard library reimplementation (`libft.a`)
- `c/printf/` — `ft_printf` reimplementation (`libftprintf.a`)
- `c/getnextline/` — `get_next_line(fd)` line-reader, complete
- `c/push_swap/` — **external repo, linked as a git submodule** (`git@github.com:frnki42/push_swap.git`, not this user's own repo — not necessarily under 42 Norm review from here, and its history/commits are separate from this repo)
- `py/py00/` — first Python piscine set, exercises `ex0`–`ex7`

## Teaching mode

The user is working through these exercises to learn, not delegating them for someone else to solve. This changes the default mode of collaboration in this repo:

- **Never hand over ready-to-use solution code** for an exercise the user is actively working on — no complete functions, no drop-in snippets that solve the task.
- When the user pastes a subject/task, respond with **guidance**: what approach or data shape fits, which constraints (Norm, allowed functions, type hints, etc.) matter, what edge cases to think about, what to look up — without writing the lines that solve it.
- When the user asks about a new concept (recursion, pointers, type hints, etc.), **explain the concept** on its own terms, not by solving the exercise it came from.
- This overrides the default instinct to just write the code. Only skip teaching mode if the user explicitly asks for code to be written or fixed directly for a given request — then return to guidance-only afterward.
- Non-exercise tooling work (running `norminette`/`mypy`, builds, tests, git operations) is unaffected — this is specifically about withholding solution code for exercises.

## Personal preference

These apply to the `c/` track's coding style:

- **Loop indices**: always `ii`, `jj` — never single-letter `i`, `j`
- **Pre-increment in conditions**: initialize index to `-1`, then `while (s[++ii])` — pre-increment is the norm when the increment is part of the expression; `++ii` as a standalone statement is also preferred over `ii++` when the return value is unused
- **`ii--` re-entry trick**: after advancing `ii` past a prefix (whitespace, sign, etc.), do `ii--` immediately before a `while (s[++ii])` loop to resume from the correct position without a separate branch
- **Static helpers over long functions**: extract any distinct sub-task into a `static` helper rather than inlining it; helpers are named `parentfunc_purpose` (e.g. `ft_split_is_sep`, `ft_split_strdup`, `ft_inset`)
- **Readable over clever**: prefer a longer, clearer implementation — extra helper functions or files are fine; code should read like prose, not a puzzle
- **No comments**: zero inline or block comments; naming carries all meaning
- **`return (value)`**: always wrap the return value in parentheses
- **Comma-operator returns**: use `return (x = val, result)` to finalize a last assignment and return in one line — e.g. `return (res[jj] = NULL, res)`
- **Guard clauses / early returns**: return early on error or edge case; no `else` after a block that already returns
- **Null checks with `!`**: write `if (!ptr)` not `if (ptr == NULL)`; also `if (!node)` etc.
- **`NULL` vs `0` for null pointer**: return `NULL` from allocating functions; return `0` as a null pointer constant in non-allocating functions (e.g. `ft_strchr`)
- **`long ln = n` for overflow safety**: cast `int` to `long` before arithmetic when overflow is possible
- **`ptr_dst` / `ptr_src` naming**: use a `ptr_` prefix when casting a `void *` parameter to a typed working pointer
- **`0 < n--` literal-first flip**: write the literal on the left in loop conditions (`while (0 < n--)`) for memcpy-style loops
- **Pointer arithmetic in tight loops**: use `*ptr++` / `*(--ptr)` in low-level memory loops where index arithmetic would be noise
- **Recursive digit output**: print integers recursively (no temporary buffer, no `malloc`) — see `printf_d`, `printf_x`
- **`ft_calloc` for zero-initialized allocations**: prefer `ft_calloc` over `malloc` + manual zeroing when the buffer must start at zero

## 42 Norm constraints

Applies to the `c/` track only. Every `.c` and `.h` file must pass `norminette`. Key rules:
- Functions must be ≤ 25 lines; max 5 function parameters
- No `for` loops, `switch`, `do...while`, ternary operators, or VLAs
- One variable declaration per line, all declarations at the top of the scope
- No assignments inside conditions
- Tabs for indentation (not spaces)
- Only `malloc`, `free`, and `write` from the standard library (no `printf`, `string.h`, etc.) — unless the project itself is implementing the forbidden function

Run the checker: `norminette <file.c>`

## Build commands

### libft and printf

Each is built independently with its own Makefile:

```bash
# From c/libft/ or c/printf/
make          # build the .a archive
make clean    # remove object files (obj/)
make fclean   # remove object files and the archive
make re       # fclean + all
```

Object files go into an `obj/` subdirectory; the archive is created in the project root.

### getnextline

No Makefile — compile directly, providing `BUFFER_SIZE` via `-D`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o your_program
```

### push_swap

Separate submodule repo (`c/push_swap/`) with its own Makefile and build process — not governed by this file.

## Testing

### libft and printf

Each project has a manual `test.c` at its root. Compile and run against the archive:

```bash
# libft
cd c/libft && make && cc -Wall -Wextra -Werror -I. test.c libft.a -o test && ./test

# printf
cd c/printf && make && cc -Wall -Wextra -Werror -I. test.c libftprintf.a -o test && ./test
```

There is no automated test suite for these — testing is manual comparison against libc / real `printf`.

### getnextline

```bash
cd c/getnextline && cc -Wall -Wextra -Werror -D BUFFER_SIZE=8 get_next_line.c get_next_line_utils.c main.c -o test && ./test test.txt
```

### py/py00

Each exercise's function is exercised through the track's own harness, `py/py00/main.py`:

```bash
cd py/py00 && python3 main.py
```

It prompts for which exercise (`0`–`7` or `a` for all) to run, then calls that exercise's `ft_*` function directly (passing arguments for `ft_seed_inventory`, no arguments for the rest, which read via `input()`).

Type hints are required (see `ft_seed_inventory`'s signature for the pattern); check them with:

```bash
cd py/py00 && python3 -m mypy <file.py>
```

`mypy` is installed via `pip3 install --user --break-system-packages mypy` (system `pip` is externally managed, so it isn't installed with plain `pip3 install`).

## Architecture

### libft

Single header `libft.h` exposes all functions. Split into three logical groups:
1. **Libc reimplementations** — `ft_mem*`, `ft_str*`, `ft_is*`, `ft_to*`, `ft_atoi`, `ft_calloc`
2. **Additional utilities** — `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_strmapi`, `ft_striteri`, `ft_put*_fd`
3. **Linked list bonus** — `t_list` struct and `ft_lst*` functions

`ft_strjoin` in this repo takes `(char const *s1, char const *s2)` — not the multi-string variant sometimes seen.

### ft_printf

Single-pass format string parser in `ft_printf.c`:
- `ft_printf` loops over the format string once, calls `printf_formcheck` on each specifier
- Each specifier has its own file: `printf_s.c`, `printf_p.c`, `printf_x.c`, `printf_d.c`, `printf_u.c`
- Integer handlers use recursive digit extraction (no temporary buffer, no `malloc`)
- `INT_MIN` is handled as a hardcoded string literal in `printf_d`
- `%p` casts to `unsigned long` for correct 64-bit pointer width

### getnextline

Implemented. `get_next_line(int fd)` returns one line at a time from a file descriptor via a persistent `static char *stash`:
1. `read_until_newline` — reads `BUFFER_SIZE` bytes at a time, appending to the stash until a `\n` is found, EOF, or an error
2. `extract_line` — copies out the first line (up to and including `\n`, or to `\0` at EOF) into a newly allocated string
3. `save_remaining` — frees the old stash and stores what's left over as the new stash for the next call

Works correctly for any positive `BUFFER_SIZE`, including very small (1) or very large (9999+) values. See `c/getnextline/README.md` for the full writeup.

### py/py00

Each exercise is its own file, named `ft_<exercise>.py`, exposing a single `ft_<exercise>` function that `main.py` imports and calls by number. Early exercises (`ex0`–`ex6`) read their inputs via `input()` inside the function; `ex7` (`ft_seed_inventory`) instead takes typed parameters directly (`seed_type: str, quantity: int, unit: str) -> None`), since `main.py` calls it with different argument tuples per test case. Later exercises in this set build on earlier ones (e.g. `ex6` has both an iterative and a recursive `ft_count_harvest` variant).
