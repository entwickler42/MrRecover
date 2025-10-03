//---------------------------------------------------------------------------

#ifndef frmoptionsH
#define frmoptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QExtCtrls.hpp>
#include <QGraphics.hpp>
#include <QButtons.hpp>
#include <QComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TImage *ImageBG;
    TSpeedButton *SpeedButton1;
    TTrackBar *Threads;
    TLabel *Label1;
    TCheckBox *UF;
    TCheckBox *UL;
    void __fastcall SpeedButton1Click(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
    __fastcall TFormOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
