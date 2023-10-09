#include"http_sock.h"
#include"http_request.h"
#include"http_response.h"
#include<sys/fcntl.h>
#include<sys/time.h>
using namespace std;

int main()
{
    TcpServer server;
    if(server.InitServer() == false)
    {
        printf("init failed\n");
        return -1;
    }

    fd_set readfdset;
    int maxfd;
    FD_ZERO(&readfdset);
    FD_SET(server.m_listenfd,&readfdset);
    maxfd = server.m_listenfd;

    while(true)
    {
        cout<<"等待连接......"<<endl;
        fd_set tmpfdset = readfdset;

        int infds = select(maxfd+1,&tmpfdset,NULL,NULL,NULL);

        if(infds < 0)
        {
            printf("select() failed\n");
            perror("select)");
            break;
        }

        for(int eventfd=0;eventfd<=maxfd;eventfd++)
        {
            if(FD_ISSET(eventfd,&tmpfdset) <= 0)
                continue;

            if(eventfd == server.m_listenfd)
            {
                if(server.Accept() == false)
                {
                    printf("connect failed\n");
                    continue;
                }
                cout<<server.GetIP()<<"已连接\n";
                FD_SET(server.m_connfd,&readfdset);
                if(maxfd < server.m_connfd)
                    maxfd = server.m_connfd;
                continue;
            }

            else
            {
                HttpRequest request;
                cout<<"Request:\n";
                if(request.AcceptRequest(eventfd) <= 0)
                {
                    close(eventfd);
                    FD_CLR(eventfd,&readfdset);

                    if(eventfd == maxfd)
                    {
                        for(int i=maxfd;i>0;i--)
                        {
                            if(FD_ISSET(i,&readfdset))
                            {
                                maxfd = i;
                                break;
                            }
                        }
                    }
                    continue;
                }

                cout<<"\n---------------------------------------------------------------------------\n\n";

                cout<<"Response:\n";
                HttpResponse response;
                if(response.DoResponse(eventfd,request.m_status,request.m_url) == false)
                {
                    printf("response failed\n");
                    continue;
                }
            }
        }
    }

    return 0;
}
