
#include <stdio.h>
#include <stdint.h>
int main(int argc, char const *argv[])
{
int i = 0;
// Rxbuf={55, AA, 0E, CD, 0C, 00, 00, 00, A0, 3F, 50, 29, 5C, EF, 3F, 14, A7};
// char Rxbuf[100] = {0x55, 0xAA, 0x0E, 0xCD, 0x0C, 00, 00, 00, 0xA0, 0x3F, 50, 29, 0x5C, 0xEF, 0x3F, 14, 0xA7};
char Rxbuf[10] = {0x55, 0xAA, 0x0E, 0xCD, 0x0C, 00, 00, 00, 0xA0, 0x3F};
Rxbuf[4]++;
// printf("%x\n",Rxbuf[4] );	
// printf("%d\n", (Rxbuf[i+4]-2)/5);
uint8_t a;
a = 4;
printf("%d, %d\n", a, sizeof a);
for (int i = 0; i < 10; ++i)
{
	/* code */
	

}

	return 0;
}

