#ifndef SPIDERNETPREREQUISITES_H
#define SPIDERNETPREREQUISITES_H




#include "SpiderNetPlatform.h"


// cpp standar library
#include <atomic>
#include <cassert>
#include <exception>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace SpiderNet{

    struct Event;
}

#include "SpiderNetException.h"

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
