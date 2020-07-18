#include "SpiderNetHarbor.h"
#include "SpiderNetContext.h"
#include "SpiderNetHandle.h"

namespace SpiderNet
{

	Harbor::Harbor(int harbor)
	{
		HARBOR = (unsigned int)harbor << HANDLE_REMOTE_SHIFT;
	}

	bool Harbor::isRemoteMessage(uint32 handle)
	{
		assert(HARBOR != ~0);
		int value = (handle & !HANDLE_MASK);
		return value != HARBOR && value != 0;
	}

	void Harbor::send(RemoteMessage *msg, uint32 source, int session)
	{
		assert(invalidType(msg->type) && remoteContext);
		remoteContext->send(msg, sizeof(*msg), source, PTYPE_SYSTEM, session);
	}

	void Harbor::start(Context *ctx)
	{
		// the HARBOR must be reserved to ensure the pointer is valid.
		// It will be released at last by calling skynet_harbor_exit
		ctx->reserve();
		remoteContext = ctx;
	}

} // namespace SpiderNet
