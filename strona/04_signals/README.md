# Lecture 4 - Signals

---

From `man 7 signal`:

```text
Signal      Standard   Action   Comment
────────────────────────────────────────────────────────────────────────
SIGABRT      P1990      Core    Abort signal from abort(3)
SIGALRM      P1990      Term    Timer signal from alarm(2)
SIGBUS       P2001      Core    Bus error (bad memory access)
SIGCHLD      P1990      Ign     Child stopped or terminated
SIGCLD         -        Ign     A synonym for SIGCHLD
SIGCONT      P1990      Cont    Continue if stopped
SIGEMT         -        Term    Emulator trap
SIGFPE       P1990      Core    Floating-point exception
SIGHUP       P1990      Term    Hangup detected on controlling terminal
                               or death of controlling process
SIGILL       P1990      Core    Illegal Instruction
SIGINFO        -                A synonym for SIGPWR
SIGINT       P1990      Term    Interrupt from keyboard
SIGIO          -        Term    I/O now possible (4.2BSD)
SIGIOT         -        Core    IOT trap. A synonym for SIGABRT
SIGKILL      P1990      Term    Kill signal
SIGLOST        -        Term    File lock lost (unused)
SIGPIPE      P1990      Term    Broken pipe: write to pipe with no
                               readers; see pipe(7)
SIGPOLL      P2001      Term    Pollable event (Sys V).
                               Synonym for SIGIO
SIGPROF      P2001      Term    Profiling timer expired
SIGPWR         -        Term    Power failure (System V)
SIGQUIT      P1990      Core    Quit from keyboard
SIGSEGV      P1990      Core    Invalid memory reference
SIGSTKFLT      -        Term    Stack fault on coprocessor (unused)
SIGSTOP      P1990      Stop    Stop process
SIGTSTP      P1990      Stop    Stop typed at terminal
SIGSYS       P2001      Core    Bad system call (SVr4);
                               see also seccomp(2)
SIGTERM      P1990      Term    Termination signal
SIGTRAP      P2001      Core    Trace/breakpoint trap
SIGTTIN      P1990      Stop    Terminal input for background process
SIGTTOU      P1990      Stop    Terminal output for background process
SIGUNUSED      -        Core    Synonymous with SIGSYS
SIGURG       P2001      Ign     Urgent condition on socket (4.2BSD)
SIGUSR1      P1990      Term    User-defined signal 1
SIGUSR2      P1990      Term    User-defined signal 2

SIGVTALRM    P2001      Term    Virtual alarm clock (4.2BSD)
SIGXCPU      P2001      Core    CPU time limit exceeded (4.2BSD);
                               see setrlimit(2)
SIGXFSZ      P2001      Core    File size limit exceeded (4.2BSD);
                               see setrlimit(2)
SIGWINCH       -        Ign     Window resize signal (4.3BSD, Sun)
```

```text
The signals SIGKILL and SIGSTOP cannot be caught, blocked, or ignored.
```

## The kill() syscall

```shell
gcc -o /tmp/kill -g kill.c
/tmp/kill
```

Try killing:
* One of the children
* Invalid PID
* Whole process group (-PGID)
* PID -1

## Signal action

Signal lifecycle: generation -> pending -> delivery/acceptance

Signals can be:

* **delivered**
  * ignored
  * default handler
  * user-defined handler
* **accepted**

## User-defined handlers

```shell
gcc -o /tmp/basic_handler -g basic_handler.c
/tmp/basic_handler
```

Try pressing C-c and using the `kill` command.

Try also setting the handler to `SIG_IGN` and `SIG_DFL`.

Unblock fork to demonstrate the handler inheritance.

```shell
gcc -o /tmp/segv_handler -g segv_handler.c
/tmp/segv_handler
```

Don't do that at home.

```shell
gcc -o /tmp/handler -g handler.c
/tmp/handler
```

Why program isn't getting killed on typing 0 or -PGID?

```shell
gcc -o /tmp/long_handler -g long_handler.c
/tmp/long_handler
```

Observe signal blocking for the time spent within the handler.

## Blocking signals

```shell
gcc -o /tmp/basic_blocking -g basic_blocking.c
/tmp/basic_blocking
```

```shell
gcc -o /tmp/blocking -g blocking.c
/tmp/blocking
```

Observe contents of proc during execution:

```shell
watch -n0.1 "cat /proc/<pid>/status | grep -E '(Sig|Shd)'"
```

## Meaning of `EINTR`

```shell
gcc -o /tmp/eintr -g eintr.c
/tmp/eintr
```
Try adding `SA_RESTART` flag to sigchld_handler setup.

## Usage of `volatile sigatomic_t`

```shell
gcc -o /tmp/sigatomic -g sigatomic.c
/tmp/sigatomic
```

## `SIGCHLD` signal

```shell
gcc -o /tmp/sigchld -g sigchld.c
/tmp/sigchld
```

## Synchronous handling

```shell
gcc -o /tmp/sigsuspend -g sigsuspend.c
/tmp/sigsuspend
```

```shell
gcc -o /tmp/sigwait -g sigwait.c
/tmp/sigwait
```
