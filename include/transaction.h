/*
 * include/transaction.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <sys/time.h>
#include <signal.h>

#include "utils.h"
#include "except.h"

namespace EasySip
{
	enum
	{
		T_FSM_CALLING,
		T_FSM_TRYING,
		T_FSM_PROCEEDING,
		T_FSM_COMPLETED,
		T_FSM_CONFIRMED,
		T_FSM_TERMINATED,
	};


	class Fsm
	{
	protected:
		int state_;
		bool run_;

	public:
		Fsm(int s, bool r = true) : state_(s), run_(r)
		{
			setup();
			main_loop();
		}

		~Fsm()
		{
		}

		int state()
		{
			return state;
		}

		void state(int s)
		{
			state_ = s;
		}

		virtual Fsm& setup()
		{
			return *this;
		}

		virtual int loop()
		{
			return (run_ = false);
		}

		int main_loop()
		{
			while (run_)
			{
				if (loop() == PROCEDURE_ERROR)
					return PROCEDURE_ERROR;
			}

			return PROCEDURE_OK,
		}
	};

	class InviteTransaction : Fsm
	{
	public:

		InviteTransaction()
		: Fsm(T_FSM_CALLING)
		{
		}

	protected:

		virtual int loop()
		{
			switch (state_)
			{
				case T_FSM_CALLING:
				{
					// setup t1
					// send message
					break;
				}
				case T_FSM_TRYING:
				{
					break;
				}
				case T_FSM_PROCEEDING:
				{
					break;
				}
				case T_FSM_COMPLETED:
				{
					break;
				}
				case T_FSM_CONFIRMED:
				{
					break;
				}
				case T_FSM_TERMINATED:
				{
					break;
				}
				default:
				{
					return PROCEDURE_ERROR;
				}
			}

			return PROCEDURE_OK,
		}
	};

	class NonInviteTransaction : Fsm
	{
	public:

		InviteTransaction()
		: Fsm(T_FSM_TRYING)
		{
		}

	protected:

		virtual int loop()
		{
			switch (state_)
			{
				case T_FSM_CALLING:
				{
					break;
				}
				case T_FSM_TRYING:
				{
					break;
				}
				case T_FSM_PROCEEDING:
				{
					break;
				}
				case T_FSM_COMPLETED:
				{
					break;
				}
				case T_FSM_CONFIRMED:
				{
					break;
				}
				case T_FSM_TERMINATED:
				{
					break;
				}
				default:
				{
					return PROCEDURE_ERROR;
				}
			}

			return PROCEDURE_OK,
		}
	};
}; // namespace EasySip

