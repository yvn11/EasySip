/*
 * include/thread.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include <pthread.h>

namespace EasySip
{
	class Thread
	{
	protected:

		pthread_t id_;
		pthread_attr_t attr_;
		void* (*routine_) (void*);
		void *arg_;

	public:

		Thread();

		~Thread();

		
	};

} // namespace EasySip


