# push_swap: sort_complex (LSD Radix Sort)

**Date:** 2026-06-23
**Scope:** Add COMPLEX strategy (LSD radix sort) to push_swap; wire up main dispatch; clean debug code.

---

## Algorithm

LSD (Least Significant Bit first) radix sort over normalized ranks (0..n-1).

For each bit position `k` from 0 to `ceil(log₂(n)) - 1`:
1. Iterate exactly `n` times over A:
   - `rank & (1 << k)` == 0 → `pb` (element belongs in lower half)
   - `rank & (1 << k)` == 1 → `ra` (element stays, cycles to bottom)
2. Flush B back to A with `pa` × `b.size`

After all bits, A is sorted ascending.

**Complexity:** O(n log n) ops and computation.
**Expected ops for n=500:** ~4500 (9 passes × ~500 ops), well under the 5500 full-score threshold.

---

## Rank Extraction

`medium_set_ranks` is promoted to a shared, non-static `set_ranks(t_stack *a)`:
- Stays in `medium.c`, loses the `static` qualifier
- Declared in `push_swap.h`
- Called once in `main` after validation, before strategy dispatch
- Both `sort_medium` and `sort_complex` rely on it; calling it unconditionally keeps dispatch clean

---

## New File: complex.c

Two functions, both Norm-compliant (≤25 lines, ≤5 params):

### `complex_pass(t_data *data, int bit)`
- Saves `n = data->a.size` before loop (size changes mid-loop as `pb` shrinks A)
- Iterates `n` times: `pb` if bit clear, `ra` if bit set
- Flushes B to A with `pa` until `b.size == 0`

### `sort_complex(t_data *data)`
- Guards `n <= 1`, returns immediately
- Computes `bits`: `while ((1 << bits) < n) ++bits`
- Calls `complex_pass` for each bit 0..bits-1

---

## Changes to Existing Files

### push_swap.h
- Add `void set_ranks(t_stack *a);`
- Add `void sort_complex(t_data *data);`
- Add `int is_sorted(t_stack *a);`

### medium.c
- Remove `static` from `medium_set_ranks`, rename to `set_ranks`
- Remove its internal call — `sort_medium` now relies on `main` having called `set_ranks` first

### checks.c
- Add `int is_sorted(t_stack *a)`: linear scan, returns 1 if each node ≤ next, 0 otherwise; non-static, declared in header

### main.c
- Remove `#include <stdio.h>`, `print_info`, `rev_rot_a` test call
- After validation: call `set_ranks`, then `is_sorted` early-exit
- Strategy dispatch:
  - `SIMPLE`   → `sort_simple`
  - `MEDIUM`   → `sort_medium`
  - `COMPLEX`  → `sort_complex`
  - `ADAPTIVE` → size ≤ 5: `sort_simple`; size ≤ 50: `sort_medium`; else: `sort_complex`
- If `data.bench.print`: write op counts (`sa: N`, `pb: N`, etc.) for all non-zero counters after sort
- Add `free_nodes(data.b.top)` alongside existing `free_nodes(data.a.top)`

### Makefile
- Add `complex.c` to `SOURCE_FILES`

---

## is_sorted

```
static int is_sorted(t_stack *a)
    cur = a->top
    while cur && cur->next:
        if cur->nbr > cur->next->nbr: return 0
        cur = cur->next
    return 1
```

Non-static in `checks.c`, declared in `push_swap.h`.

---

## Norm Compliance

- No `for`, no ternary, no assignments in conditions
- All variable declarations at top of scope
- `++bits` as standalone statement, `ii` / `jj` loop indices
- Block comments removed from `medium.c` and `simple.c` (existing violation, fix in this pass)
- `simple.c` missing 42 header — add it

---

## Out of Scope

- ADAPTIVE threshold tuning (left for post-benchmarking)
- Bench output format (minimal `name: count\n` per non-zero counter, subject does not specify)
- sort_complex for n ≤ 3 (handled by is_sorted early-exit and sort_simple fallback in ADAPTIVE)
