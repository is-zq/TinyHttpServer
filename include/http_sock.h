#pragma once
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"common.h"

class TcpServer
{
private:
    int m_socklen;      //struct sockaddr_int的大小
    struct sockaddr_in m_servaddr;
    struct sockaddr_in m_clientaddr;
public:
    int m_listenfd;
    int m_connfd;
    bool m_btimeout;    //超时标志
    int m_buflen;       //Read接收的报文大小

    TcpServer();
    bool InitServer();
    bool Accept();
    char *GetIP();
    void CloseListen();
    void CloseClient();
    ~TcpServer();
};
