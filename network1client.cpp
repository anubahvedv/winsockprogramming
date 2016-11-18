// network1client.cpp : Defines the entry point for the console application.
//client

#include "stdafx.h"

#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <iostream>


//using namespace System;

using namespace std;


int main()
{
	WSAData wsaData;
	WORD DllVersion=MAKEWORD(2,1);
	if (WSAStartup(DllVersion,&wsaData)!=0)
	{
		//MessageBoxA(NULL,"wINSOCK STARTUP FAILED","Error",MB_OK | MB | ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr;//address to be binded to our connection socket 
	int sizeofaddr=sizeof(addr);//
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");//address=localhost 
	addr.sin_port=htons(1111);//port=1111
	addr.sin_family=AF_INET;//IPV4 Socket 

	SOCKET Connection;//Socket to hold the clients connection
	Connection=socket(AF_INET,SOCK_STREAM,NULL);//Accept a new connection

	if (connect(Connection,(SOCKADDR*)&addr,sizeofaddr)!=0)
	{
		//MessageBoxA(NULL,"Failed to connect","Error",MB_OK | MB | ICONERROR);
		return 0;
	}

	char MOTD[256];
	recv(Connection,MOTD,sizeof(MOTD),NULL);//send MOTD buffer
	cout<<"MOTD:"<<MOTD<<endl;
	system("pause");

    return 0;
}
