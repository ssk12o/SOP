#define _GNU_SOURCE

#include <assert.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARR_SIZE (4ul * 1024 * 1024 * 1024)


// #define CPU_AFFINITY 0
// #define SCHED_POLICY SCHED_FIFO
// #define SCHED_PRIORITY 1

int main(int argc, char **argv) {

#ifdef CPU_AFFINITY
  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(CPU_AFFINITY, &set);
  if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
    perror("sched_setaffinity");
    return 1;
  }
#endif

#ifdef SCHED_POLICY
  struct sched_param param;
  memset(&param, 0, sizeof(param));
  param.sched_priority = SCHED_PRIORITY;
  if (sched_setscheduler(getpid(), SCHED_POLICY, &param) == -1) {
    perror("sched_setscheduler");
    return 1;
  }
#endif

  char *arr = (char *)malloc(ARR_SIZE);
  assert(arr != NULL);

  char cmd[10];
  while (scanf("%9s", cmd) == 1) {

    printf("Executing '%s' ...\n", cmd);
    for (int i = 0; i < strlen(cmd); ++i) {
      memset(arr, cmd[i], ARR_SIZE);
    }
    printf("Done '%s' ...\n", cmd);
  }

  free(arr);
  return 0;
}
