#include "SpiderNetDaemon.h"

namespace SpiderNet {



    Daemon::Daemon(const char * pidFile)
    {
        int pid = checkPID(pidFile);
        if (pid) {

        }
    }

    Daemon::~Daemon()
    {
    }

    int Daemon::checkPID(const char * pidFile){
        
    }

    int Daemon::wirtePID(const char * pidFile)
    {
        return 0;
    }

    int Daemon::redirectFds()
    {
        return 0;
    }


}


