#ifndef _STATE_H_
#define _STATE_H_

#include <stdlib.h>
#include <stdbool.h>

#include "main.h"

#define MEMORY_SIZE 2^8
#define PROGRAM_SIZE 2^8

struct _QCState
{
  uint program[PROGRAM_SIZE];
  uint memory [MEMORY_SIZE];
  uint registers[8];
  uint pc;
  bool halted;
  bool singlestepping;
};
typedef struct _QCState QCState;

/* Create a new QCState on the heap */
QCState * QC_state_new ();

/* Frees the resources held be QCState state */
void QC_state_free (QCState *state);

#endif /* _STATE_H_ */
