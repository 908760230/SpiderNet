#ifndef SPIDERNETPLUGIN_H
#define SPIDERNETPLUGIN_H

#include "SpiderNetPrerequisites.h"

namespace SpiderNet {


	class Plugin
	{
	public:
		Plugin() {};
		virtual ~Plugin(){}

		virtual const std::string& getName() const = 0;

		virtual void install() = 0;

		virtual void initialise() = 0;

		virtual void shutdown() = 0;

		virtual void uninstall() = 0;
	};


}


#endif



