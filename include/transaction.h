/*
 * include/transaction.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "utils.h"
#include "except.h"
#include "timer.h"

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

    class Fsm// : public Thread
    {
    protected:

//        MethodMapList allowed_methods_;
//        RespCodeList allowed_responses_;
//        SocketIp4UDP udp_;
        int state_;
        bool run_;
		Thread t_;

    public:
        Fsm(int s, bool r = true) : state_(s), run_(r)
        {
            setup();
            t_ = Thread(&Fsm::main_loop, this);
        }

        ~Fsm()
        {
			t_.join();
        }

        void run(bool r)
        {
            run_ = r;
        }

        bool run()
        {
            return run_;
        }

        int state()
        {
            return state_;
        }

        void state(int s)
        {
            state_ = s;
        }

        Fsm& setup()
        {
            return *this;
        }

        int loop()
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

            return PROCEDURE_OK;
        }
    };

    class Transaction : public Fsm
    {
    public:

        Transaction()
        : Fsm(T_FSM_CALLING)
        {
        }

    protected:

        virtual int loop();
    };

}; // namespace EasySip

