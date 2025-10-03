#include "icqplug.h"
#include "libicq.h"

//---------------------------------------------------------------------------
ICQPlugin::ICQPlugin() : Plugin("ICQ Plugin 1.0","64.12.161.185",5190)
{}

//---------------------------------------------------------------------------
bool ICQPlugin::login(const char* user, const char* pass, const char* host, unsigned int port)
{
    return ICQ_login(user,pass) ;
}

//---------------------------------------------------------------------------
static ICQPlugin plugin;

Plugin* __pascal init_plugin()
{
    return &plugin;
}

void __pascal unload_plugin()
{}
