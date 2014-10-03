/*
 * src/transaction.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "transaction.h"

namespace EasySip
{
    int Transaction::loop()
    {
        switch (state_)
        {
            case T_FSM_CALLING:
            {
                T1 t1;
                //element_.invite_request();
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
            //    return PROCEDURE_ERROR;
            }
        }

        return PROCEDURE_OK;
    }
}; // namespace EasySip
