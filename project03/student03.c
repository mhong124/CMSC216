#include <stdio.h>
#include <assert.h>
#include "raisin.h"

#define NUM_INSTRUCTIONS 20

int main(void) {
  unsigned int instructions[NUM_INSTRUCTIONS]= {0xC0000000, 0x14100000,
                                                0x17C40000, 0x107E0000,
                                                0x607E0000, 0x5C000000,
                                                0x97C00000, 0x90000001,
                                                0xA0000001, 0x90008000, /* outputs: li R0 1 lw R0 32768 */
                                                0x90018000, 0x90010000, /* outputs: lw R0 32768 lw R0 00000*/
                                                0xA0010000, 0x9001FFFF, /* outputs : li R0 65536*/
                                                0x9001FFFC, 0xA1000940, /* outputs : lw R0 65532*/
                                                0x90c007d0, 0x18ca0000,
                                                0x99c00870, 0x8C400000};
  int i;

  for (i= 0; i < NUM_INSTRUCTIONS; i++)
    print_instruction(instructions[i]);

  assert(print_instruction(0x8C400000) == 0);
  assert(print_instruction(0x94410000) == 0);
  assert(print_instruction(0xC0000000) == 0);
  assert(print_instruction(0x14100000) == 0);
  assert(print_instruction(0x607E0000) == 0);
  assert(print_instruction(0x97C00000) == 0);
  assert(print_instruction(0x9001FFFF) == 0);
  assert(print_instruction(0x94400000) == 0);
  assert(print_instruction(0xA4400000) == 0);
  assert(print_instruction(0x90010001) == 0);
  
  return 0;
}
