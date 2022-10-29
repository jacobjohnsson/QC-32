#include "state.h"

QCState *
QC_state_new () {
  QCState *state = calloc (1, sizeof (QCState));

  return state;
}

void
QC_state_free (QCState *state)
{
  free (state);
}
