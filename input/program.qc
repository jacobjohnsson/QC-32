/* Program takes a char as input and loops all chars from 'a' up to that char */

LOADIM 0 4    /* Return Address*/ 
LOADIM 1 5    /* Function Address */
LOADIM 2 64   /* Arg 1 */
INPUT  0 0 3  /* Arg 2 */

BRCUNC 0 0 1  /* Make the call */

HALT   0 0 0

LOADIM 4 1    /* Load constant 1 into r_4 */

ADD    2 2 4  /* Increment r_2 by one */

OUTPUT 0 0 2 

SUB    5 3 2  /* max - min */

BRCNZE 1 5 0  /* if min != max recurse */
BRCUNC 0 0 0  /* goto return address */
