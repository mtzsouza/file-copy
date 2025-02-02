#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        perror("must include source file, destination file, and size of chunk in bytes");
        return 1;
    }

    int source = open(argv[1], O_RDONLY);
    if (source < 0) {
        perror("couln't open source file");
        return 1;
    }

    int destination = open(argv[2], O_CREAT | O_WRONLY, 0644);
    if (destination < 0) {
        perror("couldn't create destination file");
        close(source);
        return 1;
    }

    int chunk_size = atoi(argv[3]);
    if (chunk_size <= 0) {
        perror("size of chunk must be greater than 0");
        return 1;
    }

    ssize_t bytes_read;
    char chunk[chunk_size];
    while ((bytes_read = read(source, chunk, chunk_size)) > 0) {
        write(destination, chunk, bytes_read);
    }

    close(source);
    close(destination);
    return 0;
}
