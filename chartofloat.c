
#include <stdio.h>

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
    return temp.value;
}


int main(int argc, char const *argv[])
{
    char b[4] = {0x29, 0x5c, 0xef, 0x3f};
float a = chartofloat(b);

    // float a = chartofloat("3fef5c29");

printf("%f\n", a);
printf("%s\n", b+4);

	return 0;
}

