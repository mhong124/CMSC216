#include <stdio.h>
#include <assert.h>
#include "raisin.h"

int main(void) {
    unsigned int memory[NUM_WORDS]= {0};

    unsigned int memory1[NUM_WORDS]= {0};
    unsigned int program[15]= {0x12960000, 0x239c0000, 0x32d80000,
                                       0x43d40000, 0x5b580000, 0x7b1c0000,
                                       0x82de0000, 0x4bc00000, 0x53400000,
                                       0xa80027e8, 0x08000000, 0xa3803810,
                                       0x93c02f10, 0x9ac03910, 0x8b560000};

  /* load the program into memory starting at address 0, it has 15 total
     words, and its data segment is 0 words large */
    assert(load_program(memory1, program, 0, 15,
                      0) == 1);

    assert(disassemble(memory, 100, NUM_WORDS, 25) == 0);

    assert(disassemble(memory, 0, (NUM_WORDS + 10), 25) == 0);

    assert(disassemble(memory, 0, 10, 25) == 0);

    assert(disassemble(memory1, 13, 15, 0) == 0);

    assert(disassemble(memory1, (NUM_WORDS - 1) * 4, 1, 0) == 1);

    assert(disassemble(memory1, 12, 0, 0) == 1);

    printf("The assertions were all extremely successful!\n");
    
    return 0;
}