#ifndef SPIDERNETMODULE_H
#define SPIDERNETMODULE_H

#include "SpiderNetPrerequisites.h"

namespace SpiderNet
{

    typedef void *(*spidernet_dl_create)(void);
    typedef int (*spidernet_dl_init)(void *inst, Context *context, const char *parm);
    typedef void (*spidernet_dl_release)(void *inst);
    typedef void (*spidernet_dl_signal)(void *inst, int signal);

    class Module
    {

    public:
        Module(Context *context, const char *param);

        void release();
        void signal(int signal);

    public:
        std::string name;

    private:
        spidernet_dl_create dl_create;
        spidernet_dl_init dl_init;
        spidernet_dl_release dl_release;
        spidernet_dl_signal dl_signal;

        void *handle;
    };

    class ModuleManager
    {
    private:
        std::map<std::string, Module *> modules;
        std::string path;
        SpinLock mtx;

    public:
        ModuleManager(std::string path);

        ModuleManager(const ModuleManager &) = delete;
        ModuleManager &operator=(const ModuleManager &) = delete;

        ~ModuleManager(){};

        void insert(Module *module);
        Module *query(const char *name);
        Module *query(const std::string &name);
        Module *create(Context *context, const char *param);
        void release(Module *module);
    };

} // namespace SpiderNet

#endif
