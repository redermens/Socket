#include <stdio.h>
#include <string>
#include <winsock2.h>
#include <fstream>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll

using namespace std;

#define BUF_SIZE 1024
#define PORT 12345//
//#define IPv4 "192.168.43.212"
#define IPv4 "192.168.50.85"

int main() {
	ifstream is("E:\\01.jpg", ios::in|ios::binary);//��binary
	if (!is.is_open())
	{
		cout << "file open failed!" << endl;//û�����������ļ���
	}
	else
		cout << "file open success!" << endl;

	//��ʼ�� DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr(IPv4);  //�����IP��ַ
	sockAddr.sin_port = htons(PORT);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//�������״̬
	listen(servSock, 20);
	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	cout << "wait connect..." << endl;
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//��ͻ��˷�������

	//send(clntSock, "hello client", strlen("hello client"),0);
	//send(clntSock, "Bye", strlen("Bye"),0);
	//int tp_length = 0;
	cout << "sending" << endl;
	int n;
	is.seekg(0, ios::end);
	long length = is.tellg();
	is.seekg(0, ios::beg);
	char* buffer = new char[length];
	is.read(buffer, length);
	n = send(clntSock, buffer, length, 0);
	if (n == length)
	{
		cout << "send success! send size = " <<length<< endl;

	}

	//send(clntSock, str, strlen(str) + sizeof(char), NULL);
	//�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);
	delete buffer;
	//��ֹ DLL ��ʹ��
	WSACleanup();
	return 0;
}