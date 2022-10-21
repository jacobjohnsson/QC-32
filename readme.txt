  Object: QC-32 "Quick Computer"
  ------------------------------------------------------------------------------
                                                                     7 June 1954

  Physical Specifiations.
  -----------------------

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


  Behavior.
  ---------

  The special memory holding the program shall be initiated with a set of 
  instructions. All registers shall be initiated with a value of 0. A special
  'program counter' shall start with the value of 0 and be incremented by 1 
  after each instruction is executed, unless the instruction says otherwise.

  Once the QC-32 has been initialized it shall begin execution. When executing
  the QC-32 will read the instruction stored at 'program counter' in the
  program memory. Once that instruction has been executed the 'program counter'
  is to be incremented and the execution phase begins again or the HALT
  instruction has been executed at which point the QC-32 will exit.

  Operators.
  -------------

  The QC-32 supports up to 32 Operators and each operator is uniquely
  identified by its number which is stored in its 5 most bits.

               operator number
               |
               vvvv
              .--------------------------------.
              |4321                            |
              `--------------------------------'

  Standard Operators.
  -------------------
  
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

  Operator #0. Addition.

                The register A receives the value in registers B plus the value
                in register C.

           #1. Subtraction.

                The register A receives the value in registers B minus the value
                in register C.

           #2. Multiplication.

                The register A receives the value in registers B multiplied by 
                the value in register C.

           #3. Division.

                The register A receives the value in registers B divided by the
                value in register C.

           #4. Halt.

                The QC-32 outputs the value in register 0 and stops computation.

           #5. Output.

                The value in register C is diplayed on the console immediately.
                Only accepts values between 0 and 255.

           #6. Input.

                The QC-32 waits for input on the console. When input arrives
                register C is loaded with the input, also between 0 and 255.

           #7. Load.

                The register A receives the value at the offset indicated by 
                the value at register B.

           #8. Store.

                Writes the value stored in register A to the memory location
                identified by the value at register B.

           #9. Branch Unconditionally.

                Sets the program counter to the value in register C.

           #10. Branch If Zero

                Sets the program counter to the value in A if the value in 
                register B is zero. Otherwise it does nothing.

           #11. Branch non Zero

                Sets the program counter to the value in A if the value in 
                register B is not zero. Otherwise it does nothing.

           #12. NAND

                The registers A receives the value at register B NAND:ed with 
                the registers C.

           #13. OR

                The registers A receives the value at register B OR:ed with 
                the registers C.

           #14.




  Special Operators
  --------------------

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

           #15. Load Immediately.

                Register A receives the value supplied by the instruction.

