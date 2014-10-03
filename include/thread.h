/*
 * include/thread.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <pthread.h>
#include "except.h"

namespace EasySip
{
//#ifndef _GNU_SOURCE
//#define _GNU_SOURCE
//#endif

    class ThrAttr
    {
    public:
        struct Stack
        {
            void *stackaddr_;
            size_t stacksize_;
        };

        struct SchedParam
        {
            int policy_;
            struct sched_param param_;
        };

    private:
        pthread_attr_t attr_;
        cpu_set_t cpuset_;
        Stack stack_;
        SchedParam schedparam_;

    public:

        ThrAttr()
        {
            if (0 > pthread_attr_init(&attr_))
                std::cerr << "pthread_attr_init: " << strerror(errno) << '\n';
        }

        ~ThrAttr()
        {
            if (0 > pthread_attr_destroy(&attr_))
                std::cerr << "pthread_attr_destroy: " << strerror(errno) << '\n';
        }

        pthread_attr_t& Attr()
        {
            return attr_;
        }

        cpu_set_t& affinity_np()
        {
            if (0 > pthread_attr_getaffinity_np(&attr_, sizeof(cpu_set_t), &cpuset_))
                std::cerr << "pthread_attr_getaffinity_np: " << strerror(errno) << '\n';

            return cpuset_;
        }

        ThrAttr& affinity_np(cpu_set_t cpuset)
        {
            cpuset_ = cpuset;

            if (0 > pthread_attr_setaffinity_np(&attr_, sizeof(cpu_set_t), &cpuset_))
                std::cerr << "pthread_attr_setaffinity_np: " << strerror(errno) << '\n';

            return *this;
        }

        int detachstate()
        {
            int detachstate;

            if (0 > pthread_attr_getdetachstate(&attr_, &detachstate))
                std::cerr << "pthread_attr_getdetachstate: " << strerror(errno) << '\n';

            return detachstate;
        }

        ThrAttr& detachstate(int detachstate)
        {
            if (0 > pthread_attr_setdetachstate(&attr_, detachstate))
                std::cerr << "pthread_attr_setdetachstate: " << strerror(errno) << '\n';

            return *this;
        }

        size_t guardsize()
        {
            size_t guardsize;

            if (0 > pthread_attr_getguardsize(&attr_, &guardsize))
                std::cerr << "pthread_attr_getguardsize: " << strerror(errno) << '\n';

            return guardsize;
        }

        ThrAttr& guardsize(size_t guardsize)
        {
            if (0 > pthread_attr_setguardsize(&attr_, guardsize))
                std::cerr << "pthread_attr_setguardsize: " << strerror(errno) << '\n';

            return *this;
        }

        int inheritsched()
        {
            int inheritsched;

            if (0 > pthread_attr_getinheritsched(&attr_, &inheritsched))
                std::cerr << "pthread_attr_getinheritsched: " << strerror(errno) << '\n';

            return inheritsched;
        }

        ThrAttr& inheritsched(int inheritsched)
        {
            if (0 > pthread_attr_setinheritsched(&attr_, inheritsched))
                std::cerr << "pthread_attr_setinheritsched: " << strerror(errno) << '\n';

            return *this;
        }

        SchedParam& schedparam()
        {
            if (0 > pthread_attr_getschedparam(&attr_, &schedparam_.param_))
                std::cerr << "pthread_attr_getschedparam: " << strerror(errno) << '\n';

            return schedparam_;
        }

        ThrAttr& schedparam(int priority)
        {
//            schedparam_.policy_ = policy;
            schedparam_.param_.sched_priority = priority;

            if (0 > pthread_attr_setschedparam(&attr_, &schedparam_.param_))
                std::cerr << "pthread_attr_setschedparam: " << strerror(errno) << '\n';

            return *this;
        }

        int schedpolicy()
        {
            int schedpolicy;

            if (0 > pthread_attr_getschedpolicy(&attr_, &schedpolicy))
                std::cerr << "pthread_attr_getschedpolicy: " << strerror(errno) << '\n';

            return schedpolicy;
        }

        ThrAttr& schedpolicy(int schedpolicy)
        {
            if (0 > pthread_attr_setschedpolicy(&attr_, schedpolicy))
                std::cerr << "pthread_attr_setschedpolicy: " << strerror(errno) << '\n';

            return *this;
        }

        int scope()
        {
            int scope;

            if (0 > pthread_attr_getscope(&attr_, &scope))
                std::cerr << "pthread_attr_getscope: " << strerror(errno) << '\n';

            return scope;
        }

        ThrAttr& scope(int scope)
        {
            if (0 > pthread_attr_setscope(&attr_, scope))
                std::cerr << "pthread_attr_setscope: " << strerror(errno) << '\n';

            return *this;
        }

        Stack& stack()
        {
            if (0 > pthread_attr_getstack(&attr_, &stack_.stackaddr_, &stack_.stacksize_))
                std::cerr << "pthread_attr_getstack: " << strerror(errno) << '\n';

            return stack_;
        }

        ThrAttr& stack(void *stackaddr, size_t stacksize)
        {
            stack_.stackaddr_ = &stackaddr;
            stack_.stacksize_ = stacksize;

            if (0 > pthread_attr_setstack(&attr_, stack_.stackaddr_, stack_.stacksize_))
                std::cerr << "pthread_attr_setstack: " << strerror(errno) << '\n';

            return *this;
        }
// ------------------------------------deprecated !----------------------------------------
//        void* stackaddr()
//        {
//            if (0 > pthread_attr_getstackaddr(&attr_, &stack_.stackaddr_))
//                std::cerr << "pthread_attr_getstackaddr: " << strerror(errno) << '\n';
//
//            return stack_.stackaddr_;
//        }
//
//        ThrAttr& stackaddr(void *stackaddr)
//        {
//            stack_.stackaddr_ = &stackaddr;
//
//            if (0 > pthread_attr_setstackaddr(&attr_, stack_.stackaddr_))
//                std::cerr << "pthread_attr_setstackaddr: " << strerror(errno) << '\n';
//
//            return *this;
//        }
// ++++++++++++++++++++++++++++++++++++deprecated !++++++++++++++++++++++++++++++++++++++++

        size_t stacksize()
        {
            if (0 > pthread_attr_getstacksize(&attr_, &stack_.stacksize_))
                std::cerr << "pthread_attr_getstacksize: " << strerror(errno) << '\n';

            return stack_.stacksize_;
        }

        ThrAttr& stacksize(size_t stacksize)
        {
            stack_.stacksize_ = stacksize;

            if (0 > pthread_attr_setstacksize(&attr_, stack_.stacksize_))
                std::cerr << "pthread_attr_setstacksize: " << strerror(errno) << '\n';

            return *this;
        }
    };

// Xdestroy            Xsetdetachstate     pthread_cleanup_push_defer_np   pthread_self
// Xgetaffinity_np     Xsetguardsize       pthread_create                  pthread_setaffinity_np
// Xgetdetachstate     Xsetinheritsched    pthread_detach                  pthread_setcancelstate
// Xgetguardsize       Xsetschedparam      pthread_equal                   pthread_setcanceltype
// Xgetinheritsched    Xsetschedpolicy     pthread_exit                    pthread_setconcurrency
// Xgetschedparam      Xsetscope           pthread_getaffinity_np          pthread_setschedparam
// Xgetschedpolicy     Xsetstack           pthread_getattr_np              pthread_setschedprio
// Xgetscope           Xsetstackaddr       pthread_getconcurrency          pthread_sigmask
// Xgetstack           Xsetstacksize       pthread_getcpuclockid           pthread_sigqueue
// Xgetstackaddr       pthread_cancel                  pthread_getschedparam           pthread_testcancel
// Xgetstacksize       pthread_cleanup_pop             pthread_join                    pthread_timedjoin_np
// Xinit               pthread_cleanup_pop_restore_np  pthread_kill                    pthread_tryjoin_np
// Xsetaffinity_np     pthread_cleanup_push            pthread_kill_other_threads_np   pthread_yield

    class ThrCondAttr
    {
    protected:
        pthread_condattr_t cattr_;

    public:
        ThrCondAttr()
        {
            if (0 > pthread_condattr_init(&cattr_))
                std::cerr << "pthread_condattr_init: " << strerror(errno) << '\n';
        }

        ~ThrCondAttr()
        {
            if (0 > pthread_condattr_destroy(&cattr_))
                std::cerr << "pthread_condattr_destroy: " << strerror(errno) << '\n';
        }

        pthread_condattr_t& Attr()
        {
            return cattr_;
        }
    };

    class Mutex
    {
        pthread_mutex_t mutex_;
    };

    class ThrCond
    {
        ThrCondAttr attr_;
        pthread_cond_t cond_;
        Mutex mutex_;

        ThrCond()
        {
            
        }

        ~ThrCond()
        {
        }
    };


    class Thread
    {
    protected:

        pthread_t id_;
        ThrAttr attr_;
        void* (*loop_) (void*);
        void *arg_;

    public:

		Thread() : loop_(0), arg_(0)
		{
		}

        Thread(void* (*loop) (void*), void* arg = 0)
        : loop_(loop), arg_(arg)
        {
            if (0 > pthread_create(&id_, &attr_.Attr(), loop_, arg_))
              std::cerr << "pthread_create: " << strerror(errno) << '\n';
        }

        ~Thread()
        {
        }

        pthread_t id()
        {
            return id_;
        }

//        Thread& add_cleanup(void (*routine)(void *), void *arg, int n)
//        {
//            pthread_cleanup_push(routine, arg)
//            pthread_cleanup_pop(n)
//            return *this;
//        }
        
        Thread& schedprio(int prio)
        {
            pthread_setschedprio(id_, prio);
            return *this;
        }

        Thread& concurrency(int c)
        {
            if (0 > pthread_setconcurrency(c))
                std::cerr << "pthread_setconcurrency: " << strerror(errno) << '\n';
            return *this;
        }

        int concurrency()
        {
            return pthread_getconcurrency();
        }

        friend bool operator== (Thread &a, Thread &b)
        {
            return pthread_equal(a.id(), b.id());
        }

        Thread& cancel()
        {
            if (0 > pthread_cancel(id_))
                std::cerr << "pthread_cancel: " << strerror(errno) << '\n';
            return *this;
        }

        int join()
        {
            void *ret;

            if (0 > pthread_join(id_, &ret))
                std::cerr << "pthread_join: " << strerror(errno) << '\n';
            std::cout << (char*)ret << '\n';    
            return 0;
        }
    };

    #define Thread(f, a) Thread((void* (*) (void*))f, (void*)a)

} // namespace EasySip

