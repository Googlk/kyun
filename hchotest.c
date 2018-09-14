
#include <stdio.h>
#define UART_RX_LEN 300
// u8 HCHO_CMD[6]={0x55,0xAA,0x03,0xC0,0xBF,0x10};
unsigned char UART4_RX_BUF[UART_RX_LEN]={0x55,0xAA,0x07,0xdc,0x29,0x5c,0xef,0x3f,0x55,0x55};
 // int UART4_RX_BUF[UART_RX_LEN]={0x55,0xAA,0x07,0xdc,0x29,0x5c,0xef,0x3f,0x9b,0x08};
float hcho;
typedef union  
{   
    float  value;   
    struct   
    {  
        unsigned char low_byte;  
        unsigned char mlow_byte;  
        unsigned char mhigh_byte;  
        unsigned char high_byte;  

            
            
        /*  
            unsigned char high_byte; 
            unsigned char mhigh_byte;
            unsigned char mlow_byte;
            unsigned char low_byte;  
            
        */ 
            
            
    }float_byte; 
}Float4Byte; 

float chartofloat(unsigned char *pdat)
{
    Float4Byte temp;
    
    temp.float_byte.low_byte = *pdat++;
    printf("%x\n",temp.float_byte.low_byte  );
    temp.float_byte.mlow_byte = *pdat++;
    temp.float_byte.mhigh_byte = *pdat++;
    temp.float_byte.high_byte = *pdat;
    printf("%x\n",temp.float_byte.high_byte  );
    return temp.value;
}

//aoinn project
float Get_hcho(void)
{
    char i=0;
    float hcho_tmp;
   
    // USART_Puts(UART4, HCHO_CMD, 6); //Query formaldehyde data
    // delay_ms(200);
    while(i<=100)
    {//55 AA 07 DC (0A D7 23 3C) 5F 12 
        // printf("%x\n", *(UART4_RX_BUF+i+3));
        if(*(UART4_RX_BUF+i)==0x55&&*(UART4_RX_BUF+i+1)==0xAA&&*(UART4_RX_BUF+i+2)==0x07&&*(UART4_RX_BUF+i+3)==0xdc)//地址回应正确
        {
            // printf("dd\n");
            //mem_copy((unsigned char *)&hcho_tmp,USART3_RX_BUF+i+3,4);
            // printf("%c\n", (UART4_RX_BUF+i+4));UART4_RX_BUF[4]后面的所有数据包含4
            hcho_tmp = chartofloat(UART4_RX_BUF+i+4); 
            // mem_clear(UART4_RX_BUF, UART_RX_LEN);        //clear cache
            printf("hcho_tmp%f\n", hcho_tmp);
            return hcho_tmp;
            
        }
        
        i++;
    }

    // mem_clear(UART4_RX_BUF, UART_RX_LEN);
    printf("hcho%f\n", hcho);
    return hcho;
} 



int main(int argc, char const *argv[])
{
    float dd = Get_hcho();
	printf("aa%f\n", dd);

	return 0;
}

