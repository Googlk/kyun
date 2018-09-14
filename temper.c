#include <stdio.h>
int temp_first_flag = 1;
int temp_error_flag = 0;
float temp_comp = 0;
void SHT2x_GetTempPoll(float *temp)
{
    float temp1;
    float temp_data;
  //  u8 ack, tmp1, tmp2;
    int ST;
    int i=0;
    temp_data=*temp;
    
    //写状态：流程：
    //SHT_IIC_Start();	//1.主机发起start			
    //SHT_IIC_Send_Byte(I2C_ADR_W);	//2.主机发送从机设备地址（7bit）和write（1bit）操作，等待ack		
    //ack = SHT_IIC_Wait_Ack();	//3.从机发送ack
    //SHT_IIC_Send_Byte(TRIG_TEMP_MEASUREMENT_POLL);//触发 T 测量 非保持主机 1111’0011 
    //ack = SHT_IIC_Wait_Ack();

    

    //tmp1 = SHT_IIC_Read_Byte(1);//data msb
   // delay_ms(1);
    //tmp2 = SHT_IIC_Read_Byte(1);//data lsb and stat.
    //delay_ms(1);
    //crc=SHT_IIC_Read_Byte(0);//checksum
 
    
    if(1)
    {
        ST = 0xfffc;
	    ST &= ~0x0003;
        //temp1 = ((float)ST/65536 * 175.72) - 46.85;
        //temp1 = 36;

        scanf("%f", &temp1);
        if(temp_first_flag==0)
        {
            if((temp1 - temp_data>10)||(temp1 - temp_data<-10))    //两次采集的数据相差10 ，
            {
                temp_error_flag++;
                if(temp1<=0)         //检测到小于0 比较十次进行赋值。
                {
                    if(temp_error_flag<=10)
                    {
                        return;
                    }
                    else
                    {
                        *temp=temp1-temp_comp;
                        temp_error_flag=0;
                        return;
                    }
                }
                else                            //检测到大于0 比较4次进行赋值。
                {
                    if(temp_error_flag<=4)
                    {
                        return;
                    }                 
                    else
                    {
                        *temp=temp1-temp_comp;     //
                        temp_error_flag=0;
                        return;
                    }
                }
            }
         
            temp_error_flag=0;    
            *temp=temp1-temp_comp;
            return;
        }
        else
        {
            temp_error_flag=0;    
            *temp=temp1-temp_comp;
            temp_first_flag=0;
            return;
        }
    }
    else       //校验未通过 直接返回
        return ;
}



int main(int argc, char const *argv[])
{
	float a = 25;
	SHT2x_GetTempPoll(&a);
	printf("%f\n", a);
    
    return 0;
}

