#include <aio.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef _POSIX_ASYNCHRONOUS_IO
#error System does not support asyncrhonous I/O
#endif

#define BLOCK_SIZE (1024 * 1024 * 1024)

void single_complection_handler(sigval_t sigval) {
  printf("Notification thread started\n");
  struct aiocb *cb = (struct aiocb *)sigval.sival_ptr;
  int ret = aio_error(cb);
  printf("aio_error() returned %d\n", ret);

  ssize_t n = aio_return(cb);
  printf("aio_read returned %ld\n", n);

  if (ret >= 0)
    printf("%.40s\n(...)\n", (char *)cb->aio_buf);
}

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

  // THREAD NOTIFICATION SETUP
  cb.aio_sigevent.sigev_notify = SIGEV_THREAD;
  cb.aio_sigevent.sigev_notify_function = single_complection_handler;
  cb.aio_sigevent.sigev_notify_attributes = NULL;
  cb.aio_sigevent.sigev_value.sival_ptr = &cb;

  if (aio_read(&cb) < 0) {
    perror("aio_read()");
    return 1;
  }

  char cmd[10];
  while (scanf("%9s", cmd) > 0) {
    printf("Doing %s ...\n", cmd);
    if (strcmp(cmd, "exit") == 0)
      break;
  }

  free(buffer);
  close(cb.aio_fildes);

  return 0;
}
