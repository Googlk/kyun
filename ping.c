#include <stdio.h>
int main(int argc, char const *argv[])
{
	/* code */
	char b[] = "0123456789ABCDEF";
	long int n, x;
	int i;
	int a[40];
	printf("input\n");
	scanf("%ld", &n);
	x = n;
	i = 0;
	while(x>0)
	{
		a[i] = x%16;
		x = x/16;
		i++;
	}
	while(i>0)
	{
		printf("%c", b[a[i-1]]);
		i--;
	}
	printf("\n");
	return 0;
}