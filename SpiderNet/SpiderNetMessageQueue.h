#ifndef SPIDERNETMESSAGEQUEUE_H
#define SPIDERNETMESSAGEQUEUE_H

#include "../Common/SpiderNetPrerequisites.h"

#define MESSAGE_TYPE_SHIFT ((sizeof(size_t) - 1) * 8)

namespace SpiderNet
{

	// class MessageQueue
	// {
	// public:
	// 	MessageQueue(const MessageQueue &) = delete;
	// 	const MessageQueue &operator=(const const MessageQueue &) = delete;

	// 	void globalMsgPush(GlobalMessage *globalMsg);
	// 	GlobalMessage *globalMsgPop();

	// 	static MessageQueue *getInstance();

	// private:
	// 	MessageQueue();

	// 	SpinLock mtx;
	// 	static MessageQueue *instance;
	// 	std::queue<GlobalMessage *> globalMsgQueue;
	// };

} // namespace SpiderNet

#endif
