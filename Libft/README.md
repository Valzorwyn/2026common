## Overview

libft is a general-purpose C library providing a collection of common utility functions designed for reusability and efficiency. It includes implementations for string manipulation, memory operations, data structure management (linked lists, stacks, queues), and error handling. The library follows best practices in C programming, emphasizing proper memory management, portability, and performance optimization through carefully implemented low-level operations.

### Chapter 5 Requirements: `ft_lstmap`

## Purpose
The `ft_lstmap` function iterates through a linked list (`t_list`), applies a user-defined function to the content of each node, and creates a new linked list containing the results. It is commonly used for transforming lists while preserving their structure.

### Parameters
- `lst`: A pointer to the first node of the original linked list.
- `f`: A pointer to the function to apply to each node's content.
- `del`: A pointer to the function to delete the content of a node if an error occurs.

### Return Value
A pointer to the first node of the new linked list, or `NULL` if an allocation fails.

### Memory Management Behavior
The function allocates memory for each new node in the resulting list. If any allocation fails, it deletes all previously allocated nodes using the provided `del` function and returns `NULL`.