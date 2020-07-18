#include "SpiderNetHandle.h"
#include "SpiderNetContext.h"

namespace SpiderNet
{

    HandleStorage *Handle::handleData = nullptr;

    Handle::Handle(int harbor)
    {
        assert(handleData == nullptr);
        handleData = new HandleStorage;
        handleData->slot_size = 4;
        handleData->slot = (Context **)malloc(handleData->slot_size * sizeof(Context *));
        memset(handleData->slot, 0, handleData->slot_size * sizeof(Context *));

        //rwlock_init(&s->lock);
        // reserve 0 for system
        handleData->harbor = (uint32_t)(harbor & 0xff) << HANDLE_REMOTE_SHIFT;
        handleData->handle_index = 1;
        handleData->name_cap = 2;
        handleData->name_count = 0;
        handleData->name = (HandleName *)malloc(handleData->name_cap * sizeof(HandleName));
    }

    uint32 Handle::resgister(Context *ctx)
    {
        //rwlock_wlock(&s->lock);

        for (;;)
        {
            int i;
            uint32_t handle = handleData->handle_index;
            for (i = 0; i < handleData->slot_size; i++, handle++)
            {
                if (handle > HANDLE_MASK)
                {
                    // 0 is reserved
                    handle = 1;
                }
                int hash = handle & (handleData->slot_size - 1);
                if (handleData->slot[hash] == NULL)
                {
                    handleData->slot[hash] = ctx;
                    handleData->handle_index = handle + 1;

                    //rwlock_wunlock(&s->lock);

                    handle |= handleData->harbor;
                    return handle;
                }
            }
            assert((handleData->slot_size * 2 - 1) <= HANDLE_MASK);
            Context **new_slot = (Context **)malloc(handleData->slot_size * 2 * sizeof(Context *));
            memset(new_slot, 0, handleData->slot_size * 2 * sizeof(struct skynet_context *));
            for (i = 0; i < handleData->slot_size; i++)
            {
                int hash = handleData->slot[i]->getHandle() & (handleData->slot_size * 2 - 1);
                assert(new_slot[hash] == nullptr);
                new_slot[hash] = handleData->slot[i];
            }
            free(handleData->slot);
            handleData->slot = new_slot;
            handleData->slot_size *= 2;
        }
    }

    int Handle::retire(uint32 handle)
    {
        return 0;
    }

} // namespace SpiderNet
