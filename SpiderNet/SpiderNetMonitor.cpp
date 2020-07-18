#include "SpiderNetMonitor.h"
#include "SpiderNetContext.h"

namespace SpiderNet {




	Monitor::Monitor():
		version(0),
		check_version(0),
		source(0),
		destination(0)
	{}

	void Monitor::trigger(uint32 source, uint32 destination)
	{
        source = source;
        destination = destination;
        version++;
	}

	void Monitor::check(Context &context)
	{
        if (version == check_version) {
            if (destination) {
				context.solveEndless(destination);
				// send warning infomation!!!!    
            }
        }
        else check_version = version;
	}

}
