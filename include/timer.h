/*
 * include/timer.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <sys/time.h>
#include <signal.h>
#include "except.h"

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
	bool operator== (struct itimerval &a, struct itimerval &b)
	{
		return timercmp(&a.it_interval, &b.it_interval, ==)
				&& timercmp(&a.it_value, &b.it_value, ==);
	}

	bool operator!= (struct itimerval &a, struct itimerval &b)
	{
		return !(timercmp(&a.it_interval, &b.it_interval, ==)
				&& timercmp(&a.it_value, &b.it_value, ==));
	}

	std::ostream& operator<< (std::ostream &o, struct timeval &a)
	{
		return o << "[" << a.tv_sec << ", " << a.tv_usec << "]";
	}

	std::ostream& operator<< (std::ostream &o, struct itimerval &a)
	{
		return o << a.it_value << " : " << a.it_interval;
	}

	void sigalrm_cb(int signo)
	{
		std::cout << "signo: " << signo << "\n";//" settimer: " << setitimer(ITIMER_REAL, 0, &it_a) << '\n';
		struct itimerval cur;

		if (0 <= getitimer(ITIMER_REAL, &cur))
				std::cout << cur << '\n';

//		timerclear(&cur.it_value);
//		timerclear(&cur.it_interval);
//		std::cout << cur << '\n';

		std::cout << "------------time's up-----------------\n";
	}

	class Timer
	{
		unsigned long value_; // in  ms
		struct itimerval itv_;
	
	public:

//		Timer(Timer &tm)
//		:value_(tm.value())
//		{
//		}
	
		Timer(unsigned long value)
		:value_(value)
		{
		}

		Timer(time_t sec, suseconds_t usec = 0)
		:value_(0)
		{
			signal(SIGALRM, sigalrm_cb);
		
			struct timeval tm_cur, tm_next;
		
			tm_cur.tv_sec = 1;
			tm_cur.tv_usec = 0;
		
			tm_next.tv_sec = sec;
			tm_next.tv_usec = usec;
		
			itv_.it_interval = tm_next;
			itv_.it_value = tm_cur;
		}
	
		Timer(std::string value)
		{
			value_ = time_string_to_ulong(value);
		}
	
		~Timer()
		{
		}
	
		void value(std::string value)
		{
			value_ = time_string_to_ulong(value);
		}
	
//		std::string value()
//		{
//			return timer_ulong_to_string(value_);
//		}
		unsigned long value()
		{
			return value_;
		}

		void value(unsigned long value)
		{
			value_ = value;
		}
	
		void start()
		{
			std::cout << "settimer: " << setitimer(ITIMER_REAL, &itv_, 0) << '\n';
//			struct itimerval cur;

//			while ((0 <= getitimer(ITIMER_REAL, &cur)) && itv_ != cur)
//				std::cout << cur << '\n';
//				std::cout << itv_ << '\n';
//				std::cout << cur << '\n';
//			std::cout << "------------time's up-----------------\n";
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
		// TODO	
		//	Timer operator()()
	};
	
	// built-in timers
	class T1_RTT : public Timer
	{
	public:

		typedef Timer Base;

		T1_RTT()
		: Timer("500ms")
		{
		}
	
		~T1_RTT()
		{
		}
	};
	
	class T2_MAX_RETRAN_INTV : public Timer
	{
	public:

		typedef Timer Base;

		T2_MAX_RETRAN_INTV()
		: Timer("4s")
		{
		}
	
		~T2_MAX_RETRAN_INTV()
		{
		}
	};
	
	class T4_MAX_DURATION_OF_MSG : public Timer
	{
	public:

		typedef Timer Base;

		T4_MAX_DURATION_OF_MSG()
		: Timer("5s")
		{
		}
	
		~T4_MAX_DURATION_OF_MSG()
		{
		}
	};
	
	class TA_INVITE_RETRAN_INTERVAL : public Timer
	{
	public:

		typedef Timer Base;

		TA_INVITE_RETRAN_INTERVAL()
		: Timer("500ms") // TODO: T1_RTT initial value
		{
		}
	
		~TA_INVITE_RETRAN_INTERVAL()
		{
		}
	};
	
	class TB_INVITE_TIMEOUT : public Timer
	{
	public:

		typedef Timer Base;

		TB_INVITE_TIMEOUT()
		: Timer(T1_RTT()*64) // TODO: T1_RTT*64
		{
		}
	
		~TB_INVITE_TIMEOUT()
		{
		}
	};
	
	class TC_PROXY_INVITE_TIMEOUT : public Timer
	{
	public:

		typedef Timer Base;

		TC_PROXY_INVITE_TIMEOUT()
		: Timer("4min") // TODO: > 3min
		{
		}
	
		~TC_PROXY_INVITE_TIMEOUT()
		{
		}

		void value(std::string value)
		{
			// TODO: check >3min
			Base::value(value);
		}
	};

	class TD_WAIT_FOR_RETRAN : public Timer
	{
	public:

		typedef Timer Base;

		TD_WAIT_FOR_RETRAN()
		: Timer("33s") // TODO: UDP: >32s, TCP/SCTP =0s
		{
		}
	
		~TD_WAIT_FOR_RETRAN()
		{
		}
	};

	class TE_NON_INVITE_RETRAN_INTV : public Timer
	{
	public:

		typedef Timer Base;

		TE_NON_INVITE_RETRAN_INTV()
		: Timer("500ms") // TODO: T1_RTT initial value
		{
		}
	
		~TE_NON_INVITE_RETRAN_INTV()
		{
		}
	};

	class TF_NON_INVITE_REQS_TIMEOUT : public Timer
	{
	public:

		typedef Timer Base;

		TF_NON_INVITE_REQS_TIMEOUT()
		: Timer(T1_RTT()*64) // TODO: T1_RTT*64
		{
		}
	
		~TF_NON_INVITE_REQS_TIMEOUT()
		{
		}
	};

	class TG_INVITE_RESP_RETRAN_INTV : public Timer
	{
	public:

		typedef Timer Base;

		TG_INVITE_RESP_RETRAN_INTV()
		: Timer("500ms") // TODO: T1_RTT initial value
		{
		}
	
		~TG_INVITE_RESP_RETRAN_INTV()
		{
		}
	};

	class TH_WAIT_FOR_ACK_RECEIPT : public Timer
	{
	public:

		typedef Timer Base;

		TH_WAIT_FOR_ACK_RECEIPT()
		: Timer(T1_RTT()*64) // TODO: T1_RTT*64
		{
		}
	
		~TH_WAIT_FOR_ACK_RECEIPT()
		{
		}
	};

	class TI_WAIT_FOR_ACK_RETRAN : public Timer
	{
	public:

		typedef Timer Base;

		TI_WAIT_FOR_ACK_RETRAN()
		: Timer(T4_MAX_DURATION_OF_MSG().value()) // TODO: UDP: T4, TCP/SCTP =0s
		{
		}
	
		~TI_WAIT_FOR_ACK_RETRAN()
		{
		}
	};

	class TJ_WAIT_FOR_NON_INVITE_REQS_RETRAN : public Timer
	{
	public:

		typedef Timer Base;

		TJ_WAIT_FOR_NON_INVITE_REQS_RETRAN()
		: Timer(T1_RTT()*64) // TODO: UDP: 64*T1, TCP/SCTP =0s
		{
		}
	
		~TJ_WAIT_FOR_NON_INVITE_REQS_RETRAN()
		{
		}
	};

	class TK_WAIT_FOR_RESP_RETRAN : public Timer
	{
	public:

		typedef Timer Base;

		TK_WAIT_FOR_RESP_RETRAN()
		: Timer(T4_MAX_DURATION_OF_MSG().value()) // TODO: UDP: 64*T1, TCP/SCTP =0s
		{
		}
	
		~TK_WAIT_FOR_RESP_RETRAN()
		{
		}
	};
} // namespace EasySip
