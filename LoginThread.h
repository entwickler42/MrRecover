#ifndef LOGINTHREAD_H
#define LOGINTHREAD_H

#include <clx.h>
#include <vector>
#include "Plugin.h"

using namespace std;

class LoginThread : public TThread
{
    public:
        static bool run;

        LoginThread(const AnsiString& user, const vector<AnsiString>& vWord, const AnsiString& host, unsigned int port = 110);
        void __fastcall Execute();

    private:
        unsigned int port;
        AnsiString user, host;
        vector<AnsiString> vWord;
};

#endif

