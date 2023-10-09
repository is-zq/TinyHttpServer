#include"http_request.h"
using namespace std;

void HttpRequest::get_url(string line)
{
    stringstream ssin(line);
    ssin>>m_method;
    string turl;
    ssin>>turl;
    int pos = turl.find('?');
    if(pos != turl.npos)
    {
        for(int i=0;i<pos;i++)
            m_url.push_back(turl[i]);
        m_url.push_back('\0');
    }
    else
        m_url = turl;
}

int HttpRequest::AcceptRequest(int connfd)
{
    char buffer[MAX_LENGTH];
    memset(buffer,0,sizeof(buffer));
    int isize = recv(connfd,buffer,MAX_LENGTH,0);
    if(isize <= 0)
    {
        m_status = BAD_REQUEST;
        return isize;
    }

    string str(buffer);
    stringstream sin(str);
    string line;

    getline(sin,line);
    get_url(line);
    cout<<line<<endl;
    cout<<"method:"<<m_method<<endl;
    cout<<"url:"<<m_url<<endl;
    string s_path(path);
    string file = s_path + m_url;
    if(access(file.c_str(),F_OK) != 0)
    {
        printf("url is not found\n");
        m_status = NOT_FOUND;
        return isize;
    }

    while(getline(sin,line))
    {
        cout<<line<<endl;
    }
    m_status = OK;
    return isize;
}
