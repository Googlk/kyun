#include <stdio.h>
// int input[2] = {0, 1};

// void printIntArray(int input[]){
//     for(int i = 0; i < 44; i ++){
//         printf("%02x ", input[i]);
//     }
// }

// int* printIntArray(int input[]){
//     input[0] = 0x56;
//     return input;
// }
// 编译生成动态库: gcc -g -fPIC -shared -o libtest.so test.c
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 

#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

#include <sys/types.h>

#include<WINSOCK2.H>
#include <string.h>
// #include <WS2tcpip.h>
#include <stdlib.h>
unsigned  char dst[200];


#define SERVER_PORT 8899
#include "stdio.h"
#include "stdlib.h"
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define MX (z>>5^y<<2)+(y>>3^z<<4)^(sum^y)+(k[p&3^e]^z)
#define DELTA 0x9e3779b9
#define S_LOOPTIME   1    //5
#define BLOCK_SIZE   44  


//unsigned char Key[16] = { 0x3A,0xDA,0x75,0x21,0xDB,0xE2,0xDB,0xB3,0x11,0xB4,0x49,0x01,0xA5,0xC6,0xEA,0xD4 };
//unsigned char dst[8] = { 0xAD,0xDE,0xE2,0xDB,0xB3,0xE2,0xDB,0xB3 };
//unsigned char dst[36] = { 0x00, 0x49, 0x53, 0x01, 0x00, 0x02, 0x00, 0x00, 0xD0, 0x18, 0x00, 0xA0, 0x71, 0x3D, 0xF2, 0x41, 0x00, 0xA2, 0x00 ,0x00 ,0x00,0x00 ,0x00 ,0xA4 ,0x00 ,0x00 ,0xA6 ,0x41 ,0x00 ,0xA6 ,0xEC ,0x51 ,0xB0 ,0x40 ,0xE3 ,0xF8 };
/*
*key  maybe 128bit =16 Bytes.
*buf  maybe BLOCK_SIZE
*/
typedef union {
	float f;
	char  buf[4];
}data;
data TEMP;
data NH4;
data DO;
data PH;


/*
*key  maybe 128bit =16Bytes.
*buf  maybe BLOCK_SIZE
inbuf == outbuf == buf
*/


void btea_decrpyt(unsigned char* buf)
{
	 char Key[] = { 0x41,0x59,0x85,0x94,0x00,0x01,0x00,0x00,0x04,0x19,0x00,0x05,0x04,0x19,0x00,0x05 };//16byte
	int n = 11;
	 long *v = ( long *)buf;
	 long *k = ( long *)Key;
	 unsigned int z = v[n - 1];
	 unsigned int  y = v[0];
	int sum = 0;
	int e = 0;
	int  p, q;
	int mx1;
	// printf("n = %d\n", n);
	//Decoding Part...
	//q = S_LOOPTIME + 52 / n;
	q = 1 + 52 / n;
	//printf("qq = %d\n", 52/n);
	//printf("qqq = %d\n", q);
	sum = q * 0x9e3779b9;
	//printf("5xdelta = %d\n", 5* DELTA);
	//printf("xDELTA %x\n", DELTA);
	//printf("DELTA %ld\n", DELTA);
	//printf("DELTA %I32d\n", DELTA);
	//printf("%x\n", DELTA);
	//printf("sum = %I32d\n", sum);
	while (sum != 0)
	{
		//printf("sum = %I32d\n", sum);
		e = sum >> 2 & 3;
		//printf("%I32d\n", e);
		for (p = n - 1; p > 0; p--)
		{
			z = v[p - 1];
				/*y = v[p] -= MX;*/
				//  mx1 = z >> 5 ^ y << 2 + (y >> 3 ^ z << 4) ^ (sum^y) + k[p & 3 ^ e] ^ z;
				 //printf("mx1 = %d\n", mx1);
			v[p] -= MX;
			y = v[p];
		}
			
		
		z = v[n - 1];
		// mx1 = (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum^y) + (k[p & 3 ^ e] ^ z);
		v[0] -= MX;
		y = v[0];

		sum -= 0x9e3779b9;

	}
}

int clientSocket;

char cmp[20] = "192.168.1.1";
char* foo(char* ad)
{
    
    // int clientSocket;
    if(strcmp(ad, cmp) != 0)
    {
        // printf("ad %s\n", ad);
        strcpy(cmp, ad);
        printf("cmp %s\n", cmp);
        printf("foo...\n");
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
    
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
		if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
        perror("socket");
        return 0;
        }

		//描述服务器的socket

        struct sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(8899);
		
        serverAddr.sin_addr.s_addr = inet_addr(ad);
        // foo.sin_addr.addr=inet_addr("192.168.1.152");
        // inet_pton(AF_INET, "192.168.1.152", &serverAddr.sin_addr.s_addr);
		printf("连接到主机...\n");
		if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
		{  //连接失败 
			printf("connect error !");
		
			return 0;
		}
 //string转const char* 
								   //char * sendData = "你好，TCP服务端，我是客户端\n";
		//send(sclient, sendData, strlen(sendData), 0);
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 

		unsigned char recData[255];
		//printf("recv...\n");
		// while (1)
		// {
			int ret = recv(clientSocket, (char*)recData, 255, 0);
			if (ret>0) {
				recData[ret] = 0x00;
				// strncpy((char*)dst, (char*)recData+3, BLOCK_SIZE);
                strncpy_s((char*)dst,  49, (const char *)recData+3, BLOCK_SIZE);
				
				//原始传输的数据
				// printf("\n\n原始传输的数据\n");
				// for (int i = 0; i < ret; i++)
				// {
				// 	//printf(" %d  %d \n",i, recData[i]);//X大写x小写输出
				// }
				//tea(dst);
				// printf("\n加密数据:\n");
				// for (int Loop_i = 0; Loop_i<BLOCK_SIZE; Loop_i++)
				// {
				// 	// printf("%02X ", dst[Loop_i]);
				// 	//printf(" %d  %d \n", Loop_i, dst[Loop_i]);//X大写x小写输出

				// }
				// printf("\n");
				btea_decrpyt(dst);
				// printf("\n解密数据:\n");
				// for (int Loop_i = 0; Loop_i<BLOCK_SIZE; Loop_i++)
				// {
				// 	// printf("%02X ", dst[Loop_i]);
				// 	//printf("%d %02x \n", Loop_i, dst[Loop_i]);
				// 	//printf(" %d  %d \n", Loop_i, dst[Loop_i]);//X大写x小写输出
				// }
                printf("unfoo ad %s\n", ad);
                return (char*)dst;
		
			}

    }
    else
    {
        printf("foo...bulianjie\n");
	
 //string转const char* 
								   //char * sendData = "你好，TCP服务端，我是客户端\n";
		//send(sclient, sendData, strlen(sendData), 0);
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 

		unsigned char recData[255];
		//printf("recv...\n");
		// while (1)
		// {
			int ret = recv(clientSocket, (char*)recData, 255, 0);
			if (ret>0) {
				recData[ret] = 0x00;
				// strncpy((char*)dst, (char*)recData+3, BLOCK_SIZE);
                strncpy_s((char*)dst,  49, (const char *)recData+3, BLOCK_SIZE);
				
				//原始传输的数据
				// printf("\n\n原始传输的数据\n");
				// for (int i = 0; i < ret; i++)
				// {
				// 	//printf(" %d  %d \n",i, recData[i]);//X大写x小写输出
				// }
				//tea(dst);
				// printf("\n加密数据:\n");
				// for (int Loop_i = 0; Loop_i<BLOCK_SIZE; Loop_i++)
				// {
				// 	// printf("%02X ", dst[Loop_i]);
				// 	//printf(" %d  %d \n", Loop_i, dst[Loop_i]);//X大写x小写输出

				// }
				// printf("\n");
				btea_decrpyt(dst);
				// printf("\n解密数据:\n");
				// for (int Loop_i = 0; Loop_i<BLOCK_SIZE; Loop_i++)
				// {
				// 	// printf("%02X ", dst[Loop_i]);
				// 	//printf("%d %02x \n", Loop_i, dst[Loop_i]);
				// 	//printf(" %d  %d \n", Loop_i, dst[Loop_i]);//X大写x小写输出
				// }
                return (char*)dst;
		
			}

    }
    
		// }
		// closesocket(clientSocket);
	// WSACleanup();
	// system("pause");
	// return 0;
}

typedef struct StructPointerTest
{
	unsigned char name[100];
	// unsigned char age;
}StructPointerTest, *StructPointer;
 
int strTest(char* pp)
{
        // printf("val:%s\n", pp);
        // printf("strTest...\n");
        return 0;
}


StructPointer test(char* pVal)	// 返回结构体指针
{ 
	StructPointer p = (StructPointer)malloc(sizeof(StructPointerTest)); 
    // printf("%s\n", pVal);
    strTest(pVal);
    unsigned char* pp = foo(pVal);
    
    
    // foo(pVal);
    printf("\n");
    for(int i = 0; i < 44; i++)
    {
        // printf("%02X ", pp[i]);
        p->name[i] = pp[i];
        // strncpy(p->name[i], (const char)pp[i], 1);

    }
	// strcpy(p->name, pVal);
    printf("\n");
    for(int i = 0; i < 44; i++)
    {
        // printf("%02X ", p->name[i]);
    }
	// p->age = 81;
	
	return p; 
}
//传递字符串
