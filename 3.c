#include <stdio.h>
 
int check()
{
	union UN
	{
		char c;
		int i;
	}un;
	un.i = 1;
	return un.c;
}
 
int main(void){  
    unsigned int i = 0x12345678;
        
    unsigned char *p = (unsigned char *)&i;
    *p = 0x00;
    printf("%4x\n", *p);
    unsigned short *p1 = (unsigned short *)(p+1);
    *p1 = 0x0000;
    printf("%4x\n", *p1);

    return 0;
}