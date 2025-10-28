# Lecture 8 - The Scheduler

---

```shell
ps -c a
```

```
-   not reported
TS  SCHED_OTHER
FF  SCHED_FIFO
RR  SCHED_RR
B   SCHED_BATCH
ISO SCHED_ISO
IDL SCHED_IDLE
DLN SCHED_DEADLINE
?   unknown value
```

Simulate system CPU load:

```shell
stress-ng --matrix 0
```

```shell
gcc -g -o /tmp/bursts bursts.c 
/tmp/bursts
```

```shell
gcc -DCPU_AFFINITY=0 -g -o /tmp/bursts bursts.c 
/tmp/bursts
```

```shell
gcc -DSCHED_POLICY=SCHED_FIFO -DSCHED_PRIORITY=99 -g -o /tmp/bursts bursts.c 
sudo /tmp/bursts
```
