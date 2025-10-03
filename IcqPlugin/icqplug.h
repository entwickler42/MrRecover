#ifndef ICQPLUG_H
#define ICQPLUG_H

#include <Plugin.h>

extern "C" Plugin* __pascal __export init_plugin();
extern "C" void __pascal __export unload_plugin();

//---------------------------------------------------------------------------
class ICQPlugin : public Plugin
{
    public:
        ICQPlugin();

        bool login(const char* user, const char* pass, const char* host, unsigned int port);
};

#endif
