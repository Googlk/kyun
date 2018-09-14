


#include <stdio.h>
int main(int argc, char const *argv[])
{
	/* code */
	 
	printf("please input an integer\n");
	
	 int i,p,n;
    int number[40];
    scanf("%d",&n);  //原题这儿少了一个分号
    p=-1;
    while(n!=0) //(27)选D  //采用的转换方法叫：除模取余倒着读，和短除法分解质因数类似
    {
        number[++p]=n%16; //（28）选A  //这儿保存的是除以16后的余数
        n/=16;  //（29）选C   使n=原数除以16的商
    }
    for(i=p;i>=0;i--)
    {
     if(number[i]<10)    //(30)选B  小于10的直接输出
         printf("%d",number[i]);
     else
         printf("%c",'A'+number[i]-10);  //(31)选D  余数>=10且<16的要变成'A'-'F'
    }
    printf("\n");
    return 0;
	
	

}
