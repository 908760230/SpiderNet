#ifndef SPIDERNETTIMER_H
#define SPIDERNETTIMER_H

#include "SpiderNetPrerequisites.h"

namespace SpiderNet
{

    typedef void (*TimerExecuteFunc)(void *ud, void *arg);

#define TIME_NEAR_SHIFT 8
#define TIME_NEAR (1 << TIME_NEAR_SHIFT)
#define TIME_LEVEL_SHIFT 6
#define TIME_LEVEL (1 << TIME_LEVEL_SHIFT)
#define TIME_NEAR_MASK (TIME_NEAR - 1)
#define TIME_LEVEL_MASK (TIME_LEVEL - 1)

    struct TimerEvent
    {
        uint32 handle = 0;
        int session = 0;
    };

    struct TimerNode
    {
        TimerNode *next = nullptr;
        uint32 expire = 0;
        TimerEvent *event = nullptr;
    };

    struct LinkList
    {
        TimerNode head;
        TimerNode *tail = nullptr;
    };

    class Timer
    {
    public:
        Timer();
        Timer(const Timer &) = delete;
        const Timer &operator=(const Timer &) = delete;

        int timeout(uint32 handle, int time, int session);
        void update();
        uint32 start();
        uint64 threadTime();
        uint64 now();

    private:
        TimerNode *linkClear(LinkList *list);
        void link(LinkList *list, TimerNode *node);
        void addNode(TimerNode *node);
        void add(TimerEvent *event, int time);
        void moveList(int level, int idx);
        void shift();
        void dispatchList(TimerNode *current);
        void execute();

    private:
        SpinLock mtx;
        uint32 time;
        uint32 startTime;
        uint64 current;
        uint64 currentPoint;

        LinkList near[TIME_NEAR];
        LinkList t[4][TIME_LEVEL];
    };

} // namespace SpiderNet

#endif
