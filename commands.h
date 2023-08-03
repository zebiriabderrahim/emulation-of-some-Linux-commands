#ifndef COMMANDS_H
#define COMMANDS_H

#define BUFFER_SIZE 4096
#define COPY_DEFAULT_FLAGS O_WRONLY | O_CREAT | O_EXCL
#define T_DEFAULT_FLAGS   O_WRONLY | O_CREAT | O_TRUNC
#define DEFAULT_PERMISSION 0644



#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

void copy(const char *src, const char *dest);
void t(int argc, char *argv[]);

#endif // COMMANDS_H
