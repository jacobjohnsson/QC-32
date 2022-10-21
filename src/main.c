#define MEMORY_SIZE 2^8

typedef unsigned int uint;

enum instruction {
  ADDITION,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION,
  HALT,
  OUTPUT,
  INPUT,
  LOAD,
  STORE,
  BRANCH_UNCONDITIONALLY,
  BRANCH_IF_ZERO,
  BRANCH_IF_NON_ZERO,
  NAND,
  OR,
  RESERVED,
  LOAD_IMMEDIATELY
}

void main (int argc, char *argv)
{
  uint memory[MEMORY_SIZE] = { 0 };
  uint registers[8] = { 0 };
  uint program_counter;

  while (1) {
      case: ADDITION:

      break;
      case: SUBTRACTION:

      break;
      case: MULTIPLICATION:

      break;
      case: DIVISION:

      break;
      case: HALT:

      break;
      case: OUTPUT:

      break;
      case: INPUT:

      break;
      case: LOAD:

      break;
      case: STORE:

      break;
      case: BRANCH_UNCONDITIONALLY:

      break;
      case: BRANCH_IF_ZERO:

      break;
      case: BRANCH_IF_NON_ZERO:

      break;
      case: NAND:

      break;
      case: OR:

      break;
      case: RESERVED:

      break;
      case: LOAD_IMMEDIATEL:

      break;
  }
}
