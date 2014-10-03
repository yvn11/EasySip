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
#include "timer.h"
#include "Element/element.h"

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

//        MethodMapList allowed_methods_;
//        RespCodeList allowed_responses_;
//        SocketIp4UDP udp_;
        Element element_;
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

            return PROCEDURE_OK;
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

        virtual int loop();
    };

    class NonInviteTransaction : Fsm
    {
    public:

        NonInviteTransaction()
        : Fsm(T_FSM_TRYING)
        {
        }

    protected:

        virtual int loop();
    };
}; // namespace EasySip

