#ifndef SPIDERNETCONFIGFILE_H
#define SPIDERNETCONFIGFILE_H

#include "SpiderNetPrerequisites.h"

namespace SpiderNet {

	struct Config{
		int thread;
		int harbor;
		int profile;
		const char * daemon;
		const char * modulePath;
		const char * bootstrap;
		const char * logger;
		const char * logService;

		enum class THEAD_TYPE{
			THREAD_WORKER,
			THREAD_MAIN,
			THREAD_SOCKET,
			THREAD_TIMER,
			THREAD_MONITOR
		};

	};


}


#endif