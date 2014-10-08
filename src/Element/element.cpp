/*
 * src/Element/element.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Element/element.h"

namespace EasySip
{
    Element::Element()
    : run_(true), stateful_(false)
    {
        HeaderFields::init_allowed_fields();
        init_allowed_methods();
        init_allowed_responses();
    }

    Element::~Element()
    {
    }

    void Element::init_allowed_methods()
    {
        allowed_methods_.insert(METHOD_INVITE);
        allowed_methods_.insert(METHOD_CANCEL);
        allowed_methods_.insert(METHOD_ACK);
        allowed_methods_.insert(METHOD_BYE);
        allowed_methods_.insert(METHOD_REGISTER);
        allowed_methods_.insert(METHOD_OPTIONS);
        allowed_methods_.insert(METHOD_SUBSCRIBE);
        allowed_methods_.insert(METHOD_NOTIFY);
        allowed_methods_.insert(METHOD_MESSAGE);
        allowed_methods_.insert(METHOD_INFO);
        allowed_methods_.insert(METHOD_UPDATE);
        allowed_methods_.insert(METHOD_REFER);
        allowed_methods_.insert(METHOD_PRACK);
    }

    void Element::init_allowed_responses()
    {
        allowed_responses_.insert(SIP_RESPONSE_TRYING);
        allowed_responses_.insert(SIP_RESPONSE_RINGING);
        allowed_responses_.insert(SIP_RESPONSE_FORWARDING);
        allowed_responses_.insert(SIP_RESPONSE_QUEUED);
        allowed_responses_.insert(SIP_RESPONSE_SESSION_PROGRESS);
        allowed_responses_.insert(SIP_RESPONSE_SUCCESSFUL);
        allowed_responses_.insert(SIP_RESPONSE_ACCEPTED);
        allowed_responses_.insert(SIP_RESPONSE_MULTI_CHOICES);
        allowed_responses_.insert(SIP_RESPONSE_MOVE_PERM);
        allowed_responses_.insert(SIP_RESPONSE_MOVE_TEMP);
        allowed_responses_.insert(SIP_RESPONSE_USE_PROXY);
        allowed_responses_.insert(SIP_RESPONSE_ALTER_SERVICE);
        allowed_responses_.insert(SIP_RESPONSE_BAD_REQUEST);
        allowed_responses_.insert(SIP_RESPONSE_UNAUTHORIZED);
        allowed_responses_.insert(SIP_RESPONSE_REQUIRE_PAYMENT);
        allowed_responses_.insert(SIP_RESPONSE_FORBIDDEN);
        allowed_responses_.insert(SIP_RESPONSE_NOT_FOUND);
        allowed_responses_.insert(SIP_RESPONSE_METHOD_NOT_ALLOWED);
        allowed_responses_.insert(SIP_RESPONSE_NOT_ACCEPTABLE);
        allowed_responses_.insert(SIP_RESPONSE_REQUIRE_PROXY_AUTHENTICATION);
        allowed_responses_.insert(SIP_RESPONSE_REQUIRE_REQUEST_TIMEOUT);
        allowed_responses_.insert(SIP_RESPONSE_RESOURCE_NOT_AVAIL);
        allowed_responses_.insert(SIP_RESPONSE_REQUEST_ENTITY_TOO_LARGE);
        allowed_responses_.insert(SIP_RESPONSE_REQUEST_URI_TOO_LONG);
        allowed_responses_.insert(SIP_RESPONSE_UNSUPPORTED_MEDIA_TYPE);
        allowed_responses_.insert(SIP_RESPONSE_UNSUPPORTED_URI_SCHEME);
        allowed_responses_.insert(SIP_RESPONSE_BAD_EXTENSION);
        allowed_responses_.insert(SIP_RESPONSE_REQUIRE_EXTENSION);
        allowed_responses_.insert(SIP_RESPONSE_INTERVAL_TOO_BRIEF);
        allowed_responses_.insert(SIP_RESPONSE_UNAVAIL_TEMP);
        allowed_responses_.insert(SIP_RESPONSE_CALL_OR_TRANSACTION_NOT_EXIST);
        allowed_responses_.insert(SIP_RESPONSE_LOOP_DETECTED);
        allowed_responses_.insert(SIP_RESPONSE_TOO_MANY_HOPS);
        allowed_responses_.insert(SIP_RESPONSE_ADDRESS_INCOMPLETE);
        allowed_responses_.insert(SIP_RESPONSE_AMBIGUOUS_URI);
        allowed_responses_.insert(SIP_RESPONSE_BUSY);
        allowed_responses_.insert(SIP_RESPONSE_REQUEST_TERMINATED);
        allowed_responses_.insert(SIP_RESPONSE_NOT_ACCEPTABLE_HERE);
        allowed_responses_.insert(SIP_RESPONSE_REQUEST_PENDING);
        allowed_responses_.insert(SIP_RESPONSE_UNDECIPHERABLE);
        allowed_responses_.insert(SIP_RESPONSE_SERVER_INTERNAL_ERROR);
        allowed_responses_.insert(SIP_RESPONSE_FUNC_NOT_IMPLEMENTED);
        allowed_responses_.insert(SIP_RESPONSE_BAD_GATEWAY);
        allowed_responses_.insert(SIP_RESPONSE_SERVICE_UNAVAIL);
        allowed_responses_.insert(SIP_RESPONSE_SERVICE_TIMEOUT);
        allowed_responses_.insert(SIP_RESPONSE_UNSUPPORTED_VERSION);
        allowed_responses_.insert(SIP_RESPONSE_MESSAGE_TOO_LARGE);
        allowed_responses_.insert(SIP_RESPONSE_GLOBAL_BUSY);
        allowed_responses_.insert(SIP_RESPONSE_CALLEE_DECLINE);
        allowed_responses_.insert(SIP_RESPONSE_GLOBAL_NOT_EXIST);
        allowed_responses_.insert(SIP_RESPONSE_GLOBAL_NOT_ACCEPTABLE);
    }

    void Element::send_msg(RequestMessage &msg)
    {
        udp_.send_buffer(msg.create().Msg());
    }

    void Element::send_msg(ResponseMessage &msg)
    {
        udp_.send_buffer(msg.create().Msg());
    }

    void Element::echo(RequestMessage &in_msg)
    {
        ResponseMessage rep(in_msg);

        rep.SipVersion(SIP_VERSION_2_0);
        rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

        rep.append_userdata("Echo from Dr.Who");
        rep.add_content_length();

        send_msg(rep);
    }

    int Element::on_receive_message(std::string &msg)
    {
        int ret;

        if (METHOD_INVITE.code() <= (ret = Message::get_method_from_buffer(allowed_methods_, msg)))
        {
            return on_receive_req(msg, ret);
        }

        if (SIP_RESPONSE_TRYING.code() <= (ret = Message::get_response_code_from_buffer(allowed_responses_, msg)))
        {
            return on_receive_resp(msg, ret);
        }
        //TODO throw exception ??
        return PROCEDURE_ERROR;
    }

    void Element::simple_response(const RespCode &rc, RequestMessage &in_msg)
    {
        ResponseMessage rep(in_msg);
        rep.SipVersion(SIP_VERSION_2_0);
        rep.ResponseCode(rc);
    
        send_msg(rep);
    }

    int Element::on_receive_req(std::string &msg, const int code)
    {
        int ret = PROCEDURE_OK;
        RequestMessage in_msg(msg);

        if (false /* TODO: pending a request on demand*/)
        {
            ResponseMessage rep(in_msg);
            rep.SipVersion(SIP_VERSION_2_0);
            rep.ResponseCode(SIP_RESPONSE_REQUEST_TERMINATED);
    
            send_msg(rep);
            return MESSAGE_PROCESSED;
        }

        if (SIP_RESPONSE_UNSUPPORTED_URI_SCHEME.code() == (ret = in_msg.parse()))
        {
            simple_response(SIP_RESPONSE_UNSUPPORTED_URI_SCHEME, in_msg);
            return MESSAGE_PROCESSED;
        }

        if (in_msg.max_forwards_.size())
        {
            if (in_msg.max_forwards_.last()->is_zero_forward())
            {
                if (METHOD_ID_OPTIONS != code)
                {
                    simple_response(SIP_RESPONSE_TOO_MANY_HOPS, in_msg);
                    return MESSAGE_PROCESSED;
                }
            }
        }

        // TODO: loop detection
        if (false)
        {
            simple_response(SIP_RESPONSE_LOOP_DETECTED, in_msg);
            return MESSAGE_PROCESSED;
        }

        if (in_msg.proxy_require_.size())
        {
            std::vector<std::string> tags = in_msg.proxy_require_.last()->misunderstand_tags();

            if (tags.size())
            {
                ResponseMessage rep(in_msg);
                rep.SipVersion(SIP_VERSION_2_0);
                rep.ResponseCode(SIP_RESPONSE_BAD_EXTENSION);
    
                rep.add_unsupported()
                ->add_value(tags);
    
                send_msg(rep);
                return MESSAGE_PROCESSED;
            }
        }

        if (in_msg.proxy_authorization_.size())
        {
            //TODO: inspection NOTE: 96/269
        }

        if (METHOD_ID_INVITE != code
        && METHOD_ID_REGISTER != code)
        {
            Dialog dialog(in_msg);
            if (dialog_preprocess<RequestMessage>(dialog, in_msg))
                return PROCEDURE_OK;
        }

        switch (code)
        {
            case METHOD_ID_INVITE:
            {
                return on_invite_request(in_msg);
            }
            case METHOD_ID_REGISTER:
            {
                return on_register_request(in_msg);
            }
            case METHOD_ID_CANCEL:
            {
                return on_cancel_request(in_msg);
            }
            case METHOD_ID_ACK:
            {
                return on_ack_request(in_msg);
            }
            case METHOD_ID_BYE:
            {
                return on_bye_request(in_msg);
            }
            case METHOD_ID_OPTIONS:
            {
                return on_options_request(in_msg);
            }
            case METHOD_ID_SUBSCRIBE:
            {
                return on_subscribe_request(in_msg);
            }
            case METHOD_ID_NOTIFY:
            {
                return on_notify_request(in_msg);
            }
            case METHOD_ID_MESSAGE:
            {
                return on_message_request(in_msg);
            }
            case METHOD_ID_INFO:
            {
                return on_info_request(in_msg);
            }
            case METHOD_ID_UPDATE:
            {
                return on_update_request(in_msg);
            }
            case METHOD_ID_REFER:
            {
                return on_refer_request(in_msg);
            }
            case METHOD_ID_PRACK:
            {
                return on_prack_request(in_msg);
            }
            default:
            {
                std::cerr << "Unexpected request: " << code << '\n';
            }
        }

        return ret;
    }

    int Element::on_receive_resp(std::string &msg, const int code)
    {
        ResponseMessage in_msg(msg);
        in_msg.parse();

        Dialog dialog(in_msg);

        if (in_msg.is_resp2invite())
        {
            if (in_msg.is_1xx_resp())
            {
                dialogs_.create_dialog(dialog);
            }
            else if (in_msg.is_2xx_resp())
            {
                dialogs_[dialog.id()]->is_confirmed(true);
    
                AckMessage ack(in_msg);
                ack.SipVersion(SIP_VERSION_2_0);
                ack.RequestURI(udp_.Addr());

                send_msg(ack);
            }
            else
            {
                bye_request();
                // TODO: invite req failed feedback
//                dialogs_.cancel_dialog(dialog.id());
                std::cerr << "Unable to establish session due to \n[\n"
                        << in_msg << "]\n";
            }
        }
        else if (in_msg.is_resp2register())
        {
			switch (code)
			{
				default:; //TODO for each code
			}
		}
//        else if ((ret = dialog_preprocess<ResponseMessage>(dialog, in_msg)))
//        {
//            return ret;
//        }
        // TODO: else
        if (dialogs_[dialog.id()])
        {
            switch (code)
            {
                case 408:
                case 481:
                {
                    std::cout << "Receive response: " << code << ", cancelling dialog\n";
                    dialogs_.cancel_dialog(dialog.id());
                    return MESSAGE_PROCESSED;
                }
                default:;
            }
        }

        return PROCEDURE_OK;
    }

    int Element::fetch_msg()
    {
        if (0 > udp_.recv_buffer(0))
            return PROCEDURE_ERROR;

        std::cout << "peer: <" << udp_.Addr() << ":" << udp_.Port() << ">\n";
        std::string msg(udp_.Message());
        udp_.clear_msg();
        on_receive_message(msg);

        return PROCEDURE_OK;
    }

    int Element::start()
    {
        try
        {
            while (run_)
            {
                if (0 > udp_.recv_buffer(0)) continue;
                // TODO: log peer
                std::cout << "peer: <" << udp_.Addr() << ":" << udp_.Port() << ">\n";
                std::string msg(udp_.Message());
                udp_.clear_msg();
                on_receive_message(msg);
            }
        }
        catch (std::exception e)
        {
            std::cout << "exception: " << e.what() << '\n';
            // TODO: log it
        }

        return PROCEDURE_OK;
    }

    int Element::invite_request()
    {
        InviteMessage req;

        req.SipVersion(SIP_VERSION_2_0);
        req.RequestURI(udp_.Addr());

        req.add_from()
        ->add_name("zex")
        .add_uri("sip:zex@"+udp_.SelfAddr())
        .add_param("tag", "293!hsj@df");

        req.add_to()
        ->add_name("\"Big Boss\"")
        .add_uri("sip:bigboss@paris.agg.oo");

        req.add_cseq()
        ->cseq("1")
        .method(req.Method());

        req.add_via()
        ->add_proto(SIP_VERSION_2_0_UDP)
        .add_sentby(udp_.SelfAddr());

        req.add_call_id()
        ->id("sundo@1311bili");

        if (false /*TODO: is_sips(req.req_line_.request_uri_) */)
        {
            req.add_contact()
            ->add_uri("sips:zex@"+udp_.SelfAddr());
        }
        else
        {
            req.add_contact()
            ->add_uri("sip:zex@"+udp_.SelfAddr());
        }

        // TODO: check for re-invite
        if (!dialogs_.empty())
        {
        }

        send_msg(req);
        ivt_.state(T_FSM_CALLING);
//        msgq_.push(req.Msg());
        // TODO: 64*T1 start
        return PROCEDURE_OK;
    }

    int Element::register_request()
    {
        RegisterMessage req;

        req.SipVersion(SIP_VERSION_2_0);
        req.RequestURI("sip:nick@uuac.com");

        req.add_to()
        ->add_uri(udp_.SelfAddr())
        .add_name("ook");

        req.add_from()
        ->add_uri(udp_.SelfAddr())
        .add_name("ook");

        req.add_call_id()
        ->id("987kk");
        
        req.add_cseq()
        ->cseq("1")
        .method(req.Method());

        req.add_contact()
        ->add_uri("tel:+1-972-555-2222");
        //->add_uri(udp_.SelfAddr());

        req.add_route()
        ->add_uri("129.99.0.32");

        req.add_via()
        ->add_proto(SIP_VERSION_2_0_UDP)
        .add_sentby(udp_.SelfAddr());

        send_msg(req);

        return PROCEDURE_OK;
    }

    int Element::bye_request()
    {
        if (dialogs_.empty())
            return PROCEDURE_OK;

        ByeMessage req;
        req.SipVersion(SIP_VERSION_2_0);

        req.add_to()
        ->add_name("Big Boss\"")
        .add_uri(dialogs_.last()->remote_uri());

        if (dialogs_.last()->id().remote_tag().size())
            req.to_.last()->add_param("tag", dialogs_.last()->id().remote_tag());

        req.add_from()
        ->add_name("zex")
        .add_uri(dialogs_.last()->local_uri());

        if (dialogs_.last()->id().local_tag().size())
            req.from_.last()->add_param("tag", dialogs_.last()->id().local_tag());

        req.add_call_id()
        ->id(dialogs_.last()->id().call_id().id());

        std::string seq;

        if (!dialogs_.last()->local_seq().cseq().empty())
        {
            dialogs_.last()->local_seq().inc_seq();
            seq = dialogs_.last()->local_seq().cseq();
        }

        if (seq.empty())
        {
            seq = "1"; // TODO: choose a seq, 32bits
        }

        req.add_cseq()
        ->cseq(seq)
        .method(req.Method());

        if (dialogs_.last()->remote_target().size())
            req.RequestURI(dialogs_.last()->remote_target().last()->uri());

        if (dialogs_.last()->routes().size())
        {
            if (dialogs_.last()->routes().last()->cons_.last()->has_param("lr"))
            {
//                    if (dialogs_.last()->remote_target().size())
                req.RequestURI(dialogs_.last()->remote_target().last()->uri());

                req.add_route();

                if (dialogs_.last()->routes().size())
                {
                    req.route_.last()->cons_ = dialogs_.last()->routes().last()->cons_;
                }
            }
            else
            {
                req.RequestURI(dialogs_.last()->routes().last()->cons_.last()->uri());

                req.add_route();

                ContactList::iterator from = dialogs_.last()->routes().last()->cons_.begin();
                from++;

                req.route_.last()->cons_.append(from, dialogs_.last()->routes().last()->cons_.end());
                req.route_.last()->cons_.append(dialogs_.last()->remote_target());
            }
        }

        req.add_via()
        ->add_proto(SIP_VERSION_2_0_UDP)
        .add_sentby(udp_.SelfAddr());


        if (false /* TODO: is_sips(req.req_line_.request_uri_) */
        || false /* TODO: is_sips(req.req_line_.request_uri_) */)
        {
            req.add_contact()->add_uri("sips:utoc@ir.cx");
        }

        send_msg(req);
//        msgq_.push(req.Msg());
//---------------------------------------------------------------
        dialogs_.cancel_dialog(dialogs_.last()->id());

        return PROCEDURE_OK;
    }

    int Element::cancel_request()
    {
        CancelMessage req;
        req.SipVersion(SIP_VERSION_2_0);

        if (false /* TODO: 1xx resp not yet received */)
        {    /* wait until 1xx resp received then send */
            return PROCEDURE_ERROR;
        }

        send_msg(req);
        return PROCEDURE_OK;
    }

    int Element::update_request()
    {
        return PROCEDURE_OK;
    }

    int Element::info_request()
    {
        return PROCEDURE_OK;
    }

    int Element::ack_request()
    {
        AckMessage req;

        req.SipVersion(SIP_VERSION_2_0);

        if (dialogs_.size())
        {
            req.add_to()
            ->add_name("Big Boss\"")
            .add_uri(dialogs_.last()->remote_uri());

            if (dialogs_.last()->id().remote_tag().size())
                req.to_.last()->add_param("tag", dialogs_.last()->id().remote_tag());

            req.add_from()
            ->add_name("zex")
            .add_uri(dialogs_.last()->local_uri());

            if (dialogs_.last()->id().local_tag().size())
                req.from_.last()->add_param("tag", dialogs_.last()->id().local_tag());

            req.add_call_id()
            ->id(dialogs_.last()->id().call_id().id());

            std::string seq;
    
            if (!dialogs_.last()->local_seq().cseq().empty())
            {
                dialogs_.last()->local_seq().inc_seq();
                seq = dialogs_.last()->local_seq().cseq();
            }

            if (seq.empty())
            {
                seq = "1"; // TODO: choose a seq, 32bits
            }
    
            req.add_cseq()
            ->cseq(seq)
            .method(req.Method());

            if (dialogs_.last()->remote_target().size())
                req.RequestURI(dialogs_.last()->remote_target().last()->uri());

            if (dialogs_.last()->routes().size())
            {
                if (dialogs_.last()->routes().last()->cons_.last()->has_param("lr"))
                {
//                    if (dialogs_.last()->remote_target().size())
                    req.RequestURI(dialogs_.last()->remote_target().last()->uri());

                    req.add_route();

                    if (dialogs_.last()->routes().size())
                    {
                        req.route_.last()->cons_ = dialogs_.last()->routes().last()->cons_;
                    }
                }
                else
                {
                    req.RequestURI(dialogs_.last()->routes().last()->cons_.last()->uri());

                    req.add_route();

                    ContactList::iterator from = dialogs_.last()->routes().last()->cons_.begin();
                    from++;

                    req.route_.last()->cons_.append(from, dialogs_.last()->routes().last()->cons_.end());
                    req.route_.last()->cons_.append(dialogs_.last()->remote_target());
                }
            }
        }

        req.add_via()
        ->add_proto(SIP_VERSION_2_0_UDP)
        .add_sentby(udp_.SelfAddr());


        if (false /*is_sips(req.req_line_.request_uri_) */
        || false /*is_sips(req.req_line_.request_uri_) */)
        {
            req.add_contact()->add_uri("sips:utoc@ir.cx");
        }

        send_msg(req);
        return PROCEDURE_OK;
    }

    int Element::message_request()
    {
        MessageMessage req;

        req.SipVersion(SIP_VERSION_2_0);
        req.RequestURI(udp_.Addr());

        if (dialogs_.size())
        {
            req.add_to()
            ->add_name("Big Boss\"")
            .add_uri(dialogs_.last()->remote_uri());

            if (dialogs_.last()->id().remote_tag().size())
                req.to_.last()->add_param("tag", dialogs_.last()->id().remote_tag());

            req.add_from()
            ->add_name("zex")
            .add_uri(dialogs_.last()->local_uri());

            if (dialogs_.last()->id().local_tag().size())
                req.from_.last()->add_param("tag", dialogs_.last()->id().local_tag());

            req.add_call_id()
            ->id(dialogs_.last()->id().call_id().id());

            std::string seq;
    
            if (!dialogs_.last()->local_seq().cseq().empty())
            {
                dialogs_.last()->local_seq().inc_seq();
                seq = dialogs_.last()->local_seq().cseq();
            }

            if (seq.empty())
            {
                seq = "1"; // TODO: choose a seq, 32bits
            }
    
            req.add_cseq()
            ->cseq(seq)
            .method(req.Method());

            if (dialogs_.last()->remote_target().size())
                req.RequestURI(dialogs_.last()->remote_target().last()->uri());

            if (dialogs_.last()->routes().size())
            {
                if (dialogs_.last()->routes().last()->cons_.last()->has_param("lr"))
                {
//                    if (dialogs_.last()->remote_target().size())
                    req.RequestURI(dialogs_.last()->remote_target().last()->uri());

                    req.add_route();

                    if (dialogs_.last()->routes().size())
                    {
                        req.route_.last()->cons_ = dialogs_.last()->routes().last()->cons_;
                    }
                }
                else
                {
                    req.RequestURI(dialogs_.last()->routes().last()->cons_.last()->uri());

                    req.add_route();

                    ContactList::iterator from = dialogs_.last()->routes().last()->cons_.begin();
                    from++;

                    req.route_.last()->cons_.append(from, dialogs_.last()->routes().last()->cons_.end());
                    req.route_.last()->cons_.append(dialogs_.last()->remote_target());
                }
            }
        }
        else
        {
            req.RequestURI(udp_.Addr());

            req.add_to()
            ->add_name("Big Boss\"")
            .add_uri(udp_.Addr());

            req.add_from()
            ->add_name("zex")
            .add_uri(udp_.SelfAddr());

            req.add_cseq()
            ->cseq("1")
            .method(req.Method());

            req.add_call_id()
            ->id("54235jd"); // TODO: generate it

        }

        req.add_priority()
        ->add_value("emergency");

        req.add_content_type()
        ->type("application")
        .subtype("pkcs7-mime")
        .HeaderParam("smime-type", "enveloped-data")
        .HeaderParam("name", "smime.p7m");

        req.add_www_authenticate()
        ->add_value("Digest")
        .add_param("realm", "\"biloxi.com\"")
        .add_param("qop", "\"auth,auth-int\"")
        .add_param("nonce", "\"d928j8mms349q\"")
        .add_param("opaque", "\"5ccc8372dsvnlk\"");

        req.add_organization()
        ->add_value("ieee.org blenisa,asirel dlg,");

        req.add_subject()
        ->add_value("wekkwida asdfgnb adun38-vn kdi");

        req.add_date()
        ->add_value("Sat, 13 Nov 2010 23:29:00 GMT");

        req.add_accept_language()
        ->add_value("da")
        .add_param("q", "0.8")
        .add_value("en-gb")
        .add_param("q", "0.7") 
        .add_value("en")
        .add_param("q", "0.1");

        req.add_accept_encoding()
        ->add_value("da")
        .add_param("q", "0.8")
        .add_value("en-gb")
        .add_param("q", "0.2"); 

        req.add_content_disposition()
        ->add_value("session")
        .HeaderParam("handling", "optional");

        req.add_via()
        ->add_proto(SIP_VERSION_2_0_UDP)
        .add_sentby(udp_.SelfAddr());

        if (false /*is_sips(req.req_line_.request_uri_) */
        || false /*is_sips(req.req_line_.request_uri_) */)
        {
            req.add_contact()->add_uri("sips:utoc@ir.cx");
        }

        req.append_userdata("bigo digo reading");
        req.add_content_length();

        send_msg(req);

        return PROCEDURE_OK;
    }

    int Element::subscribe_request()
    {
        SubscribeMessage req;

        req.SipVersion(SIP_VERSION_2_0);
        req.RequestURI(udp_.Addr());

        send_msg(req);
        return PROCEDURE_OK;
    }

    int Element::notify_request()
    {
        NotifyMessage req;

        req.SipVersion(SIP_VERSION_2_0);
        req.RequestURI(udp_.Addr());

        send_msg(req);
        return PROCEDURE_OK;
    }

    int Element::refer_request()
    {
        ReferMessage req;

        req.SipVersion(SIP_VERSION_2_0);
        req.RequestURI(udp_.Addr());

        send_msg(req);

        return PROCEDURE_OK;
    }

    int Element::options_request()
    {
        OptionsMessage req;

        req.SipVersion(SIP_VERSION_2_0);

        if (dialogs_.size())
        {
            req.add_to()
            ->add_name("Big Boss\"")
            .add_uri(dialogs_.last()->remote_uri());

            if (dialogs_.last()->id().remote_tag().size())
                req.to_.last()->add_param("tag", dialogs_.last()->id().remote_tag());

            req.add_from()
            ->add_name("zex")
            .add_uri(dialogs_.last()->local_uri());

            if (dialogs_.last()->id().local_tag().size())
                req.from_.last()->add_param("tag", dialogs_.last()->id().local_tag());

            req.add_call_id()
            ->id(dialogs_.last()->id().call_id().id());

            std::string seq;
    
            if (!dialogs_.last()->local_seq().cseq().empty())
            {
                dialogs_.last()->local_seq().inc_seq();
                seq = dialogs_.last()->local_seq().cseq();
            }

            if (seq.empty())
            {
                seq = "1"; // TODO: choose a seq, 32bits
            }
    
            req.add_cseq()
            ->cseq(seq)
            .method(req.Method());

            if (dialogs_.last()->remote_target().size())
                req.RequestURI(dialogs_.last()->remote_target().last()->uri());

            if (dialogs_.last()->routes().size())
            {
                if (dialogs_.last()->routes().last()->cons_.last()->has_param("lr"))
                {
//                    if (dialogs_.last()->remote_target().size())
                    req.RequestURI(dialogs_.last()->remote_target().last()->uri());

                    req.add_route();

                    if (dialogs_.last()->routes().size())
                    {
                        req.route_.last()->cons_ = dialogs_.last()->routes().last()->cons_;
                    }
                }
                else
                {
                    req.RequestURI(dialogs_.last()->routes().last()->cons_.last()->uri());

                    req.add_route();

                    ContactList::iterator from = dialogs_.last()->routes().last()->cons_.begin();
                    from++;

                    req.route_.last()->cons_.append(from, dialogs_.last()->routes().last()->cons_.end());
                    req.route_.last()->cons_.append(dialogs_.last()->remote_target());
                }
            }
        }
        else
        {
            req.RequestURI(udp_.Addr());

            req.add_to()
            ->add_name("Big Boss\"")
            .add_uri(udp_.Addr());

            req.add_from()
            ->add_name("zex")
            .add_uri(udp_.SelfAddr());

            req.add_cseq()
            ->cseq("1")
            .method(req.Method());

            req.add_call_id()
            ->id("54235jd"); // TODO: generate it
        }

        req.add_via()
        ->add_proto(SIP_VERSION_2_0_UDP)
        .add_sentby(udp_.SelfAddr());

        if (false /*is_sips(req.req_line_.request_uri_) */
        || false /*is_sips(req.req_line_.request_uri_) */)
        {
            req.add_contact()->add_uri("sips:utoc@ir.cx");
        }

        send_msg(req);
//        msgq_.push(req.Msg());
//---------------------------------------------------------------

        return PROCEDURE_OK;
    }

    int Element::prack_request()
    {
        PrackMessage req;

        req.SipVersion(SIP_VERSION_2_0);
        req.RequestURI(udp_.Addr());

        send_msg(req);
        return PROCEDURE_OK;
    }

    int Element::on_invite_request(RequestMessage &in_msg)
    {
        ResponseMessage rep(in_msg);
        rep.SipVersion(SIP_VERSION_2_0);

        Dialog dialog(in_msg);

        // check for a re-invite request
        if (dialogs_[dialog.id()] && dialogs_[dialog.id()]->is_confirmed())
        {
            // TODO: update dialog
        }


        dialogs_.create_dialog(dialog);

        rep.add_contact()
        ->add_uri("sip:ag@"+udp_.Addr());

        if (in_msg.record_route_.size())
            rep.record_route_ = in_msg.record_route_;

        std::cout << "----------\n" << *dialogs_.last() << "-----------\n";

        rep.ResponseCode(SIP_RESPONSE_RINGING);

        send_msg(rep);
        dialogs_[dialog.id()]->still_ringing(true);

        // TODO: timeout here

        // dummy --------------->
        int i = 7;
        PROGRESS_WITH_FEEDBACK("ringing", i--, sleep(0.5); send_msg(rep))
        // dummy ---------------|

        if (false /* TODO: need redirect */)
        {
            rep.ResponseCode(SIP_RESPONSE_MULTI_CHOICES);
//            rep.ResponseCode(SIP_RESPONSE_MOVE_PERM);
//            rep.ResponseCode(SIP_RESPONSE_MOVE_TEMP);
            send_msg(rep);

            // TODO: start redirect

            return PROCEDURE_OK;
        }

        if (false /* TODO: get reject signal */)
        {
            if (false /* TODO: no one, really, will take this */)
                rep.ResponseCode(SIP_RESPONSE_GLOBAL_BUSY);
            else
                rep.ResponseCode(SIP_RESPONSE_BUSY);

            send_msg(rep);

            return PROCEDURE_OK;
        }

        rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

        rep.add_allow();

        for (auto &it : allowed_methods_) 
            rep.allow_.last()->add_value(it.name());


        rep.add_supported()
        ->add_value("100rel");

        send_msg(rep);

        // TODO: timeout here for ACK

        return PROCEDURE_OK;
    }
    
    int Element::on_register_request(RequestMessage &in_msg)
    {
        ResponseMessage rep(in_msg);
        rep.SipVersion(SIP_VERSION_2_0);
        rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

        /*
         * TODO: Expires <= 2^32-1
         *     if Expires is illegal, then use 3600
         */

        /*
         * NOTE: A UA SHOULD NOT refresh bindings set up by
         * other UAs.
         * TODO: add bindings for AOR, check preference priority by `q`
         *  sip:xxxxxx
         *  tel:xxxxx
         *  mailto:xxxxx
         */

        /*
         * TODO: add current bindings list to rep
         */
        rep.add_date()
        ->add_value(Time::now());
//        ->add_value("Sat, 13 Nov 2014 23:29:00 GMT");
        send_msg(rep);

        return PROCEDURE_OK;
    }
    
    int Element::on_bye_request(RequestMessage &in_msg)
    {
        ResponseMessage rep(in_msg);
    
        Dialog dialog(in_msg);

//        if (in_msg.record_route_.size())
//            rep.record_route_ = in_msg.record_route_;

        dialogs_.cancel_dialog(dialog.id());

        return PROCEDURE_OK;
    }
    
    int Element::on_cancel_request(RequestMessage &in_msg)
    {
        Dialog dialog(in_msg);

        if (dialogs_[dialog.id()])
        {
            if (dialogs_[dialog.id()]->still_ringing())
            {
                // TODO: cancel it
            }
            else
            {
                ResponseMessage rep(in_msg);

                rep.SipVersion(SIP_VERSION_2_0);
                rep.ResponseCode(SIP_RESPONSE_REQUEST_TERMINATED);

                send_msg(rep);
            }
        }

        return PROCEDURE_OK;
    }
    
    int Element::on_ack_request(RequestMessage &in_msg)
    {
        Dialog dialog(in_msg);

        if (dialogs_[dialog.id()])
        {
            dialogs_[dialog.id()]->is_confirmed(true);
        }

        return PROCEDURE_OK;
    }
    
    int Element::on_options_request(RequestMessage &in_msg)
    {
        ResponseMessage rep(in_msg);

        rep.SipVersion(SIP_VERSION_2_0);
        rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

        rep.add_accept()
        ->add_value("text", "plain")
        .add_value("text", "html")
        .add_value("application/sdp")
        .add_param("level", "1")
        .add_value("multipart/sdp");

        rep.add_allow();

        for (auto &it : allowed_methods_) 
            rep.allow_.last()->add_value(it.name());

//        rep.add_error_info()
//        ->add_uri("<sip:mary238@4usnmn4.s49s.lsdj.org>")
//        .add_uri("<sip:yem.kkk.ei3m.com>");

        send_msg(rep);

        return PROCEDURE_OK;
    }
    
    int Element::on_subscribe_request(RequestMessage &in_msg)
    {
        echo(in_msg);
        return PROCEDURE_OK;
    }
    
    int Element::on_notify_request(RequestMessage &in_msg)
    {
        echo(in_msg);
        return PROCEDURE_OK;
    }
    
    int Element::on_info_request(RequestMessage &in_msg)
    {
        echo(in_msg);
        return PROCEDURE_OK;
    }
    
    int Element::on_update_request(RequestMessage &in_msg)
    {
        echo(in_msg);
        return PROCEDURE_OK;
    }
    
    int Element::on_refer_request(RequestMessage &in_msg)
    {
        echo(in_msg);
        return PROCEDURE_OK;
    }
    
    int Element::on_message_request(RequestMessage &in_msg)
    {
        echo(in_msg);
        return PROCEDURE_OK;
    }
    
    int Element::on_prack_request(RequestMessage &in_msg)
    {
        echo(in_msg);
        return PROCEDURE_OK;
    }

} // namespace EasySip
