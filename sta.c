#include<stdio.h>
int fun(int n)
{
     static int f=1;
    f=f*n;
    return f;
}
void main()
{
    int i;
    for(i=1;i<=5;i++)
    printf("fun(%d)=%d\n",i,fun(i));
}