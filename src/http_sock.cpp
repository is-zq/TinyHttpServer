#include"http_sock.h"

TcpServer::TcpServer()
{
    m_listenfd = -1;
    m_connfd = -1;
    m_socklen = 0;
    m_btimeout = false;
}

bool TcpServer::InitServer()
{
    if(m_listenfd > 0)
    {
        close(m_listenfd);
        m_listenfd = -1;
    }

    if((m_listenfd = socket(AF_INET,SOCK_STREAM,0)) <= 0)
        return false;

    int opt = 1;unsigned int len = sizeof(opt);
    setsockopt(m_listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,len);

    memset(&m_servaddr,0,sizeof(m_servaddr));
    m_servaddr.sin_family = AF_INET;
    m_servaddr.sin_addr.s_addr = inet_addr(IP);
    m_servaddr.sin_port = htons(SERVER_PORT);
    if(bind(m_listenfd,(struct sockaddr *)&m_servaddr,sizeof(m_servaddr)) != 0)
    {
        perror("bind");
        CloseListen();
        return false;
    }

    if(listen(m_listenfd,5) != 0)
    {
        CloseListen();
        return false;
    }

    m_socklen = sizeof(struct sockaddr_in);

    return true;
}

bool TcpServer::Accept()
{
    if(m_listenfd == -1)
        return false;
    if((m_connfd=accept(m_listenfd,(struct sockaddr *)&m_clientaddr,(socklen_t*)&m_socklen)) < 0)
        return false;
    return true;
}

char *TcpServer::GetIP()
{
    return (inet_ntoa(m_clientaddr.sin_addr));
}

void TcpServer::CloseListen()
{
    if(m_listenfd > 0)
    {
        close(m_listenfd);
        m_listenfd = -1;
    }
}

void TcpServer::CloseClient()
{
    if(m_connfd > 0)
    {
        close(m_connfd);
        m_connfd = -1;
    }
}

TcpServer::~TcpServer()
{
    CloseListen();
    CloseClient();
}
