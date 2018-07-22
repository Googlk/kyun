#include <stdio.h>
void main()
{
 // const char *p = "123";
 char const* p = "123";
 printf("%s\n",p);
 printf("%c\n",p[1] );
 // p[1] = '4';
 p = "456";
 printf("%s\n",p);
 printf("%c\n\n",*(p+1) );


  char *const pp = "123";
 printf("%s\n", pp);
  printf("%c\n",pp[1] );



  char a = 0x55;
  printf("%c\n",a );
  printf("%x\n",a );
  printf("%d\n",a );
  static float co2_old;
  printf("%f\n",co2_old );
  int  ST =  0xfffc;
  float temp1 = ((float)ST/65536 * 175.72 ) - 46.85;
  float temp2 = ((float)ST * 0.00268127) - 46.85;
printf("%f\n",temp1 );
printf("%f\n",temp2 );
  // *pp= '6';
   // printf("%p\n", &pp);
  // printf("%c\n",pp[1] );
}