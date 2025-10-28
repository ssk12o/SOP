# Lecture 3 - Processes

---

### Listing processes

```shell
ps -eo pid,state,command
```

From `man ps`
```text
PROCESS STATE CODES
Here are the different values that the s, stat and state output specifiers
(header "STAT" or "S") will display to describe the state of a process:

D    uninterruptible sleep (usually IO)
I    Idle kernel thread
R    running or runnable (on run queue)
S    interruptible sleep (waiting for an event to complete)
T    stopped by job control signal
t    stopped by debugger during the tracing
W    paging (not valid since the 2.6.xx kernel)
X    dead (should never be seen)
Z    defunct ("zombie") process, terminated but not reaped by its parent
```
Try also listing contents of the `/proc` subdirectories.

### Linux task structure (PCB)

[struct task_struct](https://elixir.bootlin.com/linux/latest/source/include/linux/sched.h#L738)

Some of its members:
* [PID](https://elixir.bootlin.com/linux/v6.5.8/source/include/linux/sched.h#L962)
* [state](https://elixir.bootlin.com/linux/v6.5.8/source/include/linux/sched.h#L746)
  * [enum](https://elixir.bootlin.com/linux/v6.5.8/source/include/linux/sched.h#L86)
* [childrend](https://elixir.bootlin.com/linux/v6.5.8/source/include/linux/sched.h#L984)
* [exit code](https://elixir.bootlin.com/linux/v6.5.8/source/include/linux/sched.h#L875)
* [CPU state](https://elixir.bootlin.com/linux/v6.5.8/source/include/linux/sched.h#L1541)

### Virtual address space

```shell
gcc -o /tmp/vm vm.c
/tmp/vm
```

### Counting context switches

```shell
gcc -O0 -o  /tmp/cs cs.c
perf stat -e cs /tmp/cs
```

### Hello fork()

```shell
gcc -o /tmp/hello hello.c
/tmp/hello
```

### Descriptor inheritance

```shell
rm -Rf /tmp/fork_write.txt
gcc -o /tmp/fork_write -g fork_write.c
/tmp/fork_write /tmp/fork_write.txt aaa bbbb
```

```shell
watch -n0.1 cat /tmp/fork_write.txt
```

### Waiting for children

```shell
gcc -o /tmp/wait wait.c
/tmp/wait
```

### Orphans

```shell
gcc -o /tmp/orphan orphan.c
/tmp/orphan
```

### Zombies

```shell
gcc -o /tmp/zombie zombie.c
/tmp/zombie 3
```

Run `ps -eo pid,state,cmd` during the program execution.

### Exec

```shell
gcc -o /tmp/env env.c
/tmp/env
```

```shell
gcc -o /tmp/exec exec.c
/tmp/exec
```

### Clone() example

```shell
gcc -o /tmp/clone clone.c
/tmp/clone
```
