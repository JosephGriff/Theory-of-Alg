// Joseph Griffith
// Secure hash 256-bit version
//

#include <stdio.h>
#include <stdint.h>

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
  
  return (x & y) ^ (~x & z);
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
  return (x &y) ^ (x &z) ^ (y & z);
}

int main(int argc, char *argv[]){

  uint32_t x = 0x0f0f0f0f;
  uint32_t y = 0xcccccccc;
  uint32_t z = 0x55555555;

  printf("x          = %08x\n", x);
  printf("y          = %08x\n", y);
  printf("z          = %08x\n", z);

  printf("Ch(x,y,z)  = %08x\n", Ch(x,y,z));

  printf("Maj(x,y,z) = %08x\n", Maj(x,y,z));

  return 0;

}
