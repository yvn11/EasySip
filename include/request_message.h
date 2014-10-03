/*
 * include/request_message.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "parameter.h"

namespace EasySip
{
    typedef CodeMap MethodMap;

    enum
    {
        METHOD_ID_INVITE,
        METHOD_ID_CANCEL,
        METHOD_ID_ACK,
        METHOD_ID_BYE,
        METHOD_ID_REGISTER,
        METHOD_ID_OPTIONS,
        METHOD_ID_SUBSCRIBE,
        METHOD_ID_NOTIFY,
        METHOD_ID_MESSAGE,
        METHOD_ID_INFO,
        METHOD_ID_UPDATE,
        METHOD_ID_REFER,
        METHOD_ID_PRACK,
    };

    // Requests since SIP 1.0
    // RFC-3261
    const MethodMap METHOD_INVITE(METHOD_ID_INVITE, "INVITE");
    const MethodMap METHOD_CANCEL(METHOD_ID_CANCEL, "CANCEL");
    const MethodMap METHOD_ACK(METHOD_ID_ACK, "ACK");
    const MethodMap METHOD_BYE(METHOD_ID_BYE, "BYE");
    const MethodMap METHOD_REGISTER(METHOD_ID_REGISTER, "REGISTER");
    const MethodMap METHOD_OPTIONS(METHOD_ID_OPTIONS, "OPTIONS");
    // Additional requests since SIP 2.0
    // RFC-6665
    const MethodMap METHOD_SUBSCRIBE(METHOD_ID_SUBSCRIBE, "SUBSCRIBE");
    const MethodMap METHOD_NOTIFY(METHOD_ID_NOTIFY, "NOTIFY");
    const MethodMap METHOD_MESSAGE(METHOD_ID_MESSAGE, "MESSAGE");
    // RFC-6086
    const MethodMap METHOD_INFO(METHOD_ID_INFO, "INFO");
    // RFC-3311
    const MethodMap METHOD_UPDATE(METHOD_ID_UPDATE, "UPDATE");
    // RFC-3515
    const MethodMap METHOD_REFER(METHOD_ID_REFER, "REFER");
    // RFC-3262
    const MethodMap METHOD_PRACK(METHOD_ID_PRACK, "PRACK");

    typedef std::set<MethodMap> MethodMapList;
} // namespace EasiSip
