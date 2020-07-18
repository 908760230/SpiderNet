#ifndef spidernetsocket_h
#define spidernetsocket_h

#include "../Common/SpiderNetPrerequisites.h"

namespace SpiderNet
{

    class Socket
    {
    private:
        /* data */
    public:
        enum class SOCKET_PROTOCOL_TYPE
        {
            SOCKET_TCP,
            SOCKET_UDP,
            SOCKET_SCTP,
            SOCKET_UNKNOW
        };

    public:
        Socket(SOCKET_TYPE type);
        ~Socket();

        
    };

} // namespace SpiderNet

#endif