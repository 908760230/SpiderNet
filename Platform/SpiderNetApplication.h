#ifndef SPIDERNETAPPLICATION_H
#define SPIDERNETAPPLICATION_H

#include "../Common/SpiderNetPrerequisites.h"

namespace SpiderNet
{

    class Application
    {
    public:
        Application(){};
        virtual ~Application(){};
        

        virtual void run() = 0;

    private:

    };

} // namespace SpiderNet

#endif
