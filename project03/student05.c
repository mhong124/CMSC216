#include <stdio.h>
#include "raisin.h"
#include <assert.h>

int main(void) {

  unsigned int memory[NUM_WORDS]= {0};
  unsigned int program1[15]= {0x00000000, 0x00000000, 0x00000000,
                              0x00000000, 0x00000000, 0x00000000,
                              0x00000000, 0x00000000, 0x00000000,
                              0x00000000, 0x00000000, 0x00000000,
                              0x00000000, 0x00000000, 0x00000000};
  unsigned int program2[15]= {0x00000000, 0x00000000, 0x00000000,
                              0x00000000, 0x00000000, 0x00000000,
                              0x00000000, 0x00000000, 0x00000000,
                              0x00000000, 0x00000000, 0x00000000,
                              0xFFFFFFFF, 0x00000000, 0x00000000};

  print_instruction(0x00000000); /*checks halt*/
  print_instruction(0x68220000); /*checks r0 r17*/
  print_instruction(0x6822AAAA); /*random memory*/
  print_instruction(0xA8000000); /*checks branch, memory 0*/
  
  assert(print_instruction(0xA8000001) == 0); /*invalid memory*/
  assert(print_instruction(0x8C620000) == 0); /*move and r17*/
  assert(print_instruction(0x94400000) == 0); /*lw and r17*/
  assert(print_instruction(0xA4400000) == 0); /*li and r17*/
  assert(print_instruction(0x8C000000) == 0); /*move and r16*/
  assert(print_instruction(0x94000000) == 0); /*lw and r16*/
  assert(print_instruction(0xA4000000) == 0); /*li and r16*/

  print_instruction(0xA0000401); /*li and memory not divisble by 4*/

  assert(load_program(memory, program1, 0, 15, 15) == 0); /*no instruction*/
  assert(load_program(memory, program1, 64*1024, 15, 0) == 0); /*goes beyond 
                                                                       memory*/
  assert(load_program(memory, program1, 0, 0, 0) == 1); /*prg size 0*/
  assert(load_program(memory, program1, 5, 15, 0) == 0); /*invalid start*/
  assert(load_program(memory, program1, 0, 16*1024+1, 0) == 0); /*pgmsize too 
                                                                        large*/
  assert(load_program(memory, program2, 0, 15, 0) == 1); /*invalid instr*/

  assert(disassemble(memory, 0, 15, 0) == 0); /*invalid instr*/

  assert(load_program(memory, program1, 0, 15, 0) == 1);
  disassemble(memory, 0, 15, 0); /*prints all 15*/
  disassemble(memory, 0, 15, 5); /*prints 5 data*/
  
  assert(disassemble(memory, 0, 15, 15) == 0); /*all data*/
  assert(disassemble(memory, 16*1024-10, 15, 0) == 0); /*past memory*/
  
  printf("success!");

  return 0;
}