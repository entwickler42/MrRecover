#ifndef FTP_OLUG_H
#define FTP_OLUG_H

#include <Plugin.h>

class FTPPlugin : public Plugin
{
    public:
        FTPPlugin();

        bool login(const char* user, const char* pass, const char* host, unsigned int port);
};

extern "C" Plugin* __pascal __export init_plugin();
extern "C" void __pascal __export unload_plugin();

#endif
 