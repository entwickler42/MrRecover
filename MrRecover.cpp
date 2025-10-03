//---------------------------------------------------------------------------

#include <clx.h>
#pragma hdrstop
USEFORM("frmoptions.cpp", FormOptions);
USEFORM("main.cpp", Interface);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TInterface), &Interface);
         Application->CreateForm(__classid(TFormOptions), &FormOptions);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch(...)
    {
         try
         {
             throw Exception("");
         }
         catch(Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
