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
    class Message;
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
