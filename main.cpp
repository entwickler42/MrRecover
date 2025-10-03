#include <clx.h>
#pragma hdrstop

#include "main.h"
#include "frmoptions.h"
#include <fstream>

using namespace std;

typedef Plugin* (*INIT_FUNC)();
typedef void (*UNLOAD_FUNC)();

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.xfm"

TInterface *Interface;

//---------------------------------------------------------------------------
__fastcall TInterface::TInterface(TComponent* Owner)    : TForm(Owner)
{
    plug == NULL;
}
//---------------------------------------------------------------------------
void __fastcall TInterface::BtnExitClick(TObject *Sender)
{
    Application->Terminate();    
}
//---------------------------------------------------------------------------
void __fastcall TInterface::Quit1Click(TObject *Sender)
{
    Application->Terminate();    
}
//---------------------------------------------------------------------------
void __fastcall TInterface::TimerTimer(TObject *Sender)
{
    lblWork->Visible = lblWork->Visible ? false : true;    
}
//---------------------------------------------------------------------------
void __fastcall TInterface::btnSelectPluginClick(TObject *Sender)
{
    if(OpenDialog->Execute())
    {
        btnStart->Enabled = false;

        if(loadPlugin(OpenDialog->FileName.c_str()))
        {
            lblPlugin->Caption  = plug->plugin_name.c_str();
            Server->Text        = plug->default_server.c_str();
            Port->Text          = WideString(plug->default_port);

            btnStart->Enabled  = true;
        }
        else                                         lblPlugin->Caption = "Can't load Plugin !";

        lblPlugin->Hint    = lblPlugin->Caption;
    }
}
//---------------------------------------------------------------------------
void __fastcall TInterface::btnSelectWordlistClick(TObject *Sender)
{
    if(OpenDialog->Execute())
    {
        Wordlist->Text = OpenDialog->FileName;
        Wordlist->Hint = OpenDialog->FileName;
    }
}
//---------------------------------------------------------------------------
void __fastcall TInterface::SpeedButton5Click(TObject *Sender)
{
    btnStopClick(NULL);
    Application->Terminate();    
}
//---------------------------------------------------------------------------
void __fastcall TInterface::btnStartClick(TObject *Sender)
{
    Out->Clear();

    Timer->Enabled      = true;
    btnStart->Enabled   = false;
    btnStop->Enabled    = true;

    ifstream* in = new ifstream(AnsiString(Wordlist->Text).c_str(), ios::in);
    if(!*in)
    {
        Out->Lines->Add(AnsiString("Can not open Wordlist !"));
        return;
    }

    char ch;
    AnsiString user   = Username->Text;
    AnsiString server = Server->Text;
    AnsiString port   = Port->Text;
    AnsiString line;
    vector<AnsiString> vWord;

    while(!in->eof())
    {
        in->read(&ch,1);
        if(ch == '\n')
        {
            vWord.push_back(line.LowerCase());

            if(FormOptions->UF->Checked)
            {
                char* buf = new char[line.Length()];
                strcpy(buf,line.c_str());   buf[0] -= 32;
                vWord.push_back(AnsiString(buf));
                delete buf;
            }
            if(FormOptions->UL->Checked) vWord.push_back(line.UpperCase());

            line = "";
        }
        else line += ch;
    }

    Out->Lines->Add(AnsiString("Words to process : ")+AnsiString(vWord.size()));

#ifdef MULTITHREAD_BRUTEFORCE
    div_t wpt = div(vWord.size(),FormOptions->Threads->Position);

    LoginThread* login;
    vector<AnsiString> vPass;
    unsigned int cur_pos = 0;

    Out->Lines->Add(AnsiString("Number of threads to create : ")+AnsiString(FormOptions->Threads->Position));

    for(int i=0; i<FormOptions->Threads->Position; i++)
    {
        for(int j=0; j<wpt.quot; j++) vPass.push_back(vWord[cur_pos++]);

        if(i == FormOptions->Threads->Position-1)
            if( wpt.rem > 0 ) for(int k=0; k<wpt.rem; k++) vPass.push_back(vWord[cur_pos++]);

        login = new LoginThread(Username->Text, vPass,Server->Text,AnsiString(Port->Text).ToInt());
        vThread.push_back(login);

        vPass.clear();
    }
#endif
#ifdef SINGLETHREAD_BRUTEFORCE
    for(unsigned int i=0; i<vWord.size(); i++)
        if(plug->login(user.c_str(),vWord[i].c_str(),server.c_str(),port.ToInt()))
        {
            Password->Caption = vWord[i];
            Out->Lines->Add(AnsiString("Login succsess  : ")+vWord[i]);
            i = vWord.size();
            btnStopClick(Sender);
        }
        else Out->Lines->Add(AnsiString("Login faild : ")+vWord[i]);

    btnStopClick(Sender);
#endif
}
//---------------------------------------------------------------------------
void __fastcall TInterface::btnStopClick(TObject *Sender)
{
#ifdef MULTITHREAD_BRUTEFORCE
    LoginThread::run    = false;
    for(unsigned int i=0; i<vThread.size();i++) if(vThread[i]) vThread[i]->Terminate();
    vThread.clear();
#endif

    Timer->Enabled      = false;
    btnStart->Enabled   = true;
    btnStop->Enabled    = false;
    lblWork->Visible    = false;
}
//---------------------------------------------------------------------------
void __fastcall TInterface::ImageBgDblClick(TObject *Sender)
{
    Application->Minimize();
}
//---------------------------------------------------------------------------

void __fastcall TInterface::SpeedButton1Click(TObject *Sender)
{
    FormOptions->Show();
}
//---------------------------------------------------------------------------

bool TInterface::loadPlugin(const char* f)
{
    if(plug) unloadPlugin();

    lib = LoadLibrary(f);
    if(lib == NULL)
    {
        Out->Lines->Add(AnsiString("Can not load Plugin :")+AnsiString(f));
        return false;
    }

    FARPROC proc = GetProcAddress(lib,"INIT_PLUGIN");
    if(proc == NULL)
    {
        Out->Lines->Add(AnsiString("Can not load Plugin :")+AnsiString(f));
        return false;
    }

    plug = (*(INIT_FUNC)(proc))();

    Out->Lines->Add(AnsiString("Plugin loaded :")+AnsiString(f));
    return true;
}
//---------------------------------------------------------------------------

void TInterface::unloadPlugin()
{
    FARPROC proc = GetProcAddress(lib,"UNLOAD_PLUGIN");
    if(proc) ((UNLOAD_FUNC)(proc))();
    plug = NULL;
    FreeLibrary(lib);
}

