#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "debug.h"

static struct timespec t0;

void
start_timer () {
  clock_gettime (CLOCK_MONOTONIC, &t0);
}

void
sleep_until_micro (long us)
{
  struct timespec target_time = {0};
  struct timespec current_time = {0};
  struct timespec sleep_time = {0};
  char *msg = malloc (32 * sizeof (char));

  target_time.tv_sec = t0.tv_sec;
  target_time.tv_nsec = t0.tv_nsec + (us * 1000);
  clock_gettime (CLOCK_MONOTONIC, &current_time);
  sleep_time.tv_nsec = target_time.tv_nsec - current_time.tv_nsec;

  sprintf (msg, "sleeping %ld microseconds", sleep_time.tv_nsec / 1000);
  debug_msg (msg);
  nanosleep (&sleep_time, NULL);
  clock_gettime (CLOCK_MONOTONIC, &t0);
}
