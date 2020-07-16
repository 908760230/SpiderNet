#ifndef SPIDERNETAPPLICATION_H
#define SPIDERNETAPPLICATION_H

#include "../Common/SpiderNetPrerequisites.h"
#include "SpiderNetConfig.h"
#include "../ThirdParty/lua/lua.hpp"

namespace SpiderNet
{
    class Application
    {
    public:
        Application();
        Application(const Application &) = delete;
        const Application &operator=(const Application &) = delete;

        void run();

        void start();

        void setConfig(const Config &config);

    private:
        int optInt(const std::string &key, int opt);

        bool optBoolean(const char *key, int opt);

        const char *optString(const char *key, const char *opt);

        const char *getEnv(const char *key);

        void setEnv(const char *key, const char *value);

        void _init_env(lua_State *L);

#if SPIDERNET_PLATFORM == SPIDERNET_PLATFORM_LINUX || SPIDERNET_PLATFORM == SPIDERNET_PLATFORM_UNIX
        int sigign();
#endif

    private:
        Config config;
        const char *configFile = "config.lua";
        lua_State *luaState;
        static const char *load_config;
        SpinLock mtx;
        //ModuleManager *moduleManager;
        //MessageQueue *globalMessageQueue;
    };

} // namespace SpiderNet

#endif
