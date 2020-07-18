#ifndef SPIDERNETMONITOR_H
#define SPIDERNETMONITOR_H

#include "SpiderNetPrerequisites.h"

namespace SpiderNet
{

	struct Monitor
	{
		std::atomic_int version;
		int check_version;
		uint32 source;
		uint32 destination;

		Monitor();
		void trigger(uint32 source, uint32 destination);
		void check(Context &context);
	};
} // namespace SpiderNet

#endif
