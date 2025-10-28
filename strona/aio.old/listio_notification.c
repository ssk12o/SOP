#include <aio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

#ifndef _POSIX_ASYNCHRONOUS_IO
#error System does not support asyncrhonous I/O
#endif

#define BLOCK_SIZE (size_t)(1024 * 1024 * 1024) // 1GB

void single_complection_handler(sigval_t sigval) {
  struct aiocb *cb = (struct aiocb *)sigval.sival_ptr;
  int block = (int)(cb->aio_offset / BLOCK_SIZE);

  printf("[%d] single_complection_handler() started\n", block);
  int ret = aio_error(cb);
  if (ret != 0) {
    printf("[%d] aio_error(): %s\n", block, strerror(ret));
  }

  ssize_t n = aio_return(cb);
  printf("[%d] aio_read returned %ld\n", block, n);

  if (ret >= 0)
    printf("[%d] %.40s (...)\n", block, (char *)cb->aio_buf);
}

void full_complection_handler(sigval_t sigval) {
  printf("full_complection_handler() started\n");
}

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
    cbs[i].aio_fildes = open(argv[1], O_RDONLY);
    if (cbs[i].aio_fildes < 0) {
      perror("open()");
      return 1;
    }
    cbs[i].aio_offset = i * BLOCK_SIZE;
    cbs[i].aio_buf = buff + i * BLOCK_SIZE;
    cbs[i].aio_nbytes =
        (i + 1 == blocks) ? (st.st_size - i * BLOCK_SIZE) : BLOCK_SIZE;
    cbs[i].aio_lio_opcode = LIO_READ;
    cbs[i].aio_sigevent.sigev_notify = SIGEV_THREAD;
    cbs[i].aio_sigevent.sigev_notify_function = single_complection_handler;
    cbs[i].aio_sigevent.sigev_value.sival_ptr = &cbs[i];

    cb_ptrs[i] = &cbs[i];

    printf("read[%d]: offset %ld, nbytes: %ld\n", i, cb_ptrs[i]->aio_offset,
           cb_ptrs[i]->aio_nbytes);
  }

  struct sigevent lio_ev;
  memset(&lio_ev, 0, sizeof(lio_ev));
  lio_ev.sigev_notify = SIGEV_THREAD;
  lio_ev.sigev_notify_function = full_complection_handler;

  ret = lio_listio(LIO_NOWAIT, cb_ptrs, blocks, &lio_ev);
  if (ret < 0) {
    perror("lio_listio()");
    return 1;
  }

  char cmd[10];
  while (scanf("%9s", cmd) > 0) {
    printf("Doing %s ...\n", cmd);
    if (strcmp(cmd, "exit") == 0)
      break;
  }

  free(buff);
  free(cbs);
  free(cb_ptrs);
  close(fd);

  return 0;
}
