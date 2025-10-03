#ifndef POP3PLUGIN_H
#define POP3PLUGIN_H

#include <Plugin.h>

extern "C" Plugin* __pascal __export init_plugin();
extern "C" void __pascal __export unload_plugin();

class POP3Plugin : public Plugin
{
    public:
        POP3Plugin();

        bool login(const char* user, const char* pass, const char* host, unsigned int port);        
};

#endif
 