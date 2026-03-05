Get Next Line (GNL)

Author: tlaghzal

Overview

Get Next Line is a 42 project aimed at creating a function that reads a file line by line. It’s designed to efficiently handle reading from file descriptors, dynamically allocating memory as needed, and returning each line until the end of the file.

The main function get_next_line will:

Read from a given file descriptor.

Return one line at a time, including the newline character (\n).

Return NULL when there’s nothing more to read or if an error occurs.

This project focuses on:

Mastering memory management in C (malloc, free).

Handling file descriptors.

Implementing static variables for persistent state across function calls.

Features

Reads from any valid file descriptor.

Supports multiple file descriptors simultaneously.

Handles files of any size.

Efficient memory allocation and cleanup.

Usage
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
Files

get_next_line.c – main function implementation.

get_next_line_utils.c – helper functions (strlen, strdup, join, etc.).

get_next_line.h – header file with function prototypes and includes.

Compilation
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c -o gnl

You can change BUFFER_SIZE to test different buffer sizes.

Testing

Test with text files of varying sizes.

Test with multiple file descriptors simultaneously.

Ensure memory leaks are checked with valgrind.

Notes

Always free the returned line to prevent memory leaks.

Works with both text files and standard input (stdin).
