#include <stdio.h>
#include <assert.h>
#include "raisin.h"

int main(void) {
    unsigned int memory[NUM_WORDS]= {0};
    unsigned int program[NUM_WORDS]= {0};
    unsigned int program1[100]= {0};

    assert(load_program(memory, program, 12, NUM_WORDS,
                      10) == 0);

    assert(load_program(memory, program, 0, NUM_WORDS,
                      10) == 1);

    assert(load_program(memory, program1, 12, 100,
                      125) == 0);

    assert(load_program(memory, program1, 13, 100,
                      20) == 0);

    assert(load_program(memory, program, 13, NUM_WORDS,
                      10) == 0);
    
    assert(load_program(memory, program, NUM_WORDS * 5, NUM_WORDS,
                      10) == 0);

    assert(load_program(memory, program, (NUM_WORDS - 1) * 4, 1,
                      0) == 1);

    assert(load_program(memory, program, 12, 0,
                      0) == 1);

    printf("The assertions were all extremely successful!\n");

    return 0;
}
