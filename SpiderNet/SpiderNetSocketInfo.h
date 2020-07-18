#ifndef SPIDERNETSOCKETINFO_H
#define SPIDERNETSOCKETINFO_H

#include "SpiderNetPrerequisites.h"
namespace SpiderNet
{

    struct Event
    {
        void *s;
        bool read;
        bool write;
        bool error;
        bool eof;
    };
    struct SocketMessage
    {
        int id;
        uintptr_t opaque;
        int ud; // for accept, ud is new connection id ; for data, ud is size of data
        char *data;
    };

    enum class SOCKET_PROTOCOL_TYPE
    {
        SOCKET_TCP,
        SOCKET_UDP,
        SOCKET_SCTP,
        SOCKET_UNKNOW
    };
    struct SocketState
    {
        uint64 rtime;
        uint64 wtime;
        uint64 read;
        uint64 write;
    };

    struct WriteBuffer
    {
        const void *buffer;
        char *ptr;
        size_t sz;
        bool userobject;
        uint8 udp_address[19];
    };

    typedef std::list<std::shared_ptr<WriteBuffer>> WriteBufferList;

    struct SocketData
    {
        uintptr_t opaque;
        WriteBufferList high;
        WriteBufferList low;
        int64 wb_size;
        SocketState stat;
        volatile uint32 sending;
        int fd;
        int id;
        SOCKET_PROTOCOL_TYPE protocol;
        uint8 type;
        uint16 udpconnecting;
        int64 warn_size;
        union {
            int size;
            uint8 udp_address[19];
        } p;
        SpinLock mtx;
        int dw_offset;
        const void *dw_buffer;
        size_t dw_size;
    };

    struct SocketObject
    {
        const void *(*buffer)(const void *);
        size_t (*size)(const void *);
        void (*free)(void *);
    };
    enum class SOCKET_BUFFER_TYPE
    {
        MEMORY,
        OBJECT,
        RAWPOINTER
    };

    struct SocketSendBuffer
    {

        int id;
        SOCKET_BUFFER_TYPE type;
        const void *buffer;
        size_t sz;
    };

    // -------------------------------------------------------------------
    //                      request  package
    //--------------------------------------------------------------------

    struct RequestOpen
    {
        int id;
        int port;
        uintptr_t opaque;
        char host[1];
    };

    struct RequestSend
    {
        int id;
        size_t sz;
        const void *buffer;
    };

    struct RequestSendUDP
    {
        RequestSend send;
        uint8 address[19];
    };

    struct RequestSetUDP
    {
        int id;
        uint8 address[19];
    };

    struct RequestClose
    {
        int id;
        int shutdown;
        uintptr_t opaque;
    };

    struct RequestListen
    {
        int id;
        int fd;
        uintptr_t opaque;
        char host[1];
    };

    struct RequestBind
    {
        int id;
        int fd;
        uintptr_t opaque;
    };

    struct RequestStart
    {
        int id;
        uintptr_t opaque;
    };

    struct RequestSetOpt
    {
        int id;
        int what;
        int value;
    };

    struct RequestUDP
    {
        int id;
        int fd;
        int family;
        uintptr_t opaque;
    };

    /*
	The first byte is TYPE

	S Start socket从另开哦时
	L Listen socket
	K Close socket
	O Connect to (Open)
	X Exit
	D Send package (high)
	P Send package (low)
	A Send UDP package
	T Set opt
	U Create UDP socket
	C set udp address
	Q query info
 */

    struct RequestPackage
    {
        uint8 header[8]; // 6 bytes dummy
        union {
            char buffer[256];
            RequestOpen open;
            RequestSend send;
            RequestSendUDP send_udp;
            RequestClose close;
            RequestListen listen;
            RequestBind bind;
            RequestStart start;
            RequestSetOpt setopt;
            RequestUDP udp;
            RequestSetUDP set_udp;
        } u;
        uint8 dummy[256];
    };

    union SocketAddress {
        sockaddr s;
        sockaddr_in v4;
        sockaddr_in6 v6;
    };

    struct SendObject
    {
        const void *buffer;
        size_t sz;
        void (*free_func)(void *);
    };

} // namespace SpiderNet

#endif