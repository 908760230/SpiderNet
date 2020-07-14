#ifndef SPIDERNETWINDOWS_H
#define SPIDERNETWINDOWS_H

#include "SpiderNetApplication.h"
#include <Windows.h>

namespace SpiderNet
{

    class Windows : public Application
    {
    private:
        /* data */
    public:
        Windows(/* args */){};
        ~Windows(){};

        virtual void run() override;
    };

} // namespace SpiderNet

#endif