#ifndef SPIDERNETHANDLE_H
#define SPIDERNETHANDLE_H

#include "../Common/SpiderNetPrerequisites.h"

// reserve high 8 bits for remote id
#define HANDLE_MASK 0xffffff
#define HANDLE_REMOTE_SHIFT 24

namespace SpiderNet
{

	struct HandleName
	{
		char *name;
		uint32 handle;
	};

	struct HandleStorage
	{
		//struct rwlock lock;

		uint32 harbor;
		uint32 handle_index;
		int slot_size;
		Context **slot;
		int name_cap;
		int name_count;
		HandleName *name;
	};

	class Handle
	{
	public:
		Handle(int harbor);
		Handle(const Handle &) = delete;

		uint32 resgister(Context *ctx);
		int retire(uint32 handle);
		Context *grab(uint32 handle);
		void retireAll();
		uint32 findName(const char *name);
		const char *nameHandle(uint32 handle, const char *name);

	private:
		Context *context;
		static HandleStorage *handleData;
	};

} // namespace SpiderNet

#endif
