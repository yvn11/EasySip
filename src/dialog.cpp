/*
 * src/dialog.cpp
 */
#include "dialog.h"


namespace EasySip
{
	Dialog::Dialog(Dialog &dia)
	{
		*this = dia;
	}

	Dialog::Dialog(RequestMessage &in_msg)
	: secure_flag_(false), confirmed_(false)
	{
		if (false /*TODO: sent over TLS && in_msg.req_line_->request_uri_ has sip URI */)
		{
			secure_flag(true);
		}

		if (in_msg.record_route_.size())
		{
			routes(in_msg.record_route_);
			std::reverse(routes().begin(), routes().end());
		}
		else
		{
			routes().clear();
		}

		if (in_msg.cseq_.size())
		{
			remote_seq(*in_msg.cseq_.last());
		}
//		local_seq_ = UNSET;
		if (in_msg.call_id_.size())
		{
			id().call_id(*in_msg.call_id_.last());
		}

		if (in_msg.to_.size())
		{
			id().local_tag(in_msg.to_.last()->tag());
			local_uri(in_msg.to_.last()->uri());
		}

		if (in_msg.from_.size())
		{
			id().remote_tag(in_msg.from_.last()->tag());
			remote_uri(in_msg.from_.last()->uri());
		}
	}

	Dialog::Dialog(ResponseMessage &in_msg)
	: secure_flag_(false), confirmed_(false)
	{
		if (false /*TODO: sent over TLS && in_msg.req_line_->request_uri_ has sip URI */)
		{
			secure_flag(true);
		}

		if (in_msg.record_route_.size())
		{
			routes(in_msg.record_route_);
			std::reverse(routes().begin(), routes().end());
		}
		else
		{
			routes().clear();
		}

		for (auto &it : in_msg.contact_)
		{
			remote_target().append(it->cons());
		}

//		remote_seq(UNSET);
		if (in_msg.cseq_.size())
		{
			local_seq(*in_msg.cseq_.last());
		}
		if (in_msg.call_id_.size())
		{
			id().call_id(*in_msg.call_id_.last());
		}
		if (in_msg.to_.size())
		{
			id().remote_tag(in_msg.to_.last()->tag());
			remote_uri(in_msg.to_.last()->uri());
		}
		if (in_msg.from_.size())
		{
			id().local_tag(in_msg.from_.last()->tag());
			local_uri(in_msg.from_.last()->uri());
		}
	}

	std::ostream& operator<< (std::ostream &o, Dialog &dia)
	{
		return o << dia.id() 
			<< "local_seq: " << dia.local_seq()
			<< "remote_seq: " << dia.remote_seq()
			<< "local_uri: " << dia.local_uri() << '\n'
			<< "remote_uri: " << dia.remote_uri() << '\n'
			<< dia.remote_target()
			<< "secure_flag: " << dia.secure_flag() << '\n'
			<< dia.routes()
			<< "confirmation: " << (dia.is_confirmed() ? "true" : "false") << '\n';
	}

	Dialog* Dialogs::create_dialog()
	{
		append_item();
		std::cout << "dialogs size: [" << size() << "]\n";
		return last();
	}

	Dialog* Dialogs::create_dialog(Dialog &dialog)
	{
		append_item(dialog);
		std::cout << "dialogs size: [" << size() << "]\n";
		return last();
	}

	void Dialogs::cancel_dialog(DialogId val)
	{
		for (iterator it = begin(); it != end();)
		{
			if (val == (*it)->id())
			{
				erase(it);
				std::cout << "cancel dialog: \n[\n" << **it << "]\n";
				break;
			}
			else
			{
				it++;
			}
		}
		std::cout << "dialogs size: [" << size() << "]\n";
	}

	Dialog* Dialogs::get_dialog_by_id(DialogId &val)
	{
		for (iterator it = begin(); it != end(); it++)
		{
			if (val == (*it)->id())
			{
				return *it;
			}
		}

		return 0;
	}

	Dialog* Dialogs::operator[] (DialogId val)
	{
		return get_dialog_by_id(val);
	}


} // namespace EasySip
