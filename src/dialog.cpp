/*
 * src/dialog.cpp
 */
#include "dialog.h"


namespace EasySip
{
	std::ostream& operator<< (std::ostream &o, Dialog &dia)
	{
		return o << dia.id() 
			<< "local_seq: " << dia.local_seq()
			<< "remote_seq: " << dia.remote_seq()
			<< "local_uri: " << dia.local_uri() << '\n'
			<< "remote_uri: " << dia.remote_uri() << '\n'
			<< dia.remote_target()
			<< "secure_flag:" << dia.secure_flag() << '\n'
			<< dia.routes();
	}

	Dialog* Dialogs::create_dialog()
	{
		append_item();
		return last();
	}

	void Dialogs::cancel_dialog(DialogId val)
	{
		for (iterator it = begin(); it != end();)
		{
			if (val == (*it)->id())
			{
				erase(it);
				std::cout << "cancel: -------------\n" << **it;
				break;
			}
			else
			{
				it++;
			}
		}
	}

	Dialog* Dialogs::get_dialog_by_id(DialogId val)
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

	Dialog& Dialogs::operator[] (DialogId val)
	{
		return *get_dialog_by_id(val);
	}


} // namespace EasySip
