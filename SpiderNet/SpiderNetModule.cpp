#include "SpiderNetModule.h"

namespace SpiderNet
{

    Module::Module(Context *context, const char *param)
    {
        handle = dl_create();
        if (handle == nullptr)
            SPIDERNET_EXCEPT(Exception::ERR_INVALID_STATE, "Module handle couldn't be created!");
        dl_init(handle, context, param);
    }

    void Module::release()
    {
        dl_release(handle);
    }

    void Module::signal(int sig)
    {
        dl_signal(handle, sig);
    }

    ModuleManager::ModuleManager(std::string path) : path(path)
    {
    }

    void ModuleManager::insert(Module *module)
    {
        std::lock_guard<SpinLock> lk(mtx);
        Module *tmp = query(module->name);
        assert(tmp == nullptr);
        modules.emplace(make_pair(module->name, module));
    }

    Module *ModuleManager::query(const char *name)
    {
        std::lock_guard<SpinLock> lk(mtx);
        std::map<std::string, Module *>::iterator result = modules.find(name);
        if (result == modules.end())
            return nullptr;
        return result->second;
    }

    Module *ModuleManager::query(const std::string &name)
    {
        return query(name.c_str());
    }

    Module *ModuleManager::create(Context *context, const char *param)
    {
        Module *module = new Module(context, param);
        if (module == nullptr)
            SPIDERNET_EXCEPT(Exception::ERR_INVALID_STATE, "Module couldn't be created!");
        return module;
    }

    void ModuleManager::release(Module *module)
    {
        Module *result = query(module->name);
        if (result == module)
            modules.erase(module->name);
        module->release();
    }

} // namespace SpiderNet
