#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

#define MEMORY_SIZE 2^8
#define PROGRAM_SIZE 2^8

#define INSTRUCTION(I, a, b, c) I << OP_CODE_SHIFT | a << REG_A_SHIFT | b << REG_B_SHIFT | c << REG_C_SHIFT

#define OP_CODE_SHIFT 28
#define REG_A_SHIFT 6
#define REG_B_SHIFT 3
#define REG_C_SHIFT 0

#define OP_CODE_MASK 0b00001111 << OP_CODE_SHIFT
#define REG_A_MASK 0b00000111 << REG_A_SHIFT
#define REG_B_MASK 0b00000111 << REG_B_SHIFT
#define REG_C_MASK 0b00000111 << REG_C_SHIFT

#define OP_CODE(i) (i & OP_CODE_MASK) >> OP_CODE_SHIFT
#define REG_A(i) (i & REG_A_MASK) >> REG_A_SHIFT
#define REG_B(i) (i & REG_B_MASK) >> REG_B_SHIFT
#define REG_C(i) (i & REG_C_MASK) >> REG_C_SHIFT

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
  /* TODO: Implement MOVE */
  RESERVED,
  LOAD_IMMEDIATELY
};

static void
fatal_error (const char *msg)
{
  printf ("%s", msg);
  exit(1);
}

static void
consume_line (FILE *file)
{
  char c;
  char new_line = '\n';
  int i = 0;

  while (fscanf (file, "%c", &c) == 1 && c != new_line) {
    i++;
  }
}

static bool
assemble (char * path, uint * program)
{
  char opcode_str[7] = { 0  };
  uint r_a;
  uint r_b;
  uint r_c;
  uint i = 0;

  FILE *file = fopen (path, "r");
  if (file == NULL) {
    printf ("No such file: %s", path);
    return false;
  }

  while (fscanf (file, "%s", opcode_str) == 1) {
  
    if (strcmp (opcode_str, "ADD") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (ADDITION, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "SUB") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (SUBTRACTION, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "MUL") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (MULTIPLICATION, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "DIV") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (DIVISION, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "HALT") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (HALT, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "OUTPUT") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (OUTPUT, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "INPUT") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (INPUT, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "LOAD") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (LOAD, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "STORE") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (STORE, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "BRCUNC") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (BRANCH_UNCONDITIONALLY, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "BRCZER") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (BRANCH_IF_ZERO, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "BRCNZE") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (BRANCH_IF_NON_ZERO, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "NAND") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (NAND, r_a, r_b, r_c);
    } else if (strcmp (opcode_str, "OR") == 0) {
      fscanf (file, "%u %u %u", &r_a, &r_b, &r_c);
      program[i] = INSTRUCTION (OR, r_a, r_b, r_c);
      /* TODO: Implement MOVE */
    } else if (strcmp (opcode_str, "LOADIM") == 0) {
      uint value;
      fscanf (file, "%u %u", &r_a, &value);

      program[i] = (LOAD_IMMEDIATELY << OP_CODE_SHIFT) | (r_a << 25) | value;
      print_bin (program[i]);
    
    } else if (strcmp (opcode_str, "/* ")) {
      consume_line (file);
      i--;
    } else {
      printf ("Unrecognized instruction operator: %s\n", opcode_str);
    }
    i++;
  }
}

void
read_standard_instruction_registers (uint instruction, uint * a, uint * b, uint * c)
{
  *a = REG_A(instruction);
  *b = REG_B(instruction);
  *c = REG_C(instruction);
}

void
single_step (uint program[], uint memory[], uint registers[], uint pc, uint instruction)
{
  char input;
  bool halt = false;
  print_standard_instruction_bin (instruction);
  debug_msg ("\n");
  printf ("\\ ");
  scanf ("%c", &input);
  while (!halt) {
    switch (input) {
      case 'm': 
        uint min;
        uint max;
        uint i = 0;

        scanf ("%u %u", &min, &max);
        print_bin_memory (memory, min, max);
        break;
      case 'r':
        print_registers (registers, 8, pc);
        break;
      case 'q':
        exit(0);
        break;
      case 'n':
        halt = true;
        break;
    }
    scanf ("%c", &input);
  }
}

void main (int argc, char *argv[])
{
  uint program[PROGRAM_SIZE] = { 0 };
  uint memory[MEMORY_SIZE] = { 0 };
  uint registers[8] = { 0 };
  uint program_counter;
  uint reg_a;
  uint reg_b;
  uint reg_c;
  bool halted = false;
  bool singlestepping = false;

  if (argc == 2) {
    debug_msg ("Entering single stepping mode.");
    singlestepping = (strcmp((const char *) argv[1], "d") == 0);
  }

  assemble ("input/function_call.qc", program);

  while (!halted) {
    uint instruction = program[program_counter];

    if (singlestepping) {
      single_step (program, memory, registers, program_counter, instruction);
    }

    switch (OP_CODE(instruction)) {
      case ADDITION:
        debug_msg ("ADDITION");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        registers[reg_a] = registers[reg_b] + registers[reg_c];
        break;
      case SUBTRACTION:
        debug_msg ("SUBTRACTION\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        registers[reg_a] = registers[reg_b] - registers[reg_c];
        break;
      case MULTIPLICATION:
        debug_msg ("MULTIPLICATION\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        registers[reg_a] = registers[reg_b] * registers[reg_c];
        break;
      case DIVISION:
        debug_msg ("DIVISION\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        registers[reg_a] = registers[reg_b] / registers[reg_c];
        break;
      case HALT:
        debug_msg ("HALT\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        halted = true;
        printf ("%u\n", registers[0]);
        break;
      case OUTPUT:
        debug_msg ("OUTPUT\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        printf("%u\n", registers[reg_c]);
        break;
      case INPUT:
        debug_msg ("INPUT\n");
        uint input;

        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        scanf ("%u", &input);
        registers[reg_c] = (uint) input;
        break;
      case LOAD:
        debug_msg ("LOAD\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        registers[reg_a] = memory[registers[reg_b]];
        break;
      case STORE:
        debug_msg ("STORE\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        memory[registers[reg_b]] = registers[reg_a];
        break;
      case BRANCH_UNCONDITIONALLY:
        debug_msg ("BRANCH_UNCONDITIONALLY\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        program_counter = registers[reg_c];
        break;
      case BRANCH_IF_ZERO:
        debug_msg ("BRANCH_IF_ZERO\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        program_counter = (registers[reg_b] == 0) ? registers[reg_a] : program_counter;
        break;
      case BRANCH_IF_NON_ZERO:
        debug_msg ("BRANCH_IF_NON_ZERO\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        program_counter = (registers[reg_b] != 0) ? registers[reg_a] : program_counter;
        break;
      case NAND:
        debug_msg ("NAND\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        registers[reg_a] = ~(registers[reg_b] & registers[reg_c]);
        break;
      case OR:
        debug_msg ("OR\n");
        read_standard_instruction_registers (instruction, &reg_a, &reg_b,
            &reg_c);
        registers[reg_a] = registers[reg_b] | registers[reg_c];
        break;
      case RESERVED:
        /* TODO: Implement MOVE */
        debug_msg ("RESERVED\n");
        fatal_error ("RESERVED NOT IMPLEMENTED!");
        break;
      case LOAD_IMMEDIATELY:
        debug_msg ("LOAD_IMMEDIATELY\n");
        reg_a = (instruction & 0b00000111 << 25) >> 25;
        uint value = instruction & ((1 << 25) - 1);
        registers[reg_a] = value;
        break;
      default:
        fatal_error ("NO VALID INSTRUCTION FOUND!");
    }
    program_counter++;
  }
  printf ("Exiting successfully.");
}
