  Object: QC-32 "Quick Computer"
  ------------------------------------------------------------------------------
                                                                 23 October 2022

  Physical Specifiations
  ----------------------

  The QC-32 shall consist of the following components:

    * A word shall consist of 32 bits where the "right most" bit is the most
      significant, i.e big endian.

                                      least bit
                                              |
                                              v
              .--------------------------------.
              |zyx                     ...43210|
              `--------------------------------'
              ^
              |
              most bit

    Each bit can hold the value 0 or 1. All word shall be treated as unsigned
    integers.

    * 8 distinct general purpose registes, holding one word each.

    * A contigious array of words, also known as memory. The size of this
      memory is up to the implementation to decide.

    * One special memory for holding the program instructions.

    * One display capable of printing ASCII characters.

    * One input device, capable of reading ASCII characters.


  Behavior
  --------

  The special memory holding the program shall be initiated with a set of 
  instructions. All registers shall be initiated with a value of 0. A special
  'program counter' shall start with the value of 0 and be incremented by 1 
  after each instruction is executed, unless the instruction says otherwise.

  Once the QC-32 has been initialized it shall begin execution. When executing
  the QC-32 will read the instruction stored at 'program counter' in the
  program memory. Once that instruction has been executed the 'program counter'
  is to be incremented and the execution phase begins again or the HALT
  instruction has been executed at which point the QC-32 will exit.

  Operators
  ---------

  The QC-32 supports up to 32 Operators and each operator is uniquely
  identified by its number which is stored in its 5 most bits.

               operator number
               |
               vvvv
              .--------------------------------.
              |4321                            |
              `--------------------------------'

  Standard Operators
  ------------------
  
  Each Standard Operator performs some computation involving up to three
  registers, A, B and C. Each register is described by a three bit segment of
  the word. The register C is described by the three least bits, the register B
  is described by the next three more bits, and register C is described by the 
  thee next more bits.

                                      A     C
                                      |     |
                                      vvv   vvv
              .--------------------------------.
              |                       aaabbbccc|
              `--------------------------------'
                                         ^^^
                                         |
                                         B

  A description of each standard operator follows.

  Operator #0. Addition. ADD

                The register A receives the value in register B plus the value
                in register C.

           #1. Subtraction. SUB

                The register A receives the value in register B minus the value
                in register C.

           #2. Multiplication. MUL

                The register A receives the value in register B multiplied by 
                the value in register C.

           #3. Division. DIV

                The register A receives the value in register B divided by the
                value in register C.

           #4. Halt. HALT

                The QC-32 stops computation.

           #5. Output. OUTPUT

                The value in register C is diplayed on the console immediately.
                Accepts positive integers.

           #6. Input. INPUT

                The QC-32 waits for input on the console. When input arrives
                register C is loaded with the input. Accepts positive values.

           #7. Load. LOAD

                The register A receives the value at the offset indicated by 
                the value at register B.

           #8. Store. STORE

                Writes the value stored in register A to the memory location
                identified by the value at register B.

           #9. Branch Unconditionally. BRCUNC

                Sets the program counter to the value in register C.

           #10. Branch If Zero. BRCZER

                Sets the program counter to the value in A if the value in 
                register B is zero. Otherwise it does nothing.

           #11. Branch non Zero. BRCNZE

                Sets the program counter to the value in A if the value in 
                register B is not zero. Otherwise it does nothing.

           #12. NAND. NAND

                The register A receives the value at register B NAND:ed with 
                the register C.

           #13. OR. OR

                The register A receives the value at register B OR:ed with 
                the register C.

           #14. Move. MOVE

                The register A receives the value at register B.


  Special Operators
  -----------------

  Special operators do not conform to the previously mentioned structure,
  instead they are defined below. The operator number is the same as for
  standard operators, the next 3 bits identifies a register and the other 25 
  bits represents a whole value.

               operator number
               |      value
               |      |
               vvvv   vvvvvvvvvvvvvvvvvvvvvvvvv
              .--------------------------------.
              |ooooaaa.........................|
              `--------------------------------'
                   ^^^
                   |
                   register

           #15. Load Immediately. LOADIM

                Register A receives the value supplied by the instruction.


  Programmers Guide
  -----------------
  
  The following section describes how to write function calls on the QC-32. This
  computer does not have a conventional stack yet it can be emulated by 
  following the steps below.

  This strategy assumes that the stack pointer is always kept in r_0 and the
  base pointer in r_1.

  Note that the caller can no longer make any assumptions about the other 
  registers since the callee is free to do what ever it wants with them, 
  therefore if the caller wants to use the registers after the function call it 
  must save them in memory first. The stack will look like the following 
  ahead of the call:

                     .----------------.    '
                     |                |    '
                     .----------------.    '
                     |                |    '
                     .----------------.    ' frame belonging to the callee
  stack pointer ->   |                |    '
                     .----------------.    '
                     | argument 2     |    '
                     .----------------.    '
                     | argument 1     |    '
                     .----------------.    '
                     | return address |    /
                     .----------------.    
                     | saved register |    \
                     .----------------.    ' frame belonging to the caller
                     | saved register |    '
                     .----------------.    '

  The callee must perform setup and cleanup appropriately. Setup is performed
  by saving the value of the current base pointer so that when control is 
  returned to the caller, it will have it's original base pointer. The second
  thing that must be done during setup is to set the current stack frames base
  pointer correctly. It should be set to the same as the stack pointer.
  Therefore setup is performed as follows:

    /* Save the value of bp at the memory location pointed to by sp */ 
    STORE bp sp
    /* Set bp to sp */
    MOVE bp sp

  After these operation the stack would look as below.

                     .----------------.    '
                     |                |    '
                     .----------------.    '
                     |                |    '
                     .----------------.    ' frame belonging to the callee
        sp & bp ->   | caller's bp    |    '
                     .----------------.    '
                     | argument 2     |    '
                     .----------------.    '
                     | argument 1     |    '
                     .----------------.    '
                     | return address |    /
                     .----------------.    
                     | saved register |    \
                     .----------------.    ' frame belonging to the caller
                     | saved register |    '
                     .----------------.    '

  At this point the function can execute. If the function needs to use space on
  the stack it can do so by incrementing the stack pointer by the appropiate
  amount. A function that allocated space for 2 local integers can do so as
  shown below:

  LOADIM 2 2 /* Load 2 into r_2 */
  ADD sp sp 2 /* increment sp by 2 */

  Which would move the stack pointer as shown below.

                     .----------------.    '
             sp ->   |                |    '
                     .----------------.    '
                     |                |    '
                     .----------------.    ' frame belonging to the callee
             bp ->   | caller's bp    |    '
                     .----------------.    '
                     | argument 2     |    '
                     .----------------.    '
                     | argument 1     |    '
                     .----------------.    '
                     | return address |    /
                     .----------------.    
                     | saved register |    \
                     .----------------.    ' frame belonging to the caller
                     | saved register |    '
                     .----------------.    '

  Clean up is performed by saving the return address in a register. It frees
  the stack by subtracting the space used from the stack pointer. It also
  repopulates the callers base pointer, located at the current base pointer.
  This can be achieved by the following operations:

    MOVE sp bp /* sp = bp */
    LOAD bp bp /* Restore bp */
    LOADIM 2 n_args /* store the number of args to this function somewhere */
    SUB 2 2 sp /* r_2 now holds the return address */
    BRCUNC 0 0 2 /* set pc to return address */

  The caller should now be able to continue execution by restoring it's
  registers, if necessary.
