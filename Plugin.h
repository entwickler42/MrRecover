#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>

using namespace std;

//---------------------------------------------------------------------------
class Plugin
{
    public:
        Plugin(const string& name = "", const string& server = "", unsigned int port = 0)
        {
            plugin_name     = name;
            default_server  = server;
            default_port    = port;
        };

        virtual bool login(const char* user, const char* pass, const char* host, unsigned int port)
        {
            return false;
        };

        string plugin_name, default_server;
        unsigned int default_port;
};

#endif
