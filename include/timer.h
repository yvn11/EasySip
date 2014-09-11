/*
 * include/timer.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "except.h"

namespace EasySip
{
	class Timer
	{
		unsigned long value_; // in  ms
	
	public:

		Timer(Timer &tm)
		:value_(tm.Value())
		{
		}
	
		Timer(unsigned long value)
		:value_(value)
		{
		}
	
		Timer(std::string value)
		{
			value_ = time_string_to_ulong(value);
		}
	
		~Timer()
		{
		}
	
		void Value(std::string value)
		{
			value_ = time_string_to_ulong(value);
		}
	
		std::string Value()
		{
			return timer_ulong_to_string(value_);
		}
	
		void Start()
		{
			// TODO: start timer
		}
	
		static unsigned long time_string_to_ulong(std::string value)
		{
			// TODO: string value -> long value
			
		}
	
		static unsigned long time_ulong_to_string(unsigned long value)
		{
			// TODO: string value <- long value
		}
	
		unsigned long operator* (unsigned long val)
		{
			return (time_string_to_ulong(value_)*val);
		}
		// TODO	
		//	Timer operator()()
	};
	
	// built-in timers
	class T1_Rtt : public Timer
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

		void Value(std::string value)
		{
			// TODO: check >3min
			Base::Value(value);
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
		: Timer(T4_MAX_DURATION_OF_MSG().Value()) // TODO: UDP: T4, TCP/SCTP =0s
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
		: Timer(T4_MAX_DURATION_OF_MSG().Value()) // TODO: UDP: 64*T1, TCP/SCTP =0s
		{
		}
	
		~TK_WAIT_FOR_RESP_RETRAN()
		{
		}
	};
} // namespace EasySip
