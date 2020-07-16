#ifndef spidernetsocket_h
#define spidernetsocket_h

#include "SpiderNetPrerequisites.h"

namespace SpiderNet
{

    class Socket
    {
    private:
        /* data */
    public:
        enum class SOCKET_TYPE
        {
            SOCKET_TCP,
            SOCKET_UDP,
            SOCKET_SCTP,
            SOCKET_UNKNOW
        };

    public:
        Socket(SOCKET_TYPE type,unsigned int port,);
        ~Socket();
    };

} // namespace SpiderNet

#endif