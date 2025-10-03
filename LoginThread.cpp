#include "LoginThread.h"
#include "main.h"

//---------------------------------------------------------------------------
LoginThread::LoginThread(const AnsiString& user, const vector<AnsiString>& vWord, const AnsiString& host, unsigned int port) : TThread(false)
{
    LoginThread::user    = user;
    LoginThread::vWord   = vWord;
    LoginThread::host    = host;
    LoginThread::port    = port;
}

//---------------------------------------------------------------------------
void __fastcall LoginThread::Execute()
{
    run = true;

    for(unsigned int i=0; i<vWord.size() && run; i++)
        if(Interface->plug->login(user.c_str(),vWord[i].c_str(),host.c_str(),port))
        {
            Interface->Password->Caption = vWord[i];
            Interface->Out->Lines->Add(AnsiString("Vaild Password :")+AnsiString(vWord[i]));
            Interface->btnStopClick(NULL);
        }
        else
        {
            Interface->Out->Lines->Add(AnsiString("Invaild Password :")+AnsiString(vWord[i]));
        }
}

//---------------------------------------------------------------------------
bool LoginThread::run(true);
