     // #include <syslib.h>
#include<stdio.h>
      #include <string.h>

      int main()
      {
        char *s="STATE: CONNECT OK";
        char *l="CONNECT";
        char *p;
        
        // clrscr();
        
        p=strstr(s,"CONNECT");
        if(p)
          printf("%s",p);
        else
          // printf("Not Found!");
printf("dd\n");

int a = strlen("check_gprs");
printf("%d\n", a);
        // getchar();
for (int i = 48; i < 122; ++i)
{
  /* code */
  printf("%d  %x\n",i, i );
}
        return 0;
      }