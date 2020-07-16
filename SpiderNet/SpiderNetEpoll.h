#ifndef SPIDERNETEPOLL_H
#define SPIDERNETEPOLL_H

#include "../Common/SpiderNetPrerequisites.h"

namespace SpiderNet{

    class Epoll
    {
    public:
        Epoll(){};
        ~Epoll(){};

        bool invalid(int fd);
        int  create();
        void release(int fd);
        int add(int fd, int sock, void *ud);
        void del(int fd, int sock);
        void write(int, int sock, void *ud, bool enable);
        int  wait(int, Event *e, int max);
        void nonblocking(int sock);
    };

}

#endif