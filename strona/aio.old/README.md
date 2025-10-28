# Lecture 7 - Asynchronous I/O

---

Slides up to `aio_read`/`aio_write`.

Generate big file:

```shell
dd if=/dev/urandom of=/tmp/bigfile bs=4M count=1024
ls -lah /tmp/bigfile
```

### Basic examples

Basic `aio_read()` usage example:

```shell
gcc -g -o /tmp/aio_read aio_read.c -lrt
/tmp/aio_read /tmp/bigfile
```

Review _Status of AIO_ slides.

Review _Synchornization of AIO_ slides.

```shell
gcc -g -o /tmp/aio_suspend aio_suspend.c -lrt
/tmp/aio_suspend /tmp/bigfile
```

### List IO

Review `lio_listio` slides.

```shell
gcc -g -o /tmp/listio_wait listio_wait.c -lrt
/tmp/listio_wait /tmp/bigfile
```

```shell
gcc -g -o /tmp/listio_nowait listio_nowait.c -lrt
/tmp/listio_nowait /tmp/bigfile
```

### Notifications

```shell
gcc -g -o /tmp/signal_notification signal_notification.c -lrt
/tmp/signal_notification /tmp/bigfile
```

```shell
gcc -g -o /tmp/thread_notification thread_notification.c -lrt
/tmp/thread_notification /tmp/bigfile
```

```shell
gcc -g -o /tmp/listio_notification listio_notification.c -lrt
/tmp/listio_notification /tmp/bigfile
```

### Cancellation

```shell
gcc -g -o /tmp/aio_cancel aio_cancel.c -lrt
/tmp/aio_cancel /tmp/bigfile
```
