# Lecture 6 - Threads

First review general slides up to pthreads introduction.

---

### Basic examples

```shell
gcc -o /tmp/basic_thread -g basic_thread.c -pthread -fsanitize=address
/tmp/basic_thread
```

```shell
gcc -DNOJOIN -o /tmp/basic_thread -g basic_thread.c -pthread
valgrind --leak-check=full --show-leak-kinds=all /tmp/basic_thread
```

```shell
gcc -o /tmp/thread_args -g thread_args.c -pthread
/tmp/thread_args
```

```shell
gcc -o /tmp/join -g join.c -pthread -fsanitize=address
/tmp/join
```

### Detached threads

Review attribute slides

```shell
gcc -o /tmp/detach -g detach.c -pthread
/tmp/detach
```

```shell
valgrind --leak-check=full --show-leak-kinds=all /tmp/detach
```

### Cancellation

Review thread cancellation slides

```shell
gcc -o /tmp/cancel -g cancel.c -pthread
/tmp/cancel
```

```shell
gcc -DNOCANCEL -o /tmp/cancel -g cancel.c -pthread
/tmp/cancel
```

Review cleanup handlers slides

```shell
gcc -o /tmp/cleanup -g cleanup.c -pthread
/tmp/cleanup
```

```shell
gcc -DASYNC -o /tmp/cleanup -g cleanup.c -pthread
/tmp/cleanup
```

### Concurrent data access

```shell
gcc -o /tmp/concurrent_write -g concurrent_write.c -pthread
/tmp/concurrent_write
```

Try using thread sanitizer:

```shell
gcc -o /tmp/concurrent_write -g concurrent_write.c -pthread -fsanitize=thread
/tmp/concurrent_write
```

Review mutex slides

```shell
gcc -o /tmp/mutex -g mutex.c -pthread
/tmp/mutex
```

### Threads and signals

Review signals slides

```shell
gcc -o /tmp/thread_signals -g thread_signals.c -pthread
/tmp/thread_signals
```

```shell
gcc -o /tmp/thread_kill -g thread_kill.c -pthread
/tmp/thread_kill
```

```shell
gcc -o /tmp/thread_sigsuspend -g thread_sigsuspend.c -pthread
/tmp/thread_sigsuspend
```
