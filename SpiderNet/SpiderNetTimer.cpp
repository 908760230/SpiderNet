#include "SpiderNetTimer.h"
#include "SpiderNetContext.h"
#include "SpiderNetMessageQueue.h"

using namespace std::chrono;

namespace SpiderNet
{

	Timer::Timer() : current(0),
					 time(0),
					 startTime(0),
					 currentPoint(0)
	{
		time_point<steady_clock, microseconds> tmp = time_point_cast<microseconds>(steady_clock::now());
		startTime = tmp.time_since_epoch().count() / 100000;
		current = tmp.time_since_epoch().count();
		int i, j;
		for (i = 0; i < TIME_NEAR; i++)
		{
			linkClear(&near[i]);
		}

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < TIME_LEVEL; j++)
			{
				linkClear(&(t[i][j]));
			}
		}
	}

	int Timer::timeout(uint32 handle, int time, int session)
	{
		if (time <= 0)
		{
			Message *message = new Message;
			message->source = 0;
			message->session = session;
			message->data = NULL;
			message->sz = (size_t)PTYPE_RESPONSE << MESSAGE_TYPE_SHIFT;

			if (Context::push(handle, message))
			{
				return -1;
			}
		}
		else
		{
			TimerEvent *event = new TimerEvent;
			event->handle = handle;
			event->session = session;
			add(event, time);
		}

		return session;
	}

	void Timer::update()
	{
		// try to dispatch timeout 0 (rare condition)
		execute();
		// shift time first, and then dispatch timer message
		shift();
		execute();
	}

	uint32 Timer::start()
	{
		return startTime;
	}

	uint64 Timer::threadTime()
	{
		return uint64();
	}

	TimerNode *Timer::linkClear(LinkList *list)
	{
		TimerNode *ret = list->head.next;
		list->head.next = nullptr;
		list->tail = &(list->head);
		return ret;
	}

	void Timer::link(LinkList *list, TimerNode *node)
	{
		list->tail->next = node;
		list->tail = node;
		node->next = nullptr;
	}

	void Timer::addNode(TimerNode *node)
	{
		uint32 time = node->expire;
		uint32 current_time = this->time;

		if ((time | TIME_NEAR_MASK) == (current_time | TIME_NEAR_MASK))
		{
			link(&(near[time & TIME_NEAR_MASK]), node);
		}
		else
		{
			int i;
			uint32 mask = TIME_NEAR << TIME_LEVEL_SHIFT;
			for (i = 0; i < 3; i++)
			{
				if ((time | (mask - 1)) == (current_time | (mask - 1)))
				{
					break;
				}
				mask <<= TIME_LEVEL_SHIFT;
			}

			link(&(t[i][((time >> (TIME_NEAR_SHIFT + i * TIME_LEVEL_SHIFT)) & TIME_LEVEL_MASK)]), node);
		}
	}

	void Timer::add(TimerEvent *event, int time)
	{
		TimerNode *node = new TimerNode;
		node->event = event;
		std::lock_guard<SpinLock> lock(mtx);
		node->expire = time + this->time;
		addNode(node);
	}

	void Timer::moveList(int level, int idx)
	{
		TimerNode *current = linkClear(&t[level][idx]);
		while (current)
		{
			TimerNode *tmp = current->next;
			addNode(current);
			current = tmp;
		}
	}

	void Timer::shift()
	{
		int mask = TIME_NEAR;
		uint32 ct = ++this->time;
		if (ct == 0)
		{
			moveList(3, 0);
		}
		else
		{
			uint32 time = ct >> TIME_NEAR_SHIFT;
			int i = 0;

			while ((ct & (mask - 1)) == 0)
			{
				int idx = time & TIME_LEVEL_MASK;
				if (idx != 0)
				{
					moveList(i, idx);
					break;
				}
				mask <<= TIME_LEVEL_SHIFT;
				time >>= TIME_LEVEL_SHIFT;
				++i;
			}
		}
	}

	void Timer::dispatchList(TimerNode *current)
	{
		do
		{
			TimerEvent *event = current->event;
			Message *message = new Message;
			message->source = 0;
			message->session = event->session;
			message->data = NULL;
			message->sz = (size_t)PTYPE_RESPONSE << MESSAGE_TYPE_SHIFT;

			Context::push(event->handle, message);

			TimerNode *temp = current;
			current = current->next;
			delete temp;
		} while (current);
	}

	void Timer::execute()
	{
		int idx = time & TIME_NEAR_MASK;

		while (near[idx].head.next)
		{
			TimerNode *current = linkClear(&near[idx]);
			std::lock_guard<SpinLock> lock(mtx);
			// dispatch_list don't need lock T
			dispatchList(current);
		}
	}

} // namespace SpiderNet
