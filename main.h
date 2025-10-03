#ifndef mainH
#define mainH

#define SINGLETHREAD_BRUTEFORCE

//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QExtCtrls.hpp>
#include <QGraphics.hpp>
#include <QButtons.hpp>
#include <QMenus.hpp>
#include <QTypes.hpp>
#include <QDialogs.hpp>
#include <QImgList.hpp>

#ifdef MULTITHREAD_BRUTEFORCE
#include "LoginThread.h"
#endif
#ifdef SINGLETHREAD_BRUTEFORCE
#include "Plugin.h"
#include <vector>
#endif

//---------------------------------------------------------------------------
class TInterface : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TImage *ImageBg;
    TLabel *Label1;
    TOpenDialog *OpenDialog;
    TImageList *ImageList;
    TLabel *Label3;
    TLabel *Label2;
    TLabel *Label4;
    TLabel *Label5;
    TSpeedButton *btnSelectWordlist;
    TSpeedButton *btnSelectPlugin;
    TLabel *Password;
    TLabel *Label7;
    TEdit *Username;
    TSpeedButton *btnStart;
    TSpeedButton *btnStop;
    TSpeedButton *SpeedButton5;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *lblWork;
    TTimer *Timer;
    TEdit *Wordlist;
    TLabel *Label6;
    TLabel *Label10;
    TEdit *Server;
    TLabel *Label11;
    TLabel *Label12;
    TEdit *Port;
    TLabel *lblPlugin;
    TSpeedButton *SpeedButton1;
    TMemo *Out;
    void __fastcall BtnExitClick(TObject *Sender);
    void __fastcall Quit1Click(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall btnSelectPluginClick(TObject *Sender);
    void __fastcall btnSelectWordlistClick(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
    void __fastcall btnStartClick(TObject *Sender);
    void __fastcall btnStopClick(TObject *Sender);
    void __fastcall ImageBgDblClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
private:	// Benutzer-Deklarationen
    HMODULE lib;
#ifdef MULTITHREAD_BRUTEFORCE
    vector<LoginThread*> vThread;
#endif
    bool loadPlugin(const char* f);
    void unloadPlugin();
public:		// Benutzer-Deklarationen
    Plugin* plug;
    __fastcall TInterface(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInterface *Interface;
//---------------------------------------------------------------------------
#endif
