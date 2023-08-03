#include "commands.h"


void copy(const char *src, const char *dest) {
    int fd_in = open(src, O_RDONLY);
    if (fd_in == -1) {
        perror("open source file failed");
        return;
    }

    int fd_out = open(dest, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd_out == -1) {
        perror("open destination file failed");
        close(fd_in); // Cleanup: Close the input file descriptor
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(fd_in, buffer, sizeof(buffer))) > 0) {
        char *p = buffer;
        while (bytes_read > 0) {
            bytes_written = write(fd_out, p, bytes_read);
            if (bytes_written == -1) {
                perror("write failed");
                close(fd_in);  
                close(fd_out);
                return;
            }
            bytes_read -= bytes_written;
            p += bytes_written;
        }
    }

    if (bytes_read == -1) {
        perror("read failed");
    }

    if (close(fd_in) == -1 || close(fd_out) == -1) {
        perror("close failed");
    }
}
