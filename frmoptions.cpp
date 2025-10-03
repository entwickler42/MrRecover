//---------------------------------------------------------------------------

#include <clx.h>
#pragma hdrstop

#include "frmoptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.xfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::SpeedButton1Click(TObject *Sender)
{
    Hide();    
}
//---------------------------------------------------------------------------
