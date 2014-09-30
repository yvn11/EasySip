/*
 * include/Element/element.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "message.h"
#include "socket.h"
#include "dialog.h"
#include <signal.h>
#include <queue>
#include <thread>

namespace EasySip
{
	enum
	{
		T_FSM_CALLING,
		T_FSM_TRYING,
		T_FSM_PROCEEDING,
		T_FSM_COMPLETED,
		T_FSM_TERMINATED,
	};

	class Element
	{
	protected:

		MethodMapList allowed_methods_;
		RespCodeList allowed_responses_;
		SocketIp4UDP udp_;

		bool run_;
		Dialogs dialogs_;
		std::queue<std::string> msgq_;
	
		bool stateful_;
	
	private:

		void init_allowed_methods();
		void init_allowed_responses();

	public:

		Element();

		~Element();

		void run(bool r)
		{
			run_ = r;
		}

		bool run()
		{
			return run_;
		}

		bool stateful()
		{
			return stateful_;
		}

		void stateful(bool s)
		{
			stateful_ = s;
		}

		virtual int fetch_msg();
		virtual int start();
		virtual int on_receive_message(std::string &msg);
		virtual int on_receive_req(std::string &msg, const int code);
		virtual int on_receive_resp(std::string &msg, const int code);

		virtual int invite_request();
		virtual int register_request();
		virtual int bye_request();
		virtual int cancel_request();
		virtual int update_request();
		virtual int info_request();
		virtual int ack_request();
		virtual int message_request();
		virtual int subscribe_request();
		virtual int notify_request();
		virtual int refer_request();
		virtual int options_request();
		virtual int prack_request();

		virtual int on_invite_request(RequestMessage &in_msg);
		virtual int on_register_request(RequestMessage &in_msg);
		virtual int on_bye_request(RequestMessage &in_msg);
		virtual int on_ack_request(RequestMessage &in_msg);
		virtual int on_cancel_request(RequestMessage &in_msg);
		virtual int on_options_request(RequestMessage &in_msg);
		virtual int on_refer_request(RequestMessage &in_msg);
		virtual int on_subscribe_request(RequestMessage &in_msg);
		virtual int on_notify_request(RequestMessage &in_msg);
		virtual int on_message_request(RequestMessage &in_msg);
		virtual int on_info_request(RequestMessage &in_msg);
		virtual int on_prack_request(RequestMessage &in_msg);
		virtual int on_update_request(RequestMessage &in_msg);

		virtual void send_msg(RequestMessage &msg);
		virtual void send_msg(ResponseMessage &msg);

		virtual void echo(RequestMessage &in_msg);
		virtual void simple_response(const RespCode &rc, RequestMessage &in_msg);

		template<typename T>
		int dialog_preprocess(Dialog &dialog, T &in_msg)
		{
			if (!dialogs_[dialog.id()])
			{
				// TODO: configurable reject/accept
				if (true)
				{
					simple_response(SIP_RESPONSE_CALL_OR_TRANSACTION_NOT_EXIST, in_msg);
					return MESSAGE_PROCESSED;
				}
				else
				{
					// TODO: restruct dialog
				}
			}

			return PROCEDURE_OK;
		}
	};

} // namespace EasySip
