#include "commands.h"
#include <sys/fcntl.h>

void copy(const char *src, const char *dest)
{
    int fd_in = open(src, O_RDONLY);
    if (fd_in == -1)
    {
        perror("open source file failed");
        return;
    }

    int fd_out = open(dest, COPY_DEFAULT_FLAGS, DEFAULT_PERMISSION);
    if (fd_out == -1)
    {
        perror("open destination file failed");
        close(fd_in);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(fd_in, buffer, sizeof(buffer))) > 0)
    {
        char *p = buffer;
        while (bytes_read > bytes_written)
        {
            bytes_written = write(fd_out, p, bytes_read);
            if (bytes_written == -1)
            {
                perror("write failed");
                close(fd_in);
                close(fd_out);
                return;
            }
            bytes_read -= bytes_written;
            p += bytes_written;
        }
    }

    if (bytes_read == -1)
    {
        perror("read failed");
    }

    if (close(fd_in) == -1 || close(fd_out) == -1)
    {
        perror("close failed");
    }
}

static void write_all(int fd, char *buffer, ssize_t bytes_read) {
    ssize_t bytes_written = write(fd, buffer, bytes_read);
    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return;
    }
    if (bytes_written < bytes_read) {
        write_all(fd, buffer + bytes_written, bytes_read - bytes_written);
    }
}


void t(int argc, char *argv[])
{
    int fds[argc];
    fds[0] = STDOUT_FILENO;
    for (int i = 1; i < argc; i++)
    {
        fds[i] = open(argv[i], T_DEFAULT_FLAGS, DEFAULT_PERMISSION);
        if (fds[i] == -1)
        {
            perror("open source file failed");
            exit(EXIT_FAILURE);
        }
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
    {
        for (size_t i = 0; i < argc; i++)
            write_all(fds[i], buffer, bytes_read);
    }
    for (size_t i = 0; i < argc; i++)
        close(fds[i]);
}
