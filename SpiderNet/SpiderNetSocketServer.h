#ifndef SPIDERNETSOCKETSERVER_H
#define SPIDERNETSOCKETSERVER_H

#include "SpiderNetSocketInfo.h"

namespace SpiderNet
{

    class SockerServer
    {
    public:
        SockerServer(uint64 time);
        ~SockerServer();

        void updateTime(uint64);
        void pool(SocketMessage *result, int more);
        void exit();
        void close(uintptr_t opaque, int id);
        void shutdown(uintptr_t opaque, int id);
        void start(uintptr_t opaque, int id);

        // return -1 when error
        int send(SocketSendBuffer *buffer);
        int sendLowPriority(SocketSendBuffer *buffer);

            // ctrl command below returns id
            int listen(uintptr_t opaque, const char *addr, int port, int backlog);
        int connect(uintptr_t opaque, const char *addr, int port);
        int bind(uintptr_t opaque, int fd);

        // for tcp
        void nodelay(int id);

        int getAddress() {}

        int getSocketInfo() {}

    private:
        volatile uint64_t time;
        int recvctrl_fd;
        int sendctrl_fd;
        int checkctrl;
        int event_fd;
        int alloc_id;
        int event_n;
        int event_index;
        SocketObject socketObject;
        Event events[64];
        socket slot[65536];
        char buffer[128];
        uint8_t udpbuffer[65535];
        fd_set rfds;
    };
} // namespace SpiderNet

#endif