#ifndef SPIDERNETHARBOR_H
#define SPIDERNETHARBOR_H

#include "../Common/SpiderNetPrerequisites.h"

#define GLOBALNAME_LENGTH 16
#define REMOTE_MAX 256

namespace SpiderNet
{

	struct RemoteMessage
	{
		char name[GLOBALNAME_LENGTH];
		uint32 handle;
		const void *message;
		size_t sz;
		int type;
	};

	class Harbor
	{
	public:
		Harbor(int harbor);
		bool isRemoteMessage(uint32 handle);
		void send(RemoteMessage *msg, uint32 source, int session);
		void start(Context *ctx);

	private:
		int invalidType(int type)
		{
			return 0; //type != PTYPE_SYSTEM && type != PTYPE_HARBOR;
		}

	private:
		Context *remoteContext = nullptr;
		unsigned int HARBOR = ~0;
	};

} // namespace SpiderNet

#endif
