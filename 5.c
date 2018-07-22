

#include <stdio.h>
int main(int argc, char const *argv[])
{
	unsigned char send[10];
	float hcho = 0.01;
  send[0] = 0x55;
  send[1] = 0xAA;
  send[2] = 0x07;
  send[3] = 0xDC;
  send[4] = *((unsigned char *)&hcho +3);
  send[5] = *((unsigned char *)&hcho +2);
  send[6] = *((unsigned char *)&hcho +1);
  send[7] = *((unsigned char *)&hcho );
printf("%x\n", *(unsigned char *)&hcho);
printf("%x\n",send+0);
for (int i = 0; i < 10; ++i)
{
	/* code */
	// printf("%x\n", send[i]);
}
	return 0;
}

