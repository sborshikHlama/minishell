# LIBFT

Libft is a custom implementation of the standard C library functions.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
- [Contributing](#contributing)
- [License](#license)

## Installation

To use this library in your own projects, clone the repository and compile the library:

```sh
git clone https://github.com/sborshikHlama/LIBFT.git
cd LIBFT
make
This will create a libft.a file which can be linked with your C programs.

Usage

Include the library header in your C files:
#include "libft.h"

Compile your program with the library:
sh
gcc -o my_program my_program.c -L. -lft
```
## Functions

Libft implements the following functions:

Part 1 - Libc functions
ft_memset
ft_bzero
ft_memcpy
ft_memccpy
ft_memmove
ft_memchr
ft_memcmp
ft_strlen
ft_strdup
ft_strcpy
ft_strncpy
ft_strcat
ft_strncat
ft_strlcat
ft_strchr
ft_strrchr
ft_strstr
ft_strnstr
ft_strcmp
ft_strncmp
ft_atoi
ft_isalpha
ft_isdigit
ft_isalnum
ft_isascii
ft_isprint
ft_toupper
ft_tolower

Part 2 - Additional functions
ft_memalloc
ft_memdel
ft_strnew
ft_strdel
ft_strclr
ft_striter
ft_striteri
ft_strmap
ft_strmapi
ft_strequ
ft_strnequ
ft_strsub
ft_strjoin
ft_strtrim
ft_strsplit
ft_itoa
ft_putchar
ft_putstr
ft_putendl
ft_putnbr
ft_putchar_fd
ft_putstr_fd
ft_putendl_fd
ft_putnbr_fd

Bonus part
ft_lstnew
ft_lstdelone
ft_lstdel
ft_lstadd
ft_lstiter
ft_lstmap

## Contributing

If you would like to contribute to this project, please fork the repository and create a pull request with your changes.
Ensure that your code adheres to the project's coding standards and includes appropriate tests.
Remember to follow the Norm code standard!

License
This project is licensed under the MIT License. See the LICENSE file for more details.
