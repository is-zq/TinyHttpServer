#pragma once
#include<string>
#include<sstream>
#include<iostream>
#include"common.h"
#include"http_sock.h"

constexpr int MAX_LENGTH = 1024;

class HttpRequest
{
public:
    std::string m_method;
    std::string m_url;
    int m_status = -1;

    void get_url(std::string line);
    int AcceptRequest(int connfd);
};
