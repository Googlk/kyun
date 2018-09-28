/**************************************************************
*   串口通信
*   包含初始化函数，接收函数，发送函数
*   仅写了字符发送和接收，需要可以增加单字节发送和接收
*   通过宏SERIAL_COM修改使用COM口,SERIAL_BOUD 修改波特率
*   默认：COM口：com27 波特率:115200 数据位：8 停止位：1 校验：无
*   环境：VS2017
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>

HANDLE Robocon_com;

#define SERIAL_COM "\\\\.\\COM27"          //com口 \\\\.\\COM10  这里要注意大于10的端口号表示方法，小于10直接comx
#define SERIAL_BOUD 115200

//串口初始化
int Serial_Init()
{
	DCB com_dcb;    //参数设置
	COMMTIMEOUTS tim_out;

	Robocon_com = CreateFile(SERIAL_COM, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

	if (Robocon_com == (HANDLE)-1)
	{
		printf("Serial open fail\n");
		return -1;
	}
	else
	{
		printf("Serial open succ\n");
	}
	//printf("%d\n", GetCommState(Robocon_com, &com_dcb));//如果函数调用成功，则返回值为非0；若函数调用失败，则返回值为0。
	if (!GetCommState(Robocon_com, &com_dcb))//调用成功，则返回值为非0；若函数调用失败，则返回值为0。
	{
		printf("Serial GetCommState fail %d\n", GetLastError);
		return -1;
	}
	GetCommState(Robocon_com, &com_dcb);//获取COM状态，配置参数
	com_dcb.BaudRate = SERIAL_BOUD;//波特率
	com_dcb.ByteSize = 8;     //数据位
	com_dcb.Parity = NOPARITY;//校验位
	com_dcb.StopBits = ONESTOPBIT;     //停止位
	//com_dcb.fBinary = TRUE;
	//com_dcb.fParity = TRUE;

	if (!SetCommState(Robocon_com, &com_dcb))//调用成功，则返回值为非0；若函数调用失败，则返回值为0。
	{
		printf("Serial set fail %d\n", GetLastError);
		return -1;
	}
	SetupComm(Robocon_com, 1024, 1024);//读写缓冲区

	PurgeComm(Robocon_com, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);//清除错误标志

	memset(&tim_out, 0, sizeof(tim_out));
	tim_out.ReadIntervalTimeout = MAXDWORD;//读写时间间隔设置
	tim_out.ReadTotalTimeoutConstant = 0;
	tim_out.ReadTotalTimeoutMultiplier = 10;
	tim_out.WriteTotalTimeoutMultiplier = 50;
	tim_out.WriteTotalTimeoutConstant = 5000;
	SetCommTimeouts(Robocon_com, &tim_out);

	return 1;
}

//串口发送函数
DWORD Com_Send(char *p, int len)
{
	DWORD write_bytes = 1024;
	COMSTAT comstate;
	DWORD dwErrorFlag;
	BOOL writeFlag;
	OVERLAPPED m_osWrite;

	m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);//信号状态设置
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;

	writeFlag = WriteFile(Robocon_com, p, write_bytes, &write_bytes, &m_osWrite);//接收

	if (!writeFlag)
	{

		if (GetLastError() == ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_osWrite.hEvent, 1000); //后台发送
			return write_bytes;
		}
		printf("Write fail\n");
		return 0;
	}
	return write_bytes;//写入字节数
}
//串口读取函数
DWORD Com_Recv(char *p, int len)
{
	DWORD read_bytes = len;
	BOOL readstate;
	DWORD dwErrorFlag;
	COMSTAT comstate;
	OVERLAPPED m_osRead = { 0 };

	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_osRead.hEvent = NULL)
		return 0;

	memset(&comstate, 0, sizeof(COMSTAT));

	ClearCommError(Robocon_com, &dwErrorFlag, &comstate);

	if (!comstate.cbInQue)//缓冲区无数据
		return 0;

	if (read_bytes > comstate.cbInQue)//缓冲区实际数据量
		read_bytes = comstate.cbInQue;

	readstate = ReadFile(Robocon_com, p, read_bytes, &read_bytes, &m_osRead);    //读取到p

	if (!readstate)
	{
		if (GetLastError() == ERROR_IO_PENDING)  //后台接收
		{
			GetOverlappedResult(Robocon_com, &m_osRead, &read_bytes, TRUE);
			PurgeComm(Robocon_com, PURGE_TXABORT |
				PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
			return read_bytes;//读取字节数
		}

		printf("Read fail\n");
		return 0;
	}
	return read_bytes;
}

//测试代码，注释掉就可以
#define RECVLEN 63
int main()
{
	
	unsigned char str[RECVLEN];
	memset(str, '\0', RECVLEN);
	int a;
	Serial_Init();
	while (1)
	{
		a = Com_Recv(str, 80);
		//printf("%d\n", a);
		if (a >= 50)//50是随便写的，没意义
		{
			for (size_t i = 0; i < RECVLEN; i++)
			{
				//printf("%d %02X \n",i, str[i]);
				printf("%02X ", str[i]);
			}
			printf("\n");
		}
		
		Sleep(1000);
	}
	return 0;
}

