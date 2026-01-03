# Libft
Reimplementing specific libc functions and creating custom C functions for string, memory, and linked list manipulation.

## Functions from libc

### String Manipulation 

* `isalpha` Checks for an alphabetic character.
* `isdigit` Checks for a digit (0 through 9).
* `isalnum` Checks for an alphanumeric character.
* `isascii` Checks whether c fits into the ASCII character set.
* `isprint` Checks for any printable character except space.
* `strlen`  Calculates the length of a string excluding '\0'.
* `strchr`  Returns a pointer to the first occurrence of the character c in the string s.
* `strrchr` Returns a pointer to the last occurrence of the character c in the string s.
* `strncmp` Compares the first n bytes of two strings and returns an integer indicating the result of the comparison. 
* `strnstr` Locates a substring in the first n bytes of a string.
* `strlcpy` Safely copies the NUL-terminated string src to the buffer dst (up to size bytes), guarantees NUL-termination (if size > 0), and returns the total length of src. 
* `strlcat` Safely appends the NUL-terminated string src to the end of dst (within size total bytes for dst), guarantees NUL-termination (if space exists), and returns the combined length of the original dst plus the length of src.
* `toupper` Convert character to uppercase.
* `tolower` Convert character to lowercase.
* `atoi` Converts initial portion of string to int.
* `strdup`* Duplicates a string using allocated memory.

### Memory Manipulation 
* `memset` Fills memory with a constant byte.
* `bzero` Fills memory with zero bytes.
* `memcpy` Copies memory area.
* `memmove` Copies memory area, handling overlap.
* `memchr` Scans memory for a character.
* `memcmp` Compares memory areas.
* `calloc`* Allocates memory for an array of elements and initializes all bits of the allocated memory to zero.

`*` need malloc()

## Additional functions

### String manipulation

* `ft_substr` Allocates and returns a substring from string 's', starting at index 'start' with a maximum length 'len'.
* `ft_strjoin` Allocates and returns a new string, result of the concatenation of 's1' and 's2'.
* `ft_strtrim` Allocates and returns a copy of 's1' with characters from 'set' removed from the beginning and end.
* `ft_split` Allocates and returns an array of strings obtained by splitting 's' using char 'c' as delimiter; array ends with NULL.
* `ft_itoa` Allocates and returns a string representing the integer 'n' received; handles negative numbers.
* `ft_strmapi` Applies function 'f' to each character of 's' (with index) to create a new allocated string.
* `ft_striteri` Applies function 'f' to each character of string 's' (with index), passing the character's address for modification.

### I/O

* `ft_putchar_fd` Outputs the character 'c' to the given file descriptor 'fd'.
* `ft_putstr_fd` Outputs the string 's' to the given file descriptor 'fd'.
* `ft_putendl_fd` Outputs the string 's' to the given file descriptor 'fd', followed by a newline.
* `ft_putnbr_fd` Outputs the integer 'n' to the given file descriptor 'fd'.

## Bonus

### Linked lists
* `ft_lstnew` Allocates and returns a new node with the given content and a NULL next pointer.
* `ft_lstadd_front` Adds the node 'new' at the beginning of the list.
* `ft_lstsize` Counts and returns the number of nodes in a list.
* `ft_lstlast` Returns the last node of the list.
* `ft_lstadd_back` Adds the node 'new' at the end of the list.
* `ft_lstdelone` Takes a node and frees its content using the function 'del', then frees the node itself but not its successor.
* `ft_lstclear` Deletes and frees a node and all its successors using 'del'
* `ft_lstiter` Iterates through the list and applies the function 'f' to the content of each node. 
* `ft_lstmap` Creates a new list by applying function 'f' to each node's content from the original list; uses 'del' to free content if needed.

## Moulinette score
test_ft_isalpha: OK | test_ft_isdigit: OK | test_ft_isalnum: OK | test_ft_isascii: OK | test_ft_isprint: OK | test_ft_strlen: OK | test_ft_memset: OK | test_ft_bzero: OK | test_ft_memcpy: OK | test_ft_memmove: OK | test_ft_strlcpy: OK | test_ft_strlcat: OK | test_ft_toupper: OK | test_ft_tolower: OK | test_ft_strchr: OK | test_ft_strrchr: OK | test_ft_strncmp: OK | test_ft_memchr: OK | test_ft_memcmp: OK | test_ft_strnstr: OK | test_ft_atoi: OK | test_ft_calloc: OK | test_ft_strdup: OK | test_ft_substr: OK | test_ft_strjoin: OK | test_ft_strtrim: OK | test_ft_split: OK | test_ft_itoa: OK | test_ft_strmapi: OK | test_ft_striteri: OK | test_ft_putchar_fd: OK | test_ft_putstr_fd: OK | test_ft_putendl_fd: OK | test_ft_putnbr_fd: OK | bonus: 9/9 functions correct | 125/125

## Common Core Custom Additions
* `ft_printf` Formats and prints data to the standard output. It mimics the behavior of the standard `printf` and supports the c, s, p, d, i, u, x, X, % specifiers.
