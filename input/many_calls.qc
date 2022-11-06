/* fun: MAIN */
LOADIM 0 0   /* sp = 0 */
LOADIM 1 0   /* bp = 0 */
LOADIM 2 10  /* a = 10 */
LOADIM 3 1   /* Constant 1 */
LOADIM 4 10  /* Return address */
LOADIM 5 12  /* Address of decrement */
STORE  4 0 0 /* Puts the return address on the stack */
ADD    0 0 3 /* Increment stack pointer */
STORE  2 0 0 /* Puts a on the stack as an argument */
ADD    0 0 3 /* Increment stack pointer */
BRCUNC 0 0 5 /* Call decrement */
OUTPUT 0 0 3 /* output the result of decrement */
HALT   0 0 0
/* fun: DECREMENT */
/* SETUP */
LOADIM 2 1 0  /* Load constant 1 */
STORE  1 0 0  /* Save r_bp on stack */
MOVE   1 0 0  /* set r_bp to r_sp */
ADD    0 0 2  /* Increment stack pointer */
/* Get argument from the stack */
LOADIM 3 1    /* Load constant 1 */
SUB    3 1 3  /* r_3 now hold the address of argument 1 */
LOAD   3 3 0  /* r_3 now hols argument 1 */
/* Do work */
LOADIM 4 1    /* Load constant 1 */
SUB    3 3 4  /* r3 = r3 - 1 */
/* CLEANUP */
MOVE   0 1 0  /* sp = bp */
LOAD   1 1 0  /* bp = mem[bp] */
LOADIM 2 2    /* Number of arguments + 1 */
SUB    0 0 2  /* sp = sp - 2 */
LOAD   2 0 0  /* reg_2 = mem[sp] (read return address) */
BRCUNC 0 0 2  /* Jump to return address */
