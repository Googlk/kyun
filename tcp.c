#include <sys/stat.h>

#include <fcntl.h>

#include <errno.h>

#include <netdb.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>

#define SERVER_PORT 8899

/*

连接到服务器后，会不停循环，等待输入，

输入quit后，断开与服务器的连接

*/

#define S_LOOPTIME   1  

#define MX (z>>5^y<<2)+(y>>3^z<<4)^(sum^y)+(k[p&3^e]^z)
#define DELTA 0x9e3779b9
unsigned char key[]={0x41,0x59,0x85,0x94,0x00,0x01,0x00,0x00,0x04,0x19,0x00,0x05,0x04,0x19,0x00,0x05};
void btea_decrpyt( unsigned char* buf, unsigned char count)
{
	// puts(buf);
	printf("btea_decrpyt\n");
	for (int i = 0; i < 36; i++)
{
	// printf("test\n");
	/* code */
	// sprintf(dst+i,"%02x",recvbuf[i]);
	// atoi();
	// dst[i] = AscToHex(recvbuf[i]);
	// printf("%02d  %02x   %d\n", i, recvbuf[i],recvbuf[i]);
	printf(" %d %02x \n", i ,*(buf+i));
	// printf("% ", recvbuf[i]);


}
  unsigned char n=count/4;
  printf("%d\n", n);
  unsigned long *v=(unsigned long *)buf;
  unsigned long *k=(unsigned long *)key;
  unsigned long z = v[n - 1],y = v[0],sum = 0,e ;
  unsigned char  p,q ;

  if(n==0) return;
  //Decoding Part...
  q = S_LOOPTIME + 52 / n ;
  printf("%d\n", q);
  sum = q * DELTA ;
  printf("%ld\n", sum);

  while ( sum != 0 )
  {
    e = sum >> 2 & 3 ;
// printf("%ld\n", e);
    for ( p = n - 1 ; p > 0 ; p-- )
    {  
    	printf("p %d\n", p);
    	z = v[p - 1];
    	printf("%ld\n", z);
       y = v[p] -= MX;
    }

    z = v[n - 1] ;
    y = v[0] -= MX;
    sum -= DELTA ;
    // printf("%ld\n", sum);
  }



for (int i = 0; i < 36; i++)
{
	// printf("test\n");
	/* code */
	// sprintf(dst+i,"%02x",recvbuf[i]);
	// atoi();
	// dst[i] = AscToHex(recvbuf[i]);
	// printf("%02d  %02x   %d\n", i, recvbuf[i],recvbuf[i]);
	printf(" %d %02x \n", i ,*(v+i));
	// printf("% ", recvbuf[i]);


}


}



unsigned char AscToHex(unsigned char aHex){
if((aHex>=0)&&(aHex<=9))
aHex += 0x30;
else if((aHex>=10)&&(aHex<=15))//A-F
aHex += 0x37;
else aHex = 0xff;
return aHex;
}

int main()

{

//客户端只需要一个套接字文件描述符，用于和服务器通信

int clientSocket;

//描述服务器的socket

struct sockaddr_in serverAddr;

unsigned char sendbuf[200];

unsigned char recvbuf[200];
unsigned char dst[200];

int iDataNum;

if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)

{

perror("socket");

return 1;

}

serverAddr.sin_family = AF_INET;

serverAddr.sin_port = htons(SERVER_PORT);

//指定服务器端的ip，本地测试：127.0.0.1

//inet_addr()函数，将点分十进制IP转换成网络字节序IP

serverAddr.sin_addr.s_addr = inet_addr("192.168.1.113");

if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)

{

perror("connect");

return 1;

}

printf("连接到主机...\n");

while(1)

{

// printf("发送消息:");

// scanf("%s", sendbuf);

// printf("\n");

// send(clientSocket, sendbuf, strlen(sendbuf), 0);

 

if(strcmp(sendbuf, "quit") == 0)

break;

printf("\n读取消息:");

recvbuf[0] = '\0';

iDataNum = recv(clientSocket, recvbuf, 200, 0);
printf("%d\n", iDataNum);
// recvbuf[iDataNum*2] = '\0';
unsigned char *src = recvbuf;
// int j = 0;
// while(*src !='\0' )
// {
// 	sprintf(dst+j,"%x",*src++);
// 	j++;
// }
// printf("%d\n", strlen(dst));
// char *dst;
for (int i = 0; i < iDataNum; i++)
{
	/* code */
	// sprintf(dst+i,"%02x",recvbuf[i]);
	// atoi();
	// dst[i] = AscToHex(recvbuf[i]);
	// printf("%02d  %02x   %d\n", i, recvbuf[i],recvbuf[i]);
	printf("%02x ", recvbuf[i]);
	// printf("% ", recvbuf[i]);


}
printf("\n:");
// printf("%s\n", dst);
btea_decrpyt((unsigned char*)(src+4), 36);
for (int i = 0; i < 36; i++)
{
	/* code */
	// sprintf(dst+i,"%02x",recvbuf[i]);
	// atoi();
	// dst[i] = AscToHex(recvbuf[i]);
	// printf("%02d  %02x   %d\n", i, recvbuf[i],recvbuf[i]);
	printf("%02x ", *(src+4+i));
	// printf("% ", recvbuf[i]);


}


}

close(clientSocket);

return 0;

}