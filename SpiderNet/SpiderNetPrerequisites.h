#ifndef SPIDERNETPREREQUISITES_H
#define SPIDERNETPREREQUISITES_H

#include "SpiderNetPlatform.h"

// cpp standar library
#include <cassert>
#include <chrono>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <signal.h>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

#include <thread>
#include <vector>

#define PTYPE_TEXT 0
#define PTYPE_RESPONSE 1
#define PTYPE_MULTICAST 2
#define PTYPE_CLIENT 3
#define PTYPE_SYSTEM 4
#define PTYPE_HARBOR 5
#define PTYPE_SOCKET 6
// read lualib/skynet.lua examples/simplemonitor.lua
#define PTYPE_ERROR 7
// read lualib/skynet.lua lualib/mqueue.lua lualib/snax.lua
#define PTYPE_RESERVED_QUEUE 8
#define PTYPE_RESERVED_DEBUG 9
#define PTYPE_RESERVED_LUA 10
#define PTYPE_RESERVED_SNAX 11

#define PTYPE_TAG_DONTCOPY 0x10000
#define PTYPE_TAG_ALLOCSESSION 0x20000

namespace SpiderNet
{

    class Application;
    class Config;
    class Console;
    class Context;
    class Daemon;
    class Exception;
    class Handle;
    class Logger;
    class MessageQueue;
    class Module;
    class Monitor;
    class Node;
    class RemoteMessage;
    class Server;
    class SocketMessage;
    class SocketServer;
    class Timer;
    class UDPAddress;
    struct Event;
    class SpinLock;

    struct Message
    {
        void *data;
        uint32 handle;
        uint32 source;
        int session;
        size_t sz;
    };
} // namespace SpiderNet

#include "SpiderNetException.h"
#include "SpiderNetSpinLock.h"

#if SPIDERNET_PLATFORM == SPIDERNET_PLATFORM_WINDOWS
#include <Windows.h>
#include <WinSock2.h>
#elif SPIDERNET_PLATFORM == SPIDERNET_PLATFORM_LINUX

#include <netdb.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#endif

#endif
