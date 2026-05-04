## Overview

libft is a general-purpose C library providing a collection of common utility functions designed for reusability and efficiency. It includes implementations for string manipulation, memory operations, data structure management (linked lists, stacks, queues), and error handling. The libr...

## Features

libft provides the following capabilities:

- **Memory Management**: Safe and efficient memory allocation/deallocation utilities.
- **String Operations**: Common string manipulation and formatting functions.
- **Data Structures**: Implementations of linked lists, stacks, and queues with robust traversal and modification support.
- **Error Handling**: Consistent error reporting and recovery mechanisms.
- **Type-Specific Utilities**: Helper functions for character classification, integer operations, and void pointer management.

## Chapter 5 Requirements

### ft_lstmap Function

**Purpose**: The `ft_lstmap` function creates a new list by applying a given function to each element of an existing list.

**Parameters**:
- `lst`: A pointer to the first node of the original list.
- `f`: A pointer to the function to apply to each element.
- `del`: A pointer to the function used to delete content in case of failure.

**Return Value**: The new list or NULL if the allocation fails.

**Memory Management Behavior**: If an allocation fails, all previously allocated nodes are freed using the `del` function and NULL is returned. Otherwise, a new list with the transformed elements is returned.