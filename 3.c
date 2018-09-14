#include <stdio.h>
#include <string.h>

 
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

    char *cmd = "ATE0";
    printf("%d\n", sizeof cmd);
    printf("%d\n", strlen(cmd));


    float temp;
    typedef unsigned short int      uint16_t; 
    typedef uint16_t u16;
    u16 mantissa;
    u16 fraction;   
    int pclk2;
    pclk2 = 72;

   
    temp=(float)(pclk2*1000000)/(9600*16);//得到USARTDIV
    printf("%f\n", temp);
    mantissa=(int)temp;               //得到整数部分
    printf("%d\n", mantissa);
    fraction=(temp-mantissa)*16; //得到小数部分    
    printf("%d\n",fraction );
    mantissa<<=4;
    mantissa+=fraction; 


    char check_wifi_flag;
    printf("%d\n",check_wifi_flag );

    long ret1 = 0;
long ret2 = 0;
unsigned char data[20]={0x12, 0x7d};  
ret1 = data[0];
    ret1 = (ret1<<8)+data[1];
printf("%d\n", ret1);
ret2 =    data[0]*(256)+data[1];
printf("%d\n", ret2);
float k  = (44)/22.4;
float l  = (44)/24.46;


float y =0;
float y1 =0;
float z=0;
for (int i = 125; i < 600; ++i)
{
    /* code */
    y =k*i/1000;
    y1 =l*i/1000;
    z = 0.001799*i;
    // printf("i%d  %f  %f  %f\n",i, y,y1, z);
}

char * a = "asdf";
char * b = "asdf\r\n";
// sprintf((char*)cmd, "%s\r\n", cmd);
printf("%s %d\n", a, strlen(a));
// printf("%s", b);
// printf("%d\n", strlen(b));
struct Config_Info
    {
        char *command;
        char *retComd;  //gprs?LR|?LRD|I????LR|
        unsigned char time;  //??L??LR|?Lo!A??
    };
    
     struct Config_Info GPRS_Cmd[] = {
        "AT+CGATT?\r\n", "+CGATT: 1",50,\
        "AT+CIPMODE=0\r\n","OK",50,\
        "AT+CSTT=\"CMNET\"\r\n", "OK",25,\
        "AT+CIICR\r\n","OK",25,\
        "AT+CIFSR\r\n", ".", 25,\
        //  "AT+CIPSRIP=1\r\n","OK",25,
        "AT+CIPSTART=\"UDP\",\"120.25.67.66\",\"9718\"\r\n","CONNECT",50
    };
printf("%d %d\n",  sizeof(GPRS_Cmd), strlen((char*)GPRS_Cmd));

for (int i = 0; i < 6; ++i)
{
    /* code */
    // printf("%s\n", GPRS_Cmd[i]);
    // printf("%s", GPRS_Cmd[i].command);
    // printf("%s\n", GPRS_Cmd[i].retComd);
    // printf("%d\n\n", GPRS_Cmd[i].time);
}
char *  USART2_RX_BUF = "STATE: IP INITIAL";
    char * pch;
    pch = strstr(USART2_RX_BUF, "CONNECT");
        printf("%s\n", pch);

    return 0;
}