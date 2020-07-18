#ifndef SPIDERNETDAEMON_H
#define SPIDERNETDAEMON_H

#include "../Common/SpiderNetPrerequisites.h"

namespace SpiderNet
{

    class Daemon
    {
    public:
        Daemon(const char *pidfile);
        ~Daemon();

    private:
        int checkPID(const char *pidFile);
        int wirtePID(const char *pidFile);
        int redirectFds();
    };

} // namespace SpiderNet

#endif
