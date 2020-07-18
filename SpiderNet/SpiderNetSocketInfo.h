#ifndef SPIDERNETSOCKETINFO_H
#define SPIDERNETSOCKETINFO_H

#include "../Common/SpiderNetPrerequisites.h"
namespace SpiderNet
{

    struct SocketInfo
    {
        /* data */
    };

    struct socket
    {
        uintptr_t opaque;
        struct wb_list high;
        struct wb_list low;
        int64_t wb_size;
        struct socket_stat stat;
        volatile uint32 sending;
        int fd;
        int id;
        uint8 protocol;
        uint8 type;
        uint16 udpconnecting;
        int64 warn_size;
        union
        {
            int size;
            uint8 udp_address[UDP_ADDRESS_SIZE];
        } p;
        spinlock    mtx;
        int dw_offset;
        const void *dw_buffer;
        size_t dw_size;
    };
} // namespace SpiderNet

#endif