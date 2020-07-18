#ifndef SPIDERNETCONTEXT_H
#define SPIDERNETCONTEXT_H

#include "SpiderNetPrerequisites.h"

namespace SpiderNet
{
	typedef int (*CallBackFunction)(Context *context, void *ud, int type, int session, uint32 source, const void *msg, size_t sz);

	class Context
	{
	public:
		Context(const char *name, const char *parm);

		int total();
		void grab();
		void reserve();
		uint32 getHandle();

		void send(RemoteMessage *msg, size_t sz, uint32 source, int type, int session);
		void solveEndless(uint32 handle);
		int newSession();
		MessageQueue *messageDispatch(Monitor *monitor, MessageQueue *msgQueue, int weight); // return next queue
		void dispatchAll();
		static int push(uint32 handle, Message *message);

	private:
		void *instance;
		Module *mod;
		void *cb_ud;
		CallBackFunction cb;
		MessageQueue *queue;
		FILE *logfile;
		uint64 cpu_cost;  // in microsec
		uint64 cpu_start; // in microsec
		char result[32];
		uint32 handle;
		int session_id;
		int ref;
		int message_count;
		bool init;
		bool endless;
		bool profile;
	};

} // namespace SpiderNet

#endif
