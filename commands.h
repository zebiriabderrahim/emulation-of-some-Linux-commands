#ifndef COMMANDS_H
#define COMMANDS_H

#define BUFFER_SIZE 4096


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// Function prototype for the copy function
void copy(const char *src, const char *dest);

#endif // COMMANDS_H
