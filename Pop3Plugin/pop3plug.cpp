#include "pop3plugin.h"
#include <winsock2.h>

//---------------------------------------------------------------------------
POP3Plugin::POP3Plugin() : Plugin("POP3 Plugin 1.0","mail.my-mail.ch",110)
{}

//---------------------------------------------------------------------------
bool POP3Plugin::login(const char* user, const char* pass, const char* host, unsigned int port)
{
    bool ret = false;
    char recv_buf[1024], send_buf[1024];

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

                strcpy(send_buf,"USER ");
                strcat(send_buf,user);
                strcat(send_buf,"\n");

                send(cs,send_buf,strlen(send_buf),0);
                recv(cs,recv_buf,1024,0);

                strcpy(send_buf,"PASS ");
                strcat(send_buf,pass);
                strcat(send_buf,"\n");

                send(cs,send_buf,strlen(send_buf),0);
                recv(cs,recv_buf,1024,0);

                ret = (strncmp(recv_buf,"+OK",3) == 0) ? true : false;

                strcpy(send_buf,"quit\n");
                send(cs,send_buf,strlen(send_buf),0);

                send(cs,send_buf,strlen(send_buf),0);
                recv(cs,recv_buf,1024,0);

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
static POP3Plugin plugin;

Plugin* __pascal init_plugin()
{
    return &plugin;
}

void __pascal unload_plugin()
{}

