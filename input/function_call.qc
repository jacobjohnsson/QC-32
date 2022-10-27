/* r_0 holds return address, r1 holds stack pointer, r_2 holds return value. Put arguments at stack pointer */
/* fun: MAIN */
INPUT 0 0 2 /* read -> r_2 */
LOADIM 0 4  /* return address -> r_0 */
LOADIM 3 6 /* load address of function call (-1) */
STORE 2 1 0 /* mem[r_1] = r_2 */
BRCUNC 0 0 3 /* jump to SQUARE */
OUTPUT 0 0 2 /* output return value */
HALT 0 0 0
/* SQUARE */
LOAD 3 1 0 /* read memory[stack_pointer] */
MUL 2 3 3 /* square */
BRCUNC 0 0 0 /* return to program[return_address] */ 
