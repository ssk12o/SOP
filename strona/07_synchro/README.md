### Synchronization

```shell
# Fixes tsan unexpected memory mapping issues
sudo sysctl vm.mmap_rnd_bits=28 
```

```shell
gcc -o /tmp/01_semaphore_base -g 01_semaphore_base.c -pthread
/tmp/01_semaphore_base
```

```shell
gcc -o /tmp/07_semaphore -g 07_semaphore.c -pthread
/tmp/07_semaphore
```

```shell
gcc -o /tmp/11_sem_open -g 11_sem_open.c -pthread
/tmp/11_sem_open
```

```shell
gcc -o /tmp/14_cv_base -g 14_cv_base.c -pthread
/tmp/14_cv_base
```

```shell
gcc -o /tmp/15_cv -g 15_cv.c -pthread -fsanitize=thread
/tmp/15_cv
```

```shell
gcc -o /tmp/20_barrier -g 20_barrier.c -pthread -fsanitize=thread
/tmp/20_barrier
```
