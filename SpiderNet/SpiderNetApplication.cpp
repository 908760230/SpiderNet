#include "SpiderNetApplication.h"

namespace SpiderNet
{

    const char *Application::load_config = "\
		local result = {}\n\
		local function getenv(name) return assert(os.getenv(name), [[os.getenv() failed: ]] .. name) end\n\
		local sep = package.config:sub(1,1)\n\
		local current_path = [[.]]..sep\n\
		local function include(filename)\n\
			local last_path = current_path\n\
			local path, name = filename:match([[(.*]]..sep..[[)(.*)$]])\n\
			if path then\n\
				if path:sub(1,1) == sep then	-- root\n\
					current_path = path\n\
				else\n\
					current_path = current_path .. path\n\
				end\n\
			else\n\
				name = filename\n\
			end\n\
			local f = assert(io.open(current_path .. name))\n\
			local code = assert(f:read [[*a]])\n\
			code = string.gsub(code, [[%$([%w_%d]+)]], getenv)\n\
			f:close()\n\
			assert(load(code,[[@]]..filename,[[t]],result))()\n\
			current_path = last_path\n\
		end\n\
		setmetatable(result, { __index = { include = include } })\n\
		local config_name = ...\n\
		include(config_name)\n\
		setmetatable(result, nil)\n\
		return result\n\
	";

    Application::Application()
    {

#ifdef LUA_CACHELIB
        // init the lock of code cache
        luaL_initcodecache();
#endif

        luaState = luaL_newstate();
    }

    void Application::run()
    {
        luaL_openlibs(luaState);

        int err = luaL_loadbufferx(luaState, load_config, strlen(load_config), "=[SpiderNet config]", "t");
        assert(err == LUA_OK);
        lua_pushstring(luaState, configFile);

        err = lua_pcall(luaState, 1, 1, 0);
        if (err)
        {
            fprintf(stderr, "%s\n", lua_tostring(luaState, -1));
            lua_close(luaState);
            exit(1);
        }
        _init_env(luaState);

        config.thread = optInt("thread", 8);
        config.modulePath = optString("cpath", "./cservice/?.so");
        config.harbor = optInt("harbor", 1);
        config.bootstrap = optString("bootstrap", "snlua bootstrap");
        config.daemon = optString("daemon", nullptr);
        config.logger = optString("logger", nullptr);
        config.logService = optString("logservice", "logger");
        config.profile = optBoolean("profile", 1);

        lua_close(luaState);

        std::cout<< config.thread <<" "<< config.modulePath<<" "<<config.harbor<<std::endl;

        start();
    }

    void Application::start()
    {

#if SPIDERNET_PLATFORM == SPIDERNET_PLATFORM_LINUX || SPIDERNET_PLATFORM == SPIDERNET_PLATFORM_UNIX
        sigign();
#endif

        // if (config.daemon)
        // {
        //     std::shared_ptr<Daemon> ptr_Daemon(new Daemon(config.daemon));
        //     if (ptr_Daemon == nullptr)
        //         SPIDERNET_EXCEPT(Exception::ERR_INVALID_STATE, "Cant create Daemon!!!");
        // }

        //Harbor harbor(config.harbor);
        //Handle handle(config.harbor);
        //MessageQueue *messageQueue = MessageQueue::getInstance();
        //moduleManager = new ModuleManager(config.modulePath);
        //Timer timer;
    }

    void Application::setConfig(const Config &cfg)
    {
        config.thread = cfg.thread;
        config.profile = cfg.profile;
        config.modulePath = cfg.modulePath;
        config.logService = cfg.logService;
        config.logger = cfg.logger;
        config.harbor = cfg.harbor;
        config.daemon = cfg.daemon;
        config.bootstrap = cfg.bootstrap;
    }

    int Application::optInt(const std::string &key, int opt)
    {
        const char *str = getEnv(key.c_str());
        if (str == NULL)
        {
            char tmp[20];
            sprintf(tmp, "%d", opt);
            setEnv(key.c_str(), tmp);
            return opt;
        }
        return strtol(str, NULL, 10);
    }

    bool Application::optBoolean(const char *key, int opt)
    {
        const char *str = getEnv(key);
        if (str == NULL)
        {
            setEnv(key, opt ? "true" : "false");
            return opt;
        }
        return strcmp(str, "true") == 0;
    }

    const char *Application::optString(const char *key, const char *opt)
    {
        const char *result = getEnv(key);
        if (result == nullptr)
        {
            if (opt != nullptr)
            {
                setEnv(key, opt);

                result = getEnv(key);
            }
        }
        return result;
    }

    const char *Application::getEnv(const char *key)
    {
        //获取全局变量的key的值,并将其放入栈顶
        lua_getglobal(luaState, key);
        const char *result = lua_tostring(luaState, -1);
        lua_pop(luaState, 1);

        return result;
    }

    void Application::setEnv(const char *key, const char *value)
    {
        lua_getglobal(luaState, key);
        assert(lua_isnil(luaState, -1));
        lua_pop(luaState, 1);
        lua_pushstring(luaState, value);
        lua_setglobal(luaState, key);
    }

    void Application::_init_env(lua_State *L)
    {
        lua_pushnil(L); /* first key */
        while (lua_next(L, -2) != 0)
        {
            int keyt = lua_type(L, -2);
            if (keyt != LUA_TSTRING)
            {
                fprintf(stderr, "Invalid config table\n");
                exit(1);
            }
            const char *key = lua_tostring(L, -2);
            if (lua_type(L, -1) == LUA_TBOOLEAN)
            {
                int b = lua_toboolean(L, -1);
                setEnv(key, b ? "true" : "false");
            }
            else
            {
                const char *value = lua_tostring(L, -1);
                if (value == NULL)
                {
                    fprintf(stderr, "Invalid config table key = %s\n", key);
                    exit(1);
                }
                setEnv(key, value);
            }
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

#if SPIDERNET_PLATFORM == SPIDERNET_PLATFORM_LINUX || SPIDERNET_PLATFORM == SPIDERNET_PLATFORM_UNIX
    int Application::sigign()
    {
        struct sigaction sa;
        sa.sa_handler = SIG_IGN;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGPIPE, &sa, 0);
        return 0;
    }
#endif

} // namespace SpiderNet