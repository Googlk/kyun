#include "stdio.h"
#include "stdlib.h"
#define MX (z>>5^y<<2)+(y>>3^z<<4)^(sum^y)+(k[p&3^e]^z)
#define DELTA 0x9e3779b9
#define S_LOOPTIME   1    //5
#define BLOCK_SIZE   36   //PAGE_SIZE,根据你所要加密的数据包长度修改此参数(单位:字节)
unsigned char Key[] = { 0x41,0x59,0x85,0x94,0x00,0x01,0x00,0x00,0x04,0x19,0x00,0x05,0x04,0x19,0x00,0x05 };//16byte
//unsigned char Key[16] = { 0x3A,0xDA,0x75,0x21,0xDB,0xE2,0xDB,0xB3,0x11,0xB4,0x49,0x01,0xA5,0xC6,0xEA,0xD4 };
//unsigned char Mingwen[8] = { 0xAD,0xDE,0xE2,0xDB,0xB3,0xE2,0xDB,0xB3 };
unsigned char Mingwen[36] = { 0x46, 0x49, 0x53, 0x01, 0x00, 0x02, 0x00, 0x00, 0xD0, 0x18, 0x00, 0xA0, 0x71, 0x3D, 0xF2, 0x41, 0x00, 0xA2, 0x00 ,0x00 ,0x00,0x00 ,0x00 ,0xA4 ,0x00 ,0x00 ,0xA6 ,0x41 ,0x00 ,0xA6 ,0xEC ,0x51 ,0xB0 ,0x40 ,0xE3 ,0xF8 };
/*
*key  maybe 128bit =16 Bytes.
*buf  maybe BLOCK_SIZE
*/


void btea_encrypt(unsigned char* buf, unsigned char* key)
{
  unsigned char  n = BLOCK_SIZE / 4;
  unsigned long *v = (unsigned long *)buf;
  unsigned long *k = (unsigned long *)key;
  unsigned long z = v[n - 1], y = v[0], sum = 0, e;
  unsigned char p, q;
  // Coding Part 

  q = S_LOOPTIME + 52 / n;
  while (q-- > 0)
  {
    sum += DELTA;
    e = sum >> 2 & 3;
    for (p = 0; p < n - 1; p++)
      y = v[p + 1],
      z = v[p] += MX;
    y = v[0];
    z = v[n - 1] += MX;
  }
}


/*
*key  maybe 128bit =16Bytes.
*buf  maybe BLOCK_SIZE
inbuf == outbuf == buf
*/


void btea_decrpyt(unsigned char* buf, unsigned char* key)
{
  unsigned char n = BLOCK_SIZE / 4;
  unsigned long *v = (unsigned long *)buf;
  unsigned long *k = (unsigned long *)key;
  unsigned long z = v[n - 1], y = v[0], sum = 0, e;
  unsigned char  p, q;

  printf("test\n");
  //Decoding Part...
  q = S_LOOPTIME + 52 / n;
  sum = q * DELTA;
  //printf("%d\n", q);
  printf("%I32d\n", DELTA);
  //printf("%x\n", DELTA);
  printf("%I32d\n", sum);
  while (sum != 0)
  {
    e = sum >> 2 & 3;
    //printf("%I32d\n", e);
    for (p = n - 1; p > 0; p--)
      z = v[p - 1],
      y = v[p] -= MX;
    z = v[n - 1];
    y = v[0] -= MX;
    sum -= DELTA;
    // printf("sum = %I32d\n", sum);

  }
}

int main(int argc, char const *argv[])
{
  /* code */

  unsigned int Loop_i;
  //unsigned int Loop_j;
  printf("Mingwen:");
  for (Loop_i = 0; Loop_i<BLOCK_SIZE; Loop_i++)
  {
    printf("%02X ", Mingwen[Loop_i]);
  }
  printf("\n");
  printf("Key:");
  for (Loop_i = 0; Loop_i<16; Loop_i++)
  {
    printf("%X ", Key[Loop_i]);
  }
  printf("\n");


  printf("Jiami:\n");
  btea_encrypt(Mingwen, Key);
  for (Loop_i = 0; Loop_i<BLOCK_SIZE; Loop_i++)
  {
    printf("%02X ", Mingwen[Loop_i]);
  }



  printf("\nJiemi:\n");
  btea_decrpyt(Mingwen, Key);
  for (Loop_i = 0; Loop_i<BLOCK_SIZE; Loop_i++)
  {
    printf("%02X ", Mingwen[Loop_i]);
  }
  printf("\n");
  while (1);

  return 0;
}