/*
 * include/timer.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <sys/time.h>
#include <signal.h>
#include "thread.h"

namespace EasySip
{
    /*
     * void timeradd(struct timeval *a, struct timeval *b, struct timeval *res);
     * 
     * void timersub(struct timeval *a, struct timeval *b, struct timeval *res);
     * 
     * void timerclear(struct timeval *tvp);
     * 
     * int timerisset(struct timeval *tvp);
     * 
     * int timercmp(struct timeval *a, struct timeval *b, CMP);
     */
    extern bool operator== (struct itimerval &a, struct itimerval &b);
    extern bool operator!= (struct itimerval &a, struct itimerval &b);
    extern std::ostream& operator<< (std::ostream &o, struct timeval &a);
    extern std::ostream& operator<< (std::ostream &o, struct itimerval &a);
    extern std::ostream& operator<< (std::ostream &o, struct timespec &a);
    extern std::ostream& operator<< (std::ostream &o, struct itimerspec &a);

//    void sigalrm_cb(int signo)
//    {
//        std::cout << "------------time's up-----------------\n";
//        std::cout << "signo: " << signo << "\n";//" settimer: " << setitimer(ITIMER_REAL, 0, &it_a) << '\n';
//        struct itimerval cur;
//
//        if (0 <= getitimer(ITIMER_REAL, &cur))
//                std::cout << cur << '\n';
//
////        timerclear(&cur.it_value);
////        timerclear(&cur.it_interval);
////        std::cout << cur << '\n';
//
//        std::cout << "++++++++++++time's up+++++++++++++++++\n";
//    }
//
//    void sigev_notify_cb(union sigval sigev_value)
//    {
//        std::cout << "------------time's up-----------------\n";
//        std::cout << "sigval.sival_int: [" << sigev_value.sival_int << "]\n";
////        std::cout << "timer id: [" << *(time_t*)data << "]\n";
//        std::cout << "++++++++++++time's up+++++++++++++++++\n";
//    }

    class Timer
    {
        unsigned long value_; // in  ms
        struct itimerval itv_;
    
    public:

        typedef Timer Base;

        Timer(unsigned long value)//unsigned long value /* ms */)
        :value_(value)
        {
//            signal(SIGALRM, sigalrm_cb);

            time_t sec = value_/1000;
            suseconds_t usec = (value_ % 1000) * 1000;

               itimev(sec, usec); 
        }

        Timer(time_t sec, suseconds_t usec = 0)
        :value_(sec*1000 + usec/1000)
        {
//            signal(SIGALRM, sigalrm_cb);
//            signal(SIGVTALRM, sigalrm_cb);
//            signal(SIGPROF, sigalrm_cb);

               itimev(sec, usec); 
        }
   
           Timer& itimev(time_t sec, suseconds_t usec = 0)
        {
            itv_.it_interval.tv_sec = sec;
            itv_.it_interval.tv_usec = usec;
            itv_.it_value.tv_sec = sec;
            itv_.it_value.tv_usec = usec;

            return *this;
        }

        Timer(std::string value)
        {
            value_ = time_string_to_ulong(value);
            time_t sec = value_/1000;
            suseconds_t usec = (value_ % 1000) * 1000;
               itimev(sec, usec); 
        }
    
        ~Timer()
        {
        }
    
        void value(std::string value)
        {
            value_ = time_string_to_ulong(value);
        }
    
//        std::string value()
//        {
//            return timer_ulong_to_string(value_);
//        }

        unsigned long value()
        {
            return value_;
        }

        void value(unsigned long value)
        {
            value_ = value;
        }

//        ITIMER_REAL    decrements in real time, and delivers SIGALRM upon expiration.
//        ITIMER_VIRTUAL decrements only when the process is executing, and delivers SIGVTALRM upon expiration.
//        ITIMER_PROF    decrements both when the process executes and when the system is executing on behalf of
//                        the process. Coupled with ITIMER_VIRTUAL, this timer is usually used to profile the
//                        time spent by the application in user and kernel space.  SIGPROF is delivered upon expiration.
//
//       CLOCK_REALTIME
//              A settable system-wide real-time clock.
//       CLOCK_MONOTONIC
//              A nonsettable monotonically increasing clock that measures time from some unspecified point in the past
//              that does not change after system startup.
//       CLOCK_PROCESS_CPUTIME_ID (since Linux 2.6.12)
//              A clock that measures (user and system) CPU time consumed by (all of the threads in) the calling process.
//       CLOCK_THREAD_CPUTIME_ID (since Linux 2.6.12)
//              A clock that measures (user and system) CPU time consumed by the calling thread.

//       int timer_create(clockid_t clockid, struct sigevent *sevp, timer_t *timerid);
//       int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value, struct itimerspec * old_value);
//       int timer_gettime(timer_t timerid, struct itimerspec *curr_value);

        virtual void start()
        {
//--------------------------------------------------------------------------------------
            int t_id = ITIMER_REAL;//VIRTUAL;

            std::cout << "settimer: " << setitimer(t_id, &itv_, 0) << '\n';
            struct itimerval cur;

            getitimer(t_id, &cur);

            std::cout << itv_ << "|" << cur << '\n';
//--------------------------------------------------------------------------------------
//            int ret;
//            timer_t tm_id;
//
//            struct sigevent sevp;
//            sevp.sigev_notify = SIGEV_THREAD;
//            sevp.sigev_notify_function = sigev_notify_cb;
//            sevp.sigev_value.sival_ptr = &tm_id;
//
//            if (0 > (ret = timer_create(CLOCK_REALTIME, &sevp, &tm_id)))
//                std::cout << "timer_create: " << ret << ' ' << strerror(errno) << '\n';
//
//           std::cout << "tm_id: [" << tm_id << "]\n";
//
//           struct itimerspec itspec;
//
//           itspec.it_value.tv_sec = 3;
//           itspec.it_value.tv_nsec = 0;
//           itspec.it_interval.tv_sec = 3;
//           itspec.it_interval.tv_nsec = 0;
//
//           if (0 > (ret = timer_settime(tm_id, 0, &itspec, 0)))
//              std::cout << "timer_settime: " << ret << ' ' << strerror(errno) << '\n';
//
//           std::cout << "itspec: [" << itspec << "]\n";
//
//           struct itimerspec itscur;
//
//           if (0 > (ret = timer_gettime(tm_id, &itscur)))
//              std::cout << "timer_gettime: " << ret << ' ' << strerror(errno) << '\n';
//            
//           std::cout << "itscur: [" << itscur << "]\n";
//--------------------------------------------------------------------------------------
        }
    
        static unsigned long time_string_to_ulong(std::string value)
        {
            // TODO: string value -> long value
            return 0;
        }
    
        static unsigned long time_ulong_to_string(unsigned long value)
        {
            // TODO: string value <- long value
            return 0;
        }
    
        unsigned long operator* (unsigned long val)
        {
            return (value_*val);
        }
    };
   
    // built-in timers
    class T1 : public Timer
    {
    public:

        T1() : Timer("500")//ms")
        {
        }
    };
    
    class T2 : public Timer
    {
    public:

        T2() : Timer("4000")
        {
        }
    };
    
    class T4 : public Timer
    {
    public:

        T4() : Timer("5000")
        {
        }
    };
    
    // INVITE_RETRAN_INTERVAL
    class TA : public Timer
    {
    public:

        TA() : Timer(T1().value())//ms") // TODO: T1 initial value
        {
        }
    };
    
    class TB : public Timer
    {
    public:

        TB() : Timer(T1()*64) // TODO: T1*64
        {
        }
    };
    
    class TC : public Timer // 4min
    {
    public:

        TC() : Timer((unsigned long)4*60*1000) // TODO: > 3min
        {
        }
    
        void value(std::string value)
        {
            // TODO: check >3min
            Base::value(value);
        }
    };

    class TD : public Timer
    {
    public:

        TD() : Timer("33000") // TODO: UDP: >32s, TCP/SCTP =0s
        {
        }
    };

    class TE : public Timer
    {
    public:

        TE() : Timer("500") // TODO: T1 initial value
        {
        }
    };

    class TF : public Timer
    {
    public:

        TF() : Timer(T1()*64) // TODO: T1*64
        {
        }
    };

    class TG : public Timer
    {
    public:

        TG() : Timer("500ms") // TODO: T1 initial value
        {
        }
    };

    class TH : public Timer
    {
    public:

        TH() : Timer(T1()*64) // TODO: T1*64
        {
        }
    };

    class TI : public Timer
    {
    public:

        TI() : Timer(T4().value()) // TODO: UDP: T4, TCP/SCTP =0s
        {
        }
    };

    class TJ : public Timer
    {
    public:

        TJ() : Timer(T1()*64) // TODO: UDP: 64*T1, TCP/SCTP =0s
        {
        }
    };

    class TK : public Timer
    {
    public:

        TK() : Timer(T4().value()) // TODO: UDP: 64*T1, TCP/SCTP =0s
        {
        }
    };
} // namespace EasySip
