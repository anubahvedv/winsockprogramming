// network1.cpp : main project file.
//server

#include "stdafx.h"

#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <iostream>


using namespace System;

using namespace std;

int main()
{
	WSAData wsaData;
	WORD DllVersion=MAKEWORD(2,1);
	if (WSAStartup(DllVersion,&wsaData)!=0)
	{
		//MessageBoxA(NULL,"wINSOCK STARTUP FAILED","Error",MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr;//addres that will bind out listening socket to 
	int addrlen=sizeof(addr);//length of the address (required for access call)
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");//Broadcast locally
	addr.sin_port=htons(1111);//port
	addr.sin_family=AF_INET;//IPV4 Socket 

	SOCKET sListen =socket(AF_INET,SOCK_STREAM,NULL);//Create the socket for new connections
	bind(sListen,(SOCKADDR*)&addr,sizeof(addr));//Bind the address to the socket 
	listen(sListen,SOMAXCONN);//Places sListen socket in a state in which it is listening for an incoming connection, Note:SOMAXCONN=socket outstanding max connections
	
	SOCKET newConnection;//Socket to hold the clients connection
	newConnection=accept(sListen,(SOCKADDR*)&addr,&addrlen);//Accept a new connection
	if (newConnection == 0)//if accepting the client connection failed
	{
		cout<<"Failed to accept the client's connection"<<endl;
	}
	else
	{
		cout<<"client is connected"<<endl;
		char MOTD[256]="Welcome! This is the message of the day";//create buffer with the message 
		send(newConnection,(char*)&MOTD,sizeof(MOTD),NULL);//send MOTD buffer
	}

	system("pause");

		
    return 0;
}
