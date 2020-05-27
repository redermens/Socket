#include <stdio.h>
#include <string>
#include <winsock2.h>
#include <fstream>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

using namespace std;

#define BUF_SIZE 1024
#define PORT 12345//
//#define IPv4 "192.168.43.212"
#define IPv4 "192.168.50.85"

int main() {
	ifstream is("E:\\01.jpg", ios::in|ios::binary);//用binary
	if (!is.is_open())
	{
		cout << "file open failed!" << endl;//没法传输整个文件夹
	}
	else
		cout << "file open success!" << endl;

	//初始化 DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr(IPv4);  //具体的IP地址
	sockAddr.sin_port = htons(PORT);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//进入监听状态
	listen(servSock, 20);
	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	cout << "wait connect..." << endl;
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//向客户端发送数据

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
	//关闭套接字
	closesocket(clntSock);
	closesocket(servSock);
	delete buffer;
	//终止 DLL 的使用
	WSACleanup();
	return 0;
}