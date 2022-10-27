#include "main.h"

#define DEBUG 0

void debug_msg (char *msg);

void print_standard_instruction_bin (uint instruction);

void print_bin (uint value);

void print_bin_memory (uint * memory, uint min, uint max);

void print_registers (uint * memory, uint length, uint pc);
