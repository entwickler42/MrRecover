#include "main.h"
#include <windows.h>

//---------------------------------------------------------------------------
FTPPlugin::FTPPlugin() : Plugin("FTP Plugin 1.0","ftp.freenet.de",21)
{}

//---------------------------------------------------------------------------
bool FTPPlugin::login(const char* user, const char* pass, const char* host, unsigned int port)
{
    bool ret = false;
    char recv_buf[512], send_buf[512];

    WSAData data;
    WSAStartup(MAKEWORD(1,1),&data);

    HOSTENT *h;
    SOCKADDR_IN remote;
    unsigned long ip;
    int cs;

    if( (ip = inet_addr(host)) == INADDR_NONE)
    {
        h = gethostbyname(host);
        if(host == NULL) return false;
        memcpy(&ip,h->h_addr_list[0],h->h_length);
        if ( ip == INADDR_NONE ) return false;
    }

    remote.sin_family = AF_INET;
    remote.sin_port   = htons(port);
    remote.sin_addr.S_un.S_addr   = ip;
    memset(remote.sin_zero,0,sizeof(remote.sin_zero));

    unsigned int ree = 5;
    while(ree > 0 )
    {
        if ((cs = socket(AF_INET,SOCK_STREAM,0)) != -1 )
        {
            if(connect(cs,(struct sockaddr*)&remote,sizeof(struct sockaddr_in)) != -1)
            {
                recv(cs,recv_buf,1024,0);

                strcpy(send_buf,"user ");
                strcat(send_buf,user);
                strcat(send_buf,"\r\n");

                send(cs,send_buf,strlen(send_buf),0);
                recv(cs,recv_buf,1024,0);

                strcpy(send_buf,"pass ");
                strcat(send_buf,pass);
                strcat(send_buf,"\r\n");

                send(cs,send_buf,strlen(send_buf),0);
                recv(cs,recv_buf,1024,0);

                ret = (strncmp(recv_buf,"230",3) == 0) ? true : false;
                ree = 1;
            }
            closesocket(cs);
        }
        ree--;
    }

    WSACleanup();
    return ret;
}

//---------------------------------------------------------------------------
static FTPPlugin plugin;

Plugin* __pascal init_plugin()
{
    return &plugin;
}

//---------------------------------------------------------------------------
void __pascal unload_plugin()
{}

//---------------------------------------------------------------------------
#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    return 1;
}
//---------------------------------------------------------------------------
 