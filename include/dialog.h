/*
 * include/dialog.h
 */
#include "message.h"
#include <algorithm>

namespace EasySip
{
    class DialogId
    {
        HFCallId call_id_;
        std::string local_tag_;
        std::string remote_tag_;

    public:
        DialogId(HFCallId& id, std::string ltag, std::string rtag)
        : call_id_(id), local_tag_(ltag), remote_tag_(rtag)
        {
        }

        DialogId()
        {
        }

        HFCallId& call_id()
        {
            return call_id_;
        }

        std::string& local_tag()
        {
            return local_tag_;
        }
    
        std::string& remote_tag()
        {
            return remote_tag_;
        }
    
        void call_id(HFCallId val)
        {
            call_id_ = val;
        }

        void local_tag(std::string val)
        {
            local_tag_ = val;
        }
    
        void remote_tag(std::string val)
        {
            remote_tag_ = val;
        }
    
        friend bool operator== (DialogId a, DialogId b)
        {
            if (a.call_id() == b.call_id())
                if (a.local_tag() == b.local_tag())
                    if (a.remote_tag() == b.remote_tag())
                        return true;

            return false;
        }

        friend std::ostream& operator<< (std::ostream &o, DialogId id)
        {
            return o << id.call_id()
                << "local_tag: " << id.local_tag() << '\n'
                << "remote_tag: " << id.remote_tag() << '\n';
        }
    };

    class Dialog
    {
        DialogId id_;
        HFCSeq local_seq_;
        HFCSeq remote_seq_;
        std::string local_uri_;
        std::string remote_uri_;
        ContactList remote_target_;
        bool secure_flag_;
        PtsOf<HFRecordRoute> routes_;

        bool confirmed_;
        bool still_ringing_;

    public:

        Dialog()
        : secure_flag_(false), confirmed_(false),
         still_ringing_(false)
        {
        }

        Dialog(Dialog &dia);
        Dialog(ResponseMessage &in_msg);
        Dialog(RequestMessage &in_msg);

        DialogId& id()
        {
            return id_;
        }

        HFCSeq& local_seq()
        {
            return local_seq_;
        }

        HFCSeq& remote_seq()
        {
            return remote_seq_;
        }

        std::string& local_uri()
        {
            return local_uri_;
        }

        std::string& remote_uri()
        {
            return remote_uri_;
        }

        ContactList& remote_target()
        {
            return remote_target_;
        }

        bool& secure_flag()
        {
            return secure_flag_;
        }

        PtsOf<HFRecordRoute>& routes()
        {
            return routes_;
        }
        
        void id(DialogId val)
        {
            id_ = val;
        }

        void local_seq(HFCSeq val)  
        {
            local_seq_ = val;
        }

        void remote_seq(HFCSeq val)  
        {
            remote_seq_ = val;
        }

        void local_uri(std::string val) 
        {
            local_uri_ = val;
        }

        void remote_uri(std::string val) 
        {
            remote_uri_ = val;
        }

        void remote_target(ContactList val) 
        {
            remote_target_ = val;
        }

        void secure_flag(bool val)    
        {
            secure_flag_ = val;
        }

        void routes(PtsOf<HFRecordRoute> val) 
        {
            routes_ = val;
        }

        void is_confirmed(bool c)
        {
            confirmed_ = c;
        }

        bool is_confirmed()
        {
            return confirmed_;
        }

        bool still_ringing()
        {
            return still_ringing_;
        }

        void still_ringing(bool ring)
        {
            still_ringing_ = ring;
        }

        friend std::ostream& operator<< (std::ostream &o, Dialog &dia);
    };

    class Dialogs : public PtsOf<Dialog>
    {
    public:

        Dialog* create_dialog();
        Dialog* create_dialog(Dialog &dialog);

        void cancel_dialog(DialogId val);

        Dialog* get_dialog_by_id(DialogId &val);

        Dialog* operator[] (DialogId val);
    };
} // namespace EasySip
        
          
          
          
          
          
          
          
  
