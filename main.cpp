#include "SpiderNetApplication.h"

using namespace SpiderNet;

int main() {
    
    Application app;
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