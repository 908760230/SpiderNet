#include "SpiderNetSpinLock.h"

namespace SpiderNet {


	void SpinLock::lock()
	{
        while (flag.exchange(true, std::memory_order_acquire));
	}

	bool SpinLock::tryLock()
	{
		return false;
	}

	void SpinLock::unlock()
	{
		flag.store(false, std::memory_order_release);
	}


}