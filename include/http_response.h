#pragma once
#include<string>
#include<iostream>
#include"common.h"
#include"http_sock.h"

class HttpResponse
{
public:
    bool SendHead(int connfd,int status,char *tag,char *type);
    bool SendHTML(int connfd,const char *file);
    bool SendJPG(int connfd,const char*file);
    bool DoResponse(int connfd,int status,std::string url);
};
