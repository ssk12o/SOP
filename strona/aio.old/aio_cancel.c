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

#define BLOCK_SIZE (size_t)(1024 * 1024 * 1024) // 1GB

int main(int argc, const char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "File path is required\n");
    return 1;
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    perror("open()");
    return 1;
  }
  struct stat st;
  memset(&st, 0, sizeof(st));
  int ret = fstat(fd, &st);
  if (ret < 0) {
    perror("open()");
    return 1;
  }

  printf("File size: %ld bytes\n", st.st_size);

  char *buff = (char *)malloc(st.st_size);
  if (buff == NULL) {
    perror("malloc()");
    return 1;
  }
  int blocks = (int)((st.st_size + BLOCK_SIZE - 1) / BLOCK_SIZE);
  struct aiocb *cbs = (struct aiocb *)malloc(blocks * sizeof(struct aiocb));
  struct aiocb **cb_ptrs =
      (struct aiocb **)malloc(blocks * sizeof(struct aiocb *));
  if (cbs == NULL || cb_ptrs == NULL) {
    perror("malloc()");
    return 1;
  }

  printf("Blocks: %d\n", blocks);

  for (int i = 0; i < blocks; ++i) {
    memset(&cbs[i], 0, sizeof(cbs[i]));
    cbs[i].aio_fildes = fd;
    cbs[i].aio_offset = i * BLOCK_SIZE;
    cbs[i].aio_buf = buff + i * BLOCK_SIZE;
    cbs[i].aio_nbytes =
        (i + 1 == blocks) ? (st.st_size - i * BLOCK_SIZE) : BLOCK_SIZE;
    cbs[i].aio_lio_opcode = LIO_READ;

    cb_ptrs[i] = &cbs[i];

    printf("read[%d]: offset %ld, nbytes: %ld\n", i, cb_ptrs[i]->aio_offset,
           cb_ptrs[i]->aio_nbytes);
  }

  ret = lio_listio(LIO_NOWAIT, cb_ptrs, blocks, NULL);
  if (ret < 0) {
    perror("lio_listio()");
    return 1;
  }

  // sleep(2); TODO: uncomment

  switch (aio_cancel(fd, NULL)) {
  case AIO_CANCELED:
    printf("AIO_CANCELED\n");
    break;
  case AIO_NOTCANCELED:
    printf("AIO_NOTCANCELED\n");
    break;
  case AIO_ALLDONE:
    printf("AIO_ALLDONE\n");
    break;
  default:
    perror("aio_cancel()");
    return 1;
  }

  for (int i = 0; i < blocks; ++i) {
    if (aio_suspend(cb_ptrs, blocks, NULL) < 0) {
      perror("aio_suspend");
      return 1;
    }

    printf("suspend[%d]\n", i);

    for (int j = 0; j < blocks; ++j) {
      if (cb_ptrs[j] == NULL) {
        printf("read[%d] done\n", j);
        continue;
      }

      if (aio_error(cb_ptrs[j]) == EINPROGRESS) {
        printf("read[%d] is still in progress\n", j);
        continue;
      } else {
        ssize_t read_size = aio_return(cb_ptrs[j]);
        printf("read[%d] returned %ld\n", j, read_size);
        cb_ptrs[j] = NULL; // Important!
      }
    }

    printf("\n");
  }

  free(buff);
  free(cbs);
  free(cb_ptrs);
  close(fd);

  return 0;
}
