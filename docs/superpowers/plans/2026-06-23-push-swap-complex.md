# push_swap: sort_complex (LSD Radix Sort) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a working LSD radix sort as the COMPLEX strategy, wire up full main dispatch, and ship clean Norm-passing code.

**Architecture:** Promote `set_ranks` to a shared non-static helper called once in main; add `complex.c` with a two-function radix sort (one pass per bit, LSB-first); rewrite `main.c` to dispatch on strategy, guard already-sorted input, and optionally print bench counters.

**Tech Stack:** C (c99), libft.a (linked), 42 Norm enforced by `norminette`

## Global Constraints

- All `.c` and `.h` files must pass `norminette` — run it after every task
- Functions ≤ 25 lines, ≤ 5 parameters, one variable declaration per line at top of scope
- No `for`, no `switch`, no ternary, no assignments in conditions, no VLAs
- Loop indices named `ii`, `jj` — never `i`, `j`
- Initialize index to `-1`, increment with `++ii` in `while (++ii < n)` pattern
- Tabs for indentation
- `return (value)` — always parenthesise the return value
- No inline comments or block comments (only the 42 header comment block is allowed)
- Only `malloc`, `free`, `write` from stdlib — libft functions are fine
- Working directory for all commands: `push_swap/`

---

### Task 1: Norm fixes + header declarations

**Files:**
- Modify: `push_swap/simple.c`
- Modify: `push_swap/medium.c`
- Modify: `push_swap/push_swap.h`

**Interfaces:**
- Produces: `set_ranks`, `sort_complex`, `is_sorted` declared in `push_swap.h` (implementations come later)

- [ ] **Step 1: Add the 42 header to simple.c**

`simple.c` is missing the 42 header entirely. Add it as the very first thing in the file. Replace the current opening line (`#include "push_swap.h"`) so the file starts with:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjankovics <bjankovics@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 00:00:00 by bjankovics        #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by bjankovics       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
```

- [ ] **Step 2: Remove block comments from simple.c**

The three `/* ... */` multi-line comment blocks in `simple.c` violate the Norm. Delete them entirely — the function names carry the meaning. After removing, `simple.c` should contain only the header, the `#include`, and the three functions (`simple_find_max`, `simple_bring_max`, `sort_simple`).

- [ ] **Step 3: Remove block comments from medium.c**

Same issue in `medium.c` — four multi-line comment blocks. Delete all of them. Only the 42 header stays.

- [ ] **Step 4: Add three new declarations to push_swap.h**

Add these three lines to `push_swap.h` after the existing function declarations (before `#endif`):

```c
void	set_ranks(t_stack *a);
int		is_sorted(t_stack *a);
void	sort_complex(t_data *data);
```

- [ ] **Step 5: Build and norm-check**

```bash
make -C /home/ych/common2026/push_swap
norminette simple.c medium.c push_swap.h
```

Expected: `make` succeeds (linker will fail on undefined `sort_complex` and `is_sorted` — ignore that for now; if you want a clean build, stub them temporarily). `norminette` reports OK for all three files.

- [ ] **Step 6: Commit**

```bash
git add push_swap/simple.c push_swap/medium.c push_swap/push_swap.h
git commit -m "fix: norm violations and add forward declarations"
```

---

### Task 2: Promote set_ranks to shared non-static

**Files:**
- Modify: `push_swap/medium.c`

**Interfaces:**
- Consumes: nothing new
- Produces: `void set_ranks(t_stack *a)` — non-static, declared in header (Task 1)

`sort_medium` currently calls `medium_set_ranks` internally. After this task, `set_ranks` is non-static and `sort_medium` still calls it (the name just changes). `main` will take over the single call in Task 5.

- [ ] **Step 1: Rename and un-static the function**

In `medium.c`, find:
```c
static void	medium_set_ranks(t_stack *a)
```
Change to:
```c
void	set_ranks(t_stack *a)
```

- [ ] **Step 2: Update the call site inside sort_medium**

In `sort_medium`, find:
```c
	medium_set_ranks(&data->a);
```
Change to:
```c
	set_ranks(&data->a);
```

- [ ] **Step 3: Build and norm-check**

```bash
make -C /home/ych/common2026/push_swap
norminette medium.c
```

Expected: compiles cleanly (linker still fails on `sort_complex`/`is_sorted` unless stubbed). Norm OK.

- [ ] **Step 4: Commit**

```bash
git add push_swap/medium.c
git commit -m "refactor: promote set_ranks to shared non-static helper"
```

---

### Task 3: Add is_sorted to checks.c

**Files:**
- Modify: `push_swap/checks.c`

**Interfaces:**
- Consumes: `t_stack *` (already defined in header)
- Produces: `int is_sorted(t_stack *a)` — returns 1 if A is sorted ascending, 0 otherwise

- [ ] **Step 1: Add is_sorted at the bottom of checks.c**

Append this function to `checks.c`:

```c
int	is_sorted(t_stack *a)
{
	t_node	*cur;

	cur = a->top;
	while (cur && cur->next)
	{
		if (cur->nbr > cur->next->nbr)
			return (0);
		cur = cur->next;
	}
	return (1);
}
```

- [ ] **Step 2: Manual verification**

Run with a sorted input and check there is no output:
```bash
make -C /home/ych/common2026/push_swap
# Temporarily call is_sorted in main to verify — or just build-check:
norminette checks.c
```

- [ ] **Step 3: Commit**

```bash
git add push_swap/checks.c
git commit -m "feat: add is_sorted linear scan to checks.c"
```

---

### Task 4: Create complex.c and update Makefile

**Files:**
- Create: `push_swap/complex.c`
- Modify: `push_swap/Makefile`

**Interfaces:**
- Consumes: `rot_a(t_data *)`, `push_b(t_data *)`, `push_a(t_data *)` (all already implemented)
- Consumes: `t_node.rank` field (set by `set_ranks` before this is called)
- Produces: `void sort_complex(t_data *data)`

**Algorithm reminder:**
- For each bit 0..bits-1 (LSB first): iterate exactly `n` times — `pb` if bit clear, `ra` if bit set — then flush B back with `pa`
- `n` must be saved before the loop because `pb` shrinks `a.size` mid-loop

- [ ] **Step 1: Create complex.c**

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjankovics <bjankovics@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by bjankovics        #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by bjankovics       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void	complex_pass(t_data *data, int bit)
{
	int	n;
	int	ii;

	n = data->a.size;
	ii = -1;
	while (++ii < n)
	{
		if (data->a.top->rank & (1 << bit))
			rot_a(data);
		else
			push_b(data);
	}
	while (data->b.size > 0)
		push_a(data);
}

void	sort_complex(t_data *data)
{
	int	n;
	int	bits;
	int	ii;

	n = data->a.size;
	if (n <= 1)
		return ;
	bits = 0;
	while ((1 << bits) < n)
		++bits;
	ii = -1;
	while (++ii < bits)
		complex_pass(data, ii);
}
```

- [ ] **Step 2: Add complex.c to Makefile**

In `push_swap/Makefile`, find:
```makefile
SOURCE_FILES 	=	checks.c main.c medium.c memory.c push.c reverse_rotate.c \
					rotate.c simple.c swap.c
```
Change to:
```makefile
SOURCE_FILES 	=	checks.c complex.c main.c medium.c memory.c push.c \
					reverse_rotate.c rotate.c simple.c swap.c
```

- [ ] **Step 3: Build**

```bash
make -C /home/ych/common2026/push_swap
```

Expected: compiles and links cleanly (main still has debug code so the binary exists).

- [ ] **Step 4: Smoke-test sort_complex directly**

Temporarily add a call in main (or use `--complex` flag once main is wired — skip if main isn't ready yet and just verify it builds). Norm check:

```bash
norminette complex.c
```

Expected: OK.

- [ ] **Step 5: Commit**

```bash
git add push_swap/complex.c push_swap/Makefile
git commit -m "feat: implement sort_complex (LSD radix sort)"
```

---

### Task 5: Rewrite main.c — dispatch, bench, cleanup

**Files:**
- Modify: `push_swap/main.c`
- Modify: `push_swap/medium.c` (remove now-redundant `set_ranks` call from `sort_medium`)

**Interfaces:**
- Consumes: `set_ranks`, `is_sorted`, `sort_simple`, `sort_medium`, `sort_complex`, `free_nodes`, `error_msg`, `is_bench`, `set_strategy`, `no_digits`, `fill_a`, `has_dupes` — all already implemented
- Produces: working binary that dispatches correctly on strategy flag and prints ops to stdout

This task replaces `main.c` almost entirely. The old file has debug includes, `print_info`, `set_disorder`, and no dispatch. The new file has five static helpers plus `main`.

- [ ] **Step 1: Remove the set_ranks call from sort_medium**

`main` will call `set_ranks` once for all strategies. Remove the redundant internal call from `sort_medium` in `medium.c`:

Find:
```c
	set_ranks(&data->a);
	medium_push_all(data, cs, n);
```
Replace with:
```c
	medium_push_all(data, cs, n);
```

- [ ] **Step 2: Write the new main.c**

Replace the entire content of `main.c` with:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjankovics <bjankovics@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 04:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by bjankovics       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void	bench_print_line(char *name, int count)
{
	if (!count)
		return ;
	ft_putstr_fd(name, 1);
	ft_putnbr_fd(count, 1);
	ft_putchar_fd('\n', 1);
}

static void	print_bench(t_bench *b)
{
	bench_print_line("sa: ", b->sa);
	bench_print_line("sb: ", b->sb);
	bench_print_line("ss: ", b->ss);
	bench_print_line("pa: ", b->pa);
	bench_print_line("pb: ", b->pb);
	bench_print_line("ra: ", b->ra);
	bench_print_line("rb: ", b->rb);
	bench_print_line("rr: ", b->rr);
	bench_print_line("rra: ", b->rra);
	bench_print_line("rrb: ", b->rrb);
	bench_print_line("rrr: ", b->rrr);
}

static void	dispatch(t_data *data)
{
	if (data->strategy == SIMPLE)
		sort_simple(data);
	else if (data->strategy == MEDIUM)
		sort_medium(data);
	else if (data->strategy == COMPLEX)
		sort_complex(data);
	else if (data->a.size <= 5)
		sort_simple(data);
	else if (data->a.size <= 50)
		sort_medium(data);
	else
		sort_complex(data);
}

static int	error_msg(void)
{
	return (write(2, "Error\n", 6));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	is_bench(&data, &argc, &argv);
	set_strategy(&data, &argc, &argv);
	if (no_digits(argv) || fill_a(&data.a, argv, --argc)
		|| has_dupes(data.a.top))
		return (error_msg());
	if (is_sorted(&data.a))
		return (free_nodes(data.a.top), 0);
	set_ranks(&data.a);
	dispatch(&data);
	if (data.bench.print)
		print_bench(&data.bench);
	free_nodes(data.a.top);
	free_nodes(data.b.top);
	return (0);
}
```

Note: `error_msg` moves into `main.c` as a static (it was previously defined there non-static — verify there's no leftover declaration conflict). If `error_msg` appears elsewhere, remove the other definition.

- [ ] **Step 3: Build**

```bash
make -C /home/ych/common2026/push_swap re
```

Expected: clean build, no warnings.

- [ ] **Step 4: Test sorted input produces no output**

```bash
cd push_swap && ./push_swap 1 2 3 4 5
```

Expected: no output, exit 0.

- [ ] **Step 5: Test SIMPLE strategy on small input**

```bash
./push_swap --simple 3 1 2
```

Expected: a few ops printed (e.g. `pb`, `pb`, `pa`, `pa` or similar), stack ends sorted.

- [ ] **Step 6: Test COMPLEX strategy with correctness checker**

```bash
python3 << 'EOF'
import subprocess, random
nums = random.sample(range(100000), 500)
args = list(map(str, nums))
result = subprocess.run(['./push_swap', '--complex'] + args, capture_output=True, text=True)
ops = [o for o in result.stdout.strip().split('\n') if o]
a = nums[:]
b = []
for op in ops:
    if op == 'ra' and a: a.append(a.pop(0))
    elif op == 'rb' and b: b.append(b.pop(0))
    elif op == 'rr':
        if a: a.append(a.pop(0))
        if b: b.append(b.pop(0))
    elif op == 'rra' and a: a.insert(0, a.pop())
    elif op == 'rrb' and b: b.insert(0, b.pop())
    elif op == 'rrr':
        if a: a.insert(0, a.pop())
        if b: b.insert(0, b.pop())
    elif op == 'pa' and b: a.insert(0, b.pop(0))
    elif op == 'pb' and a: b.insert(0, a.pop(0))
    elif op == 'sa' and len(a) >= 2: a[0], a[1] = a[1], a[0]
    elif op == 'sb' and len(b) >= 2: b[0], b[1] = b[1], b[0]
    elif op == 'ss':
        if len(a) >= 2: a[0], a[1] = a[1], a[0]
        if len(b) >= 2: b[0], b[1] = b[1], b[0]
print(f"ops: {len(ops)}  sorted: {a == sorted(nums)}  b_empty: {b == []}")
EOF
```

Expected output: `ops: ~4500  sorted: True  b_empty: True`
Op count must be ≤ 5500 for full score.

- [ ] **Step 7: Test bench flag**

```bash
./push_swap --bench --complex 5 3 1 4 2
```

Expected: ops printed to stdout first, then bench summary lines like `pa: 10`, `pb: 10`, `ra: N`, etc.

- [ ] **Step 8: Test error cases**

```bash
./push_swap 1 a 3         # non-digit → Error on stderr, exit non-zero
./push_swap 1 2 2         # duplicate → Error on stderr
./push_swap               # no args → exit 1, no output
./push_swap 2147483648    # overflow → Error on stderr
```

- [ ] **Step 9: Norm check everything**

```bash
norminette checks.c complex.c main.c medium.c
```

Expected: OK for all.

- [ ] **Step 10: Commit**

```bash
git add push_swap/main.c push_swap/medium.c
git commit -m "feat: wire up dispatch, bench output, sorted guard in main"
```

---

## Self-Review

**Spec coverage:**
- LSD radix sort algorithm → Task 4 `complex_pass` + `sort_complex` ✓
- `set_ranks` promoted to non-static → Task 2 ✓
- `is_sorted` in checks.c, declared in header → Task 3 ✓
- `push_swap.h` updated with all three declarations → Task 1 ✓
- `main.c` rewritten: dispatch, bench, sorted guard, `free_nodes(data.b.top)` → Task 5 ✓
- ADAPTIVE picks by size (≤5 simple, ≤50 medium, else complex) → Task 5 `dispatch` ✓
- Norm fixes (simple.c header, block comments) → Task 1 ✓
- `complex.c` added to Makefile → Task 4 ✓

**Placeholder scan:** None found.

**Type consistency:**
- `set_ranks(t_stack *a)` — declared Task 1, defined Task 2, called Task 5 ✓
- `is_sorted(t_stack *a)` — declared Task 1, defined Task 3, called Task 5 ✓
- `sort_complex(t_data *data)` — declared Task 1, defined Task 4, called Task 5 ✓
