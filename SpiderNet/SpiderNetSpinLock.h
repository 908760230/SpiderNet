#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <atomic>

namespace SpiderNet {

	class SpinLock
	{
	public:
		SpinLock() = default;
		SpinLock(const SpinLock&) = delete;
		SpinLock& operator=(const SpinLock&) = delete;

		void lock();

		// has not been implemented yet!
		bool tryLock();
		void unlock();

	private:
		std::atomic_bool flag = false;
	};

}

#endif // !SPINLOCK_H


