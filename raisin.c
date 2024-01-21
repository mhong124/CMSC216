#include <stdio.h>
#include "raisin.h"

/*
* I pledge on my honor that I have not given or received any
* unauthorized assistance on this examination (or assignment).
* Name : Mabel Hong TerpConnect Login : mhong124 UID: 118927671
* discussion section : 0106
*/

/* 
* This function reads it's parameter as a MAD Raisin instruction
* and prints the instruction's opcode, register, and/or
* memory address operand or immediate operand if they apply to
* the specified opcode on an output line and outputs 1. If the 
* parameter represents an invalid MAD Raisin instruction, nothing 
* is printed and the function returns 0. 
*/
unsigned short print_instruction(unsigned int instruction) {
    int valid = 1; /* indicates whether instruction is valid. */

    /* shifts instruction right 27 bits to get left most 5 bits. */
    int opcode = (instruction >> 27);

    /* shifts instruction right 22 bits and ands with 31 in binary
        which isolates the 5 bits that represent register 1.*/
    int r1 = (instruction >> 22) & 31;

    /* indicates if r1 is a valid register if its less than 18. */
    int r1_valid = r1 < 18;

    /* indicates if r1 is non special register number.*/
    int r1_non_special = r1 != 16 && r1 != 17;

    /* shifts instruction right 17 bits and ands with 31 in binary
        which isolates the 5 bits that represent register 2.*/
    int r2 = (instruction >> 17) & 31;

    /* indicates if r2 is a valid register if r2 is less than 18. */
    int r2_valid = r2 < 18;

    /* stores the rightmost 17 bits in mem. */
    int mem = instruction & ((1 << 17) - 1);

    /* 
    * if opcode matches any enum opcode_value and its components
    * are valid, it is printed. if the instruction uses contents 
    * in r1 or r2, they are checked for validity before printing 
    * instruction. if the instruction modifies first register 
    * operand, r1 is checked for being non special before printing. 
    * if the intruction uses the memory address/immediate
    * operand field, then mem is checked to determine if it is divisible
    * by 4 before printing memory in 5 places with leading zeros. If
    * opcode is LI, mem is a literal that is printed without leading
    * zeros and is not checked for divisibility by 4.
    */
    if (opcode == HALT)
        printf("halt\n");
    else if (opcode == SYSCALL)
        printf("syscall\n");
    /* checks if registers are valid and because it is a modifying
        operator, r1 is checked for being non special. */
    else if (opcode == ADD && r1_valid && r2_valid && r1_non_special) 
    {
        printf("add");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == SUB && r1_valid && r2_valid && r1_non_special) 
    {
        printf("sub");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == MUL && r1_valid && r2_valid && r1_non_special) 
    {
        printf("mul");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == QUOT && r1_valid && r2_valid && r1_non_special) 
    {
        printf("quot");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == MOD && r1_valid && r2_valid && r1_non_special) 
    {
        printf("mod");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == AND && r1_valid && r2_valid && r1_non_special) 
    {
        printf("and");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == OR && r1_valid && r2_valid && r1_non_special) 
    {
        printf("or");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    /* r1 is checked to be valid and non special. */
    else if (opcode == NEG && r1_valid && r1_non_special) 
    {
        printf("neg");
        printf(" R%d\n", r1);
    }
    else if (opcode == NOT && r1_valid && r1_non_special) 
    {
        printf("not");
        printf(" R%d\n", r1);
    }
    else if (opcode == EQL && r1_valid && r2_valid) 
    {
        printf("eql");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == NEQ && r1_valid && r2_valid)
    {
        printf("neq");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == LT && r1_valid && r2_valid) 
    {
        printf("lt");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == LE && r1_valid && r2_valid) 
    {
        printf("le");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == GT && r1_valid && r2_valid) 
    {
        printf("gt");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == GE && r1_valid && r2_valid) 
    {
        printf("ge");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    else if (opcode == MOVE && r1_valid && r2_valid && r1_non_special) 
    {
        printf("move");
        printf(" R%d", r1);
        printf(" R%d\n", r2);
    }
    /* additionally checks if the rightmost 16 bits
        representing mem address is divisible by 4. */
    else if (opcode == LW && r1_valid && r1_non_special 
             && (mem &= ((1 << 16) - 1)) % 4 == 0) 
    {
        printf("lw");
        printf(" R%d", r1);
        /* printed in 5 places with leading zeros. */
        printf(" %05d\n", mem);
    }
    /* additionally checks if the rightmost 16 bits
        representing mem address is divisible by 4. */
    else if (opcode == SW && r1_valid 
             && (mem &= ((1 << 16) - 1)) % 4 == 0) 
    {
        printf("sw");
        printf(" R%d", r1);
        printf(" %05d\n", mem);
    }
    /* LI memory operand is a literal so it is printed 
        as rightmost 17 bits. */
    else if (opcode == LI && r1_valid && r1_non_special) 
    {
        printf("li");
        printf(" R%d", r1);
        /* printed without 5 places or leading zeros. */
        printf(" %d\n", mem);
    }
    /* additionally checks if the rightmost 16 bits
        representing mem address is divisible by 4. */
    else if (opcode == BRANCH && (mem &= ((1 << 16) - 1)) % 4 == 0) 
    {
        printf("branch");
        printf(" %05d\n", mem);
    }
    /* if opcode does not equal any enum opcode_name
        instruction is not valid and nothing is printed. */
    else
        valid = 0;
    
    return valid;
}

/*
* This function represents the operating system in it's act
* of loading a machine language program into MAD Raisin
* memory. The parameter array program represents the 
* machine language program to be loaded into array memory 
* beginning as address start_addr. Parameter pgm_size 
* represents program size and data_segment_size represents
* the size of the data segment at the end of memory. If
* the parameters are valid, the functions will load
* the program into memory and return 1, otherwise it modifies
* nothing and returns 0. 
*/
int load_program(unsigned int memory[], const unsigned int program[],
                unsigned int start_addr, unsigned short pgm_size,
                unsigned short data_segment_size) {
    /* start_word represents where the program 
        will be loaded into memory starting at that word address. */
    int start_word = start_addr / 4;
    int i;
    int j;

    /*
    * program is loaded into memory starting at start_word if 
    * start_addr is divisible by 4 and a valid start address, 
    * the start word address is not more than NUM_WORDS,
    * pgm_size is not more than NUM_WORDS, starting at 
    * start_word and loading pgm_size would not exceed NUM_WORDS, 
    * and data_segment_size < pgm_size so there is atleast one
    * instruction unless pgm_size is zero.
    */
    if (start_addr % 4 == 0 && start_word < NUM_WORDS 
        && pgm_size <= NUM_WORDS 
        && (start_word + pgm_size) <= NUM_WORDS
        && (pgm_size == 0 || (data_segment_size < pgm_size))) 
    {
        /* 
        * iterates through memory starting at start_word
        * and program starting at 0 until memory index reaches 
        * start_word + pgm_size. 
        */
        for (i = start_word, j = 0; i < start_word + 
            pgm_size; i++, j++) 
        {
            /*
            * Setting memory element of index i to program 
            * element of index j loads program elements into
            * memory starting at start_word.
            */
            memory[i] = program[j];
        }
        return 1;
    }
    else
        /* if any condition is false and a parameter is invalid
            nothing is modified and returns 0.*/
        return 0;
}

/*
* The function acts as a disassembler which converts machine 
* language to assembly language for a MAD Raisin program
* stored in memory. Disassembly begins at start_addr. 
* Parameter pgm_size represents program size and data_segment_size 
* represents the size of the data segment at the end of memory.
* Each word in memory represents an instruction, which will be 
* printed as opcode, register, and and/or memory address operand
* or immediate operand as specified by the instruction. The 
* function then prints the remaining data elements in hexadecimal.
* If parameters are valid, instruction and data are printed and
* function returns 1, otherwise nothing is outputed and 0 is 
* returned. 
*/
unsigned short disassemble(const unsigned int memory[],
                           unsigned int start_addr, unsigned int pgm_size,
                           unsigned int data_segment_size) {
    /* indicates start word address. */
    int start_word = start_addr / 4;
    /* indicates if all instructions are valid. */
    int valid = 1;
    int i;
    /* stores each instruction in memory. */
    unsigned int instruction;
    /* stores opcode, register 1 and 2 variables, mem, and 
        variables to indicate validity of registers. */
    int opcode, r1, r1_valid, r1_non_special, r2, r2_valid, mem;

    /* 
    * checks if size of program is not more then NUM_WORDS, if loading
    * pgm_size starting at start_word or start_word exceeds NUM_WORDS, 
    * start_addr is divisible by 4 and valid, and 
    * data_segment_size is less than pgm_size so there is atleast
    * one instruction unless pgm_size is zero.
    */
    if (start_addr % 4 == 0 && start_word < NUM_WORDS 
        && pgm_size <= NUM_WORDS 
        && (start_word + pgm_size) <= NUM_WORDS 
        && (pgm_size == 0 || (data_segment_size < pgm_size))) 
    {
            /* while starts at start_word. */
            i = start_word;

            /* iterates through memory starting at start_word for all 
                instructions stored in memory and stops if any is invalid. */
            while (valid && i < start_word + 
                    (pgm_size - data_segment_size)) 
            {
                instruction = memory[i];
                /* sets opcode to leftmost 5 bits. */
                opcode = (instruction >> 27);
                /* sets r1 to isolated 5 bits before opcode. */
                r1 = (instruction >> 22) & 31;
                /* r1_valid is 1 if r1 is valid and less than 18. */
                r1_valid = r1 < 18;
                /* r1_non_special is true or 1 if r1 isnt 16 or 17. */
                r1_non_special = r1 != 16 && r1 != 17;
                /* sets r2 to isolated 5 bits after memory operand. */
                r2 = (instruction >> 17) & 31;
                /* r2_valid is 1 if r2 is less than 18 and valid. */
                r2_valid = r2 < 18;
                /* mem is set to rightmost 16 bits to check memory address. */
                mem = instruction & ((1 << 16) - 1);

                /* if opcode is 0 or 1, instruction is valid. */
                if (opcode == 0 || opcode == 1)
                {
                    valid = 1;
                }
                /* if opcode is between 2 and 8 inclusive, instruction
                    is valid if r1 r2 are valid and r1 is nonspecial. */
                else if (opcode >= 2 && opcode <= 8)
                {
                    valid = r1_valid && r2_valid && r1_non_special;
                }
                /* if opcode is 9 or 10, instruction is valid if
                    r1 is valid.*/
                else if (opcode == 9 || opcode == 10) 
                {
                    valid = r1_valid && r1_non_special;
                }
                /* if opcode is between 11 and 16 inclusive instruction
                    is valid if r1 and r2 are valid. */
                else if (opcode >= 11 && opcode <= 16) 
                {
                    valid = r1_valid && r2_valid;
                }
                /* opcode 17 checks r1 valid and nonspecial and r2 valid. */
                else if (opcode == 17)
                {
                    valid = r1_valid && r2_valid && r1_non_special;
                }
                /* opcode 18 checks memory address divisibility by 4 and
                    r1 is valid and non special. */
                else if (opcode == 18) 
                {
                    valid = r1_valid && r1_non_special && mem % 4 == 0;
                }
                /* opcode 19 checks r1 is valid and mem is divisible by 4. */
                else if (opcode == 19)
                {
                    valid = r1_valid && mem % 4 == 0;
                }
                /* opcode 20 checks r1 is valid and non special. */
                else if (opcode == 20) 
                {
                    valid = r1_valid && r1_non_special;
                }
                /* if opcode is 21 instruction is valid if mem is 
                    divisible by 4. */
                else if (opcode == 21) 
                {
                    valid = mem % 4 == 0;
                }
                /* if opcode is not found, it is not valid. */
                else 
                    valid = 0;

                i++;
            }

            /* if all instructions were valid. */
            if (valid) 
            {
                /*
                * iterates through memory starting at start_word until
                * start_word + pgm_size indicating all elements
                * in the program were visited.
                */
                for (i = start_word; i < start_word + pgm_size; i++) 
                {
                    /* checks if index is within word range for 
                        instructions. */
                    if (i < start_word + (pgm_size - data_segment_size)) 
                    {
                        /* prints instruction for index i. */
                        print_instruction(memory[i]);
                    }
                    else 
                    {
                        /* prints memory at index i as hexidecimal and
                            occupying 8 places with leading zeros.*/
                        printf("%08x\n", memory[i]);
                    }
                }
            }
    }
    /* if any parameter is invalid, valid is set to 0. */
    else
        valid = 0;

    return valid;
}