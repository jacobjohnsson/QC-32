#include "state.h"

static uint *
my_calloc (int n, int size)
{
  uint *arr = malloc (n * size);

  for (int i = 0; i < n; i++) {
    arr[i] = 0;
  }

  return arr;
}

QCState *
QC_state_new () {
  QCState *state = calloc (1, sizeof (QCState));

  state->program = my_calloc (PROGRAM_SIZE, sizeof (uint));
  state->memory = my_calloc (MEMORY_SIZE, sizeof (uint));
  state->registers = my_calloc (8, sizeof (uint));

  state->memory[0] = 0xff;

  state->pc = 0;
  state->halted = false;
  state->singlestepping = false;

  return state;
}

void
QC_state_free (QCState *state)
{
  free (state->program);
  free (state->memory);
  free (state->registers);

  free (state);
}
