#ifndef SPIDERNETLINUX_H
#define SPIDERNETLINUX_H


#include "SpiderNetApplication.h"

namespace SpiderNet{

    class Linux : public Application
    {
        public:
        Linux();
        virtual void run() override;
    };
}


#endif
