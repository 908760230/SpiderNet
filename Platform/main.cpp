#include "SpiderNetLinux.h"
#include "SpiderNetWindows.h"

using namespace SpiderNet;

int main() {
    

#if SPIDERNET_PLATFORM  == SPIDERNET_PLATFORM_WINDOWS
    Application &app = Windows();
#elif SPIDERNET_PLATFORM  == SPIDERNET_PLATFORM_LINUX
    Application &app = Linux;
#endif

    try
    {
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}