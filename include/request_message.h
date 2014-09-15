/*
 * include/request_message.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "mapper.h"

namespace EasySip
{
	class Method;
	class InviteMethod;
	class AckMethod;
	class RegisterMethod;
	class CancelMethod;
	class ByeMethod;
	class UpdateMethod;
	class PrackMethod;
	class NotifyMethod;
	class SubscribeMethod;
	class InfoMethod;
	class OptionsMethod;
	class ReferMethod;
	class MessageMethod;

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
	const MethodMap/*<InviteMethod>*/ METHOD_INVITE(METHOD_ID_INVITE, "INVITE");
	const MethodMap/*<CancelMethod>*/ METHOD_CANCEL(METHOD_ID_CANCEL, "CANCEL");
	const MethodMap/*<AckMethod>*/ METHOD_ACK(METHOD_ID_ACK, "ACK");
	const MethodMap/*<ByeMethod>*/ METHOD_BYE(METHOD_ID_BYE, "BYE");
	const MethodMap/*<RegisterMethod>*/ METHOD_REGISTER(METHOD_ID_REGISTER, "REGISTER");
	const MethodMap/*<OptionsMethod>*/ METHOD_OPTIONS(METHOD_ID_OPTIONS, "OPTIONS");
	// Additional requests since SIP 2.0
	// RFC-6665
	const MethodMap/*<SubscribeMethod>*/ METHOD_SUBSCRIBE(METHOD_ID_SUBSCRIBE, "SUBSCRIBE");
	const MethodMap/*<NotifyMethod>*/ METHOD_NOTIFY(METHOD_ID_NOTIFY, "NOTIFY");
	const MethodMap/*<MessageMethod>*/ METHOD_MESSAGE(METHOD_ID_MESSAGE, "MESSAGE");
	// RFC-6086
	const MethodMap/*<InfoMethod>*/ METHOD_INFO(METHOD_ID_INFO, "INFO");
	// RFC-3311
	const MethodMap/*<UpdateMethod>*/ METHOD_UPDATE(METHOD_ID_UPDATE, "UPDATE");
	// RFC-3515
	const MethodMap/*<ReferMethod>*/ METHOD_REFER(METHOD_ID_REFER, "REFER");
	// RFC-3262
	const MethodMap/*<PrackMethod>*/ METHOD_PRACK(METHOD_ID_PRACK, "PRACK");

	typedef std::set<MethodMap> MethodMapList;
} // namespace EasiSip
