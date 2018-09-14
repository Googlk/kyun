#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	/* code */
	int count, len;
	char cunt = 10;        
	
	int a = 0;
	char  send_ps[100];
	typedef struct
{
  char nongdu;
  float nongdudy;
}dian;
	dian hcho_dy[20];
	send_ps[a*5] = *((unsigned char *)(hcho_dy) + a*5);


	len = 0;
	unsigned char Flash_data[105]={0x25,15,0x80,0x3F};//前两个是地址，后两个表示波特率
	count =  sizeof(Flash_data);
unsigned char dat[4]={0};
	char str[20]={0};
	int count1 =  sizeof(str);
	len = strlen(str);
char *cmd = Flash_data;
printf("%x\n", cmd[0]);
printf("%x\n", cmd[1]);
cmd = cmd+1;
printf("%x\n", cmd);

	for (int i = 0; i < count1; ++i)
	{

		// printf("%d  %x  \n", i,Flash_data[i]);
		// printf("%d  %p  \n", i,str[i]);
		/* code */
	}
	return 0;
}