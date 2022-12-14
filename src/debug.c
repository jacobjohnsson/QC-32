#include <stdio.h>

#include "debug.h"

void
debug_msg (char *msg)
{
#if DEBUG
  printf ("%s", msg);
#endif
}

void 
print_standard_instruction_bin (uint instruction)
{
#if DEBUG
  for (uint i = 1 << 31; i > 1 << 27; i = i >> 1)
    (instruction & i) ? printf("1") : printf("0");
  printf("|");
  for (uint i = 1 << 27; i > 1 << 8; i = i >> 1)
    (instruction & i) ? printf("1") : printf("0");
  printf("|");
  for (uint i = 1 << 8; i > 1 << 5; i = i >> 1)
    (instruction & i) ? printf("1") : printf("0");
  printf("|");
  for (uint i = 1 << 5; i > 1 << 2; i = i >> 1)
    (instruction & i) ? printf("1") : printf("0");
  printf("|");
  for (uint i = 1 << 2; i > 0; i = i >> 1)
    (instruction & i) ? printf("1") : printf("0");
#endif
}

void
print_bin (uint value)
{
#if DEBUG
  for (uint i = 1 << 31; i > 0; i = i >> 1)
    (value & i) ? printf("1") : printf("0");
#endif
}

void
print_bin_memory (uint * memory, uint min, uint max)
{
#if DEBUG
  printf ("Address\t\tValue (Hex) \tValue (Binary)\n");
  for (uint i = max; i >= min; i -= 1) {
    printf ("[%#5x] ", i);
    printf ("\t%#x\t\t", memory[i]);
    print_bin (memory[i]);
    printf ("\n");

    if (i == 0) {
      break;
    }
  }
#endif
}

void
print_state (QCState *state)
{
#if DEBUG
  printf ("pc=%d, ", state->pc);
  for (uint i = 0; i < 8; i += 1)
    printf("r%u=%x, ", i, state->registers[i]);
  printf("\n");
#endif
}
