#include"http_response.h"
using namespace std;

bool HttpResponse::SendHead(int connfd,int status,char *tag,char *type)
{
    char main_header[256];
    memset(main_header,0,sizeof(main_header));
    sprintf(main_header,"HTTP/1.1 %d %s\r\nServer: Myhttp Server\r\nContent-Type: %s\r\nConnection: Close\r\n\r\n",status,tag,type);
    if(send(connfd,main_header,strlen(main_header),0) <= 0)
    {
        perror("send");
        return false;
    }
    cout<<main_header<<endl;
    return true;
}

bool HttpResponse::SendHTML(int connfd,const char *file)
{
    FILE *fp = fopen(file,"r");
    if(!fp)
    {
        fclose(fp);
        printf("file open failed\n");
        return false;
    }

    char buffer[512];
    memset(buffer,0,sizeof(buffer));
    while(fgets(buffer,sizeof(buffer),fp))
    {
        cout<<buffer;
        if(send(connfd,buffer,strlen(buffer),0) <= 0)
        {
            perror("send");
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    return true;
}

bool HttpResponse::SendJPG(int connfd,const char *file)
{
    FILE *fp = fopen(file,"r");
    if(!fp)
    {
        fclose(fp);
        printf("file open failed\n");
        return false;
    }

    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    while(!feof(fp))
    {
        int isize = fread(buffer,1,1024,fp);
        if(send(connfd,buffer,isize,0) <= 0)
        {
            perror("send");
            fclose(fp);
            return false;
        }
        memset(buffer,0,sizeof(buffer));
    }

    fclose(fp);
    return true;
}

bool HttpResponse::DoResponse(int connfd,int status,string url)
{
    if(status == OK)
    {
        string s_path(path);
        string file = s_path + url;
        int pos = url.find('.');
        string suf = url.substr(pos+1,5);
        if(strcmp(suf.c_str(),"html") == 0)
        {
            char tag[32] = "OK";
            char type[16] = "html";
            if(SendHead(connfd,OK,tag,type) == false)
                return false;
            if(SendHTML(connfd,file.c_str()) == false)
                return false;
        }
        else if(strcmp(suf.c_str(),"jpg") == 0)
        {
            char tag[32] = "OK";
            char type[16] = "jpg";
            if(SendHead(connfd,OK,tag,type) == false)
               return false;
            if(SendJPG(connfd,file.c_str()) == false)
                return false;
        }
        else
            return false;
    }
    else if(status == BAD_REQUEST)
    {
        char tag[32] = "BAD_REQUEST";
        char type[16] = "html";
        if(SendHead(connfd,BAD_REQUEST,tag,type) == false)
            return false;
        string s_path(path);
        string file = s_path + "/bad_request.html";
        if(SendHTML(connfd,file.c_str()) == false)
            return false;
    }
    else if(status == NOT_FOUND)
    {
        char tag[32] = "NOT_FOUND";
        char type[16] = "html";
        if(SendHead(connfd,NOT_FOUND,tag,type) == false)
            return false;
        string s_path(path);
        string file = s_path + "/not_found.html";
        if(SendHTML(connfd,file.c_str()) == false)
            return false;
    }
    else
    {
        char tag[32] = "INTER_ERROR";
        char type[16] = "html";
        if(SendHead(connfd,INTER_ERROR,tag,type) == false)
            return false;
        string s_path(path);
        string file = s_path + "/inter_error.html";
        if(SendHTML(connfd,file.c_str()) == false)
            return false;
    }

    return true;
}
