/**************************************************************
*   ����ͨ��
*   ������ʼ�����������պ��������ͺ���
*   ��д���ַ����ͺͽ��գ���Ҫ�������ӵ��ֽڷ��ͺͽ���
*   ͨ����SERIAL_COM�޸�ʹ��COM��,SERIAL_BOUD �޸Ĳ�����
*   Ĭ�ϣ�COM�ڣ�com27 ������:115200 ����λ��8 ֹͣλ��1 У�飺��
*   ������VS2017
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>

HANDLE Robocon_com;

#define SERIAL_COM "\\\\.\\COM27"          //com�� \\\\.\\COM10  ����Ҫע�����10�Ķ˿ںű�ʾ������С��10ֱ��comx
#define SERIAL_BOUD 115200

//���ڳ�ʼ��
int Serial_Init()
{
	DCB com_dcb;    //��������
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
	//printf("%d\n", GetCommState(Robocon_com, &com_dcb));//����������óɹ����򷵻�ֵΪ��0������������ʧ�ܣ��򷵻�ֵΪ0��
	if (!GetCommState(Robocon_com, &com_dcb))//���óɹ����򷵻�ֵΪ��0������������ʧ�ܣ��򷵻�ֵΪ0��
	{
		printf("Serial GetCommState fail %d\n", GetLastError);
		return -1;
	}
	GetCommState(Robocon_com, &com_dcb);//��ȡCOM״̬�����ò���
	com_dcb.BaudRate = SERIAL_BOUD;//������
	com_dcb.ByteSize = 8;     //����λ
	com_dcb.Parity = NOPARITY;//У��λ
	com_dcb.StopBits = ONESTOPBIT;     //ֹͣλ
	//com_dcb.fBinary = TRUE;
	//com_dcb.fParity = TRUE;

	if (!SetCommState(Robocon_com, &com_dcb))//���óɹ����򷵻�ֵΪ��0������������ʧ�ܣ��򷵻�ֵΪ0��
	{
		printf("Serial set fail %d\n", GetLastError);
		return -1;
	}
	SetupComm(Robocon_com, 1024, 1024);//��д������

	PurgeComm(Robocon_com, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);//��������־

	memset(&tim_out, 0, sizeof(tim_out));
	tim_out.ReadIntervalTimeout = MAXDWORD;//��дʱ��������
	tim_out.ReadTotalTimeoutConstant = 0;
	tim_out.ReadTotalTimeoutMultiplier = 10;
	tim_out.WriteTotalTimeoutMultiplier = 50;
	tim_out.WriteTotalTimeoutConstant = 5000;
	SetCommTimeouts(Robocon_com, &tim_out);

	return 1;
}

//���ڷ��ͺ���
DWORD Com_Send(char *p, int len)
{
	DWORD write_bytes = 1024;
	COMSTAT comstate;
	DWORD dwErrorFlag;
	BOOL writeFlag;
	OVERLAPPED m_osWrite;

	m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);//�ź�״̬����
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;

	writeFlag = WriteFile(Robocon_com, p, write_bytes, &write_bytes, &m_osWrite);//����

	if (!writeFlag)
	{

		if (GetLastError() == ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_osWrite.hEvent, 1000); //��̨����
			return write_bytes;
		}
		printf("Write fail\n");
		return 0;
	}
	return write_bytes;//д���ֽ���
}
//���ڶ�ȡ����
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

	if (!comstate.cbInQue)//������������
		return 0;

	if (read_bytes > comstate.cbInQue)//������ʵ��������
		read_bytes = comstate.cbInQue;

	readstate = ReadFile(Robocon_com, p, read_bytes, &read_bytes, &m_osRead);    //��ȡ��p

	if (!readstate)
	{
		if (GetLastError() == ERROR_IO_PENDING)  //��̨����
		{
			GetOverlappedResult(Robocon_com, &m_osRead, &read_bytes, TRUE);
			PurgeComm(Robocon_com, PURGE_TXABORT |
				PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
			return read_bytes;//��ȡ�ֽ���
		}

		printf("Read fail\n");
		return 0;
	}
	return read_bytes;
}

//���Դ��룬ע�͵��Ϳ���
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
		if (a >= 50)//50�����д�ģ�û����
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

