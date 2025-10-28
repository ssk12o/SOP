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

void signal_handler(int sig, siginfo_t *info, void *context) {
  printf("Received signal %d\n", sig);
  struct aiocb *cb = (struct aiocb *)info->si_value.sival_ptr;
  int ret = aio_error(cb);
  printf("aio_error() returned %d\n", ret);
}

int main(int argc, const char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "File path is required\n");
    return 1;
  }

  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));

  sa.sa_flags = SA_SIGINFO; // Important
  sa.sa_sigaction = signal_handler;

  if (sigaction(SIGUSR1, &sa, NULL) < 0) {
    perror("sigaction(): ");
    return 1;
  }

  sigset_t mask, oldmask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);
  if (sigprocmask(SIG_BLOCK, &mask, &oldmask) < 0) {
    perror("sigprocmask");
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

  // SIGNAL NOTIFICATION SETUP
  cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
  cb.aio_sigevent.sigev_signo = SIGUSR1;
  cb.aio_sigevent.sigev_value.sival_ptr = &cb;

  if (aio_read(&cb) < 0) {
    perror("aio_read()");
    return 1;
  }

  // Do not touch &cb from now on ...

  sigsuspend(&oldmask);

  int err = aio_error(&cb);
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
