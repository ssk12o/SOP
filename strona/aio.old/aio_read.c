#include <aio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef _POSIX_ASYNCHRONOUS_IO
#error System does not support asyncrhonous I/O
#endif

#define BLOCK_SIZE 1000000

int main(int argc, const char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "File path is required\n");
    return 1;
  }

  char *buffer = (char *)malloc(BLOCK_SIZE);
  if (buffer == NULL) {
    perror("malloc()");
    return 1;
  }

  struct aiocb cb;
  memset(&cb, 0, sizeof(struct aiocb));

  cb.aio_fildes = open(argv[1], O_RDONLY);
  if (cb.aio_fildes < 0) {
    perror("open()");
    return 1;
  }
  cb.aio_offset = 0;
  cb.aio_buf = buffer;
  cb.aio_nbytes = BLOCK_SIZE;

  if (aio_read(&cb) < 0) { // read(fd, buffer, 100000);
    perror("aio_read()");
    return 1;
  }

  // Do not touch &cb from now on ...

  // vVVVv BAADC0DE! Busy waiting here vVVVv
  int err;
  while ((err = aio_error(&cb)) == EINPROGRESS) {
    printf("Operation in progress...\n");
  }

  if (err != 0) {
    fprintf(stderr, "aio_read(): %s\n", strerror(err));
  }

  ssize_t ret = aio_return(&cb);
  printf("aio_read returned %ld\n", ret);

  if (ret >= 0)
    printf("%.40s\n(...)\n", (char *)buffer);

  free(buffer);
  close(cb.aio_fildes);

  return 0;
}
