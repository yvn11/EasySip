/*
 * src/header_field.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "header_field.h"

namespace EasySip
{
	void HeaderFields::init_allowed_fields()
	{
//		allowed_fields_["CallId"] = call_id_;
//		allowed_fields_["CSeq"] = call_id_;
//		allowed_fields_["From"] = call_id_;
//		allowed_fields_["To"] = call_id_;
//		allowed_fields_["Via"] = call_id_;
//		allowed_fields_["Alert-Info"] = call_id_;
//		allowed_fields_["Allow-Events"] = call_id_;
//		allowed_fields_["Date"] = call_id_;
//		allowed_fields_["Contact"] = call_id_;
//		allowed_fields_["Organization"] = call_id_;
//		allowed_fields_["Record-Route"] = call_id_;
//		allowed_fields_["Retry-After"] = call_id_;
//		allowed_fields_["Subject"] = call_id_;
//		allowed_fields_["Supported"] = call_id_;
//		allowed_fields_["Timestamp"] = call_id_;
//		allowed_fields_["User-Agent"] = call_id_;
//		allowed_fields_["Answer-Mode"] = call_id_;
//		allowed_fields_["Priv-Answer-Mode"] = call_id_;
//		allowed_fields_["Accept"] = call_id_;
//		allowed_fields_["Accept-Contact"] = call_id_;
//		allowed_fields_["Accept-Encoding"] = call_id_;
//		allowed_fields_["Accept-Language"] = call_id_;
//		allowed_fields_["Authorization"] = call_id_;
//		allowed_fields_["Call-Info"] = call_id_;
//		allowed_fields_["Event"] = call_id_;
//		allowed_fields_["In-Reply-To"] = call_id_;
//		allowed_fields_["Join"] = call_id_;
//		allowed_fields_["Priority"] = call_id_;
//		allowed_fields_["Privacy"] = call_id_;
//		allowed_fields_["Proxy-Authorization"] = call_id_;
//		allowed_fields_["Proxy-Require"] = call_id_;
//		allowed_fields_["P-OSP-AuthToken"] = call_id_;
//		allowed_fields_["PAsserted-Identity"] = call_id_;
//		allowed_fields_["PPreferred-Identity"] = call_id_;
//		allowed_fields_["Max-Forwards"] = call_id_;
//		allowed_fields_["Reason"] = call_id_;
//		allowed_fields_["Refer-To"] = call_id_;
//		allowed_fields_["Referred-By"] = call_id_;
//		allowed_fields_["Reply-To"] = call_id_;
//		allowed_fields_["Replaces"] = call_id_;
//		allowed_fields_["Reject-Contact"] = call_id_;
//		allowed_fields_["Request-Disposition"] = call_id_;
//		allowed_fields_["Require"] = call_id_;
//		allowed_fields_["Route"] = call_id_;
//		allowed_fields_["Rack"] = call_id_;
//		allowed_fields_["Session-Expires"] = call_id_;
//		allowed_fields_["Subscription-State"] = call_id_;
//		allowed_fields_["AuthenticationInfo"] = call_id_;
//		allowed_fields_["Error-Info"] = call_id_;
//		allowed_fields_["Min-Expires"] = call_id_;
//		allowed_fields_["Min-SE"] = call_id_;
//		allowed_fields_["Proxy-Authenticate"] = call_id_;
//		allowed_fields_["Server"] = call_id_;
//		allowed_fields_["Unsupported"] = call_id_;
//		allowed_fields_["Warning"] = call_id_;
//		allowed_fields_["WWW-Authenticate"] = call_id_;
//		allowed_fields_["RSeq"] = call_id_;
//		allowed_fields_["Allow"] = call_id_;
//		allowed_fields_["Content-Encoding"] = call_id_;
//		allowed_fields_["Content-Length"] = call_id_;
//		allowed_fields_["Content-Language"] = call_id_;
//		allowed_fields_["Content-Type"] = call_id_;
//		allowed_fields_["Expires"] = call_id_;
//		allowed_fields_["MIME-Version"] = call_id_;

		
		allowed_fields_.insert("CallId");
		allowed_fields_.insert("CSeq");
		allowed_fields_.insert("From");
		allowed_fields_.insert("To");
		allowed_fields_.insert("Via");
		allowed_fields_.insert("Alert-Info");
		allowed_fields_.insert("Allow-Events");
		allowed_fields_.insert("Date");
		allowed_fields_.insert("Contact");
		allowed_fields_.insert("Organization");
		allowed_fields_.insert("Record-Route");
		allowed_fields_.insert("Retry-After");
		allowed_fields_.insert("Subject");
		allowed_fields_.insert("Supported");
		allowed_fields_.insert("Timestamp");
		allowed_fields_.insert("User-Agent");
		allowed_fields_.insert("Answer-Mode");
		allowed_fields_.insert("Priv-Answer-Mode");
		allowed_fields_.insert("Accept");
		allowed_fields_.insert("Accept-Contact");
		allowed_fields_.insert("Accept-Encoding");
		allowed_fields_.insert("Accept-Language");
		allowed_fields_.insert("Authorization");
		allowed_fields_.insert("Call-Info");
		allowed_fields_.insert("Event");
		allowed_fields_.insert("In-Reply-To");
		allowed_fields_.insert("Join");
		allowed_fields_.insert("Priority");
		allowed_fields_.insert("Privacy");
		allowed_fields_.insert("Proxy-Authorization");
		allowed_fields_.insert("Proxy-Require");
		allowed_fields_.insert("P-OSP-AuthToken");
		allowed_fields_.insert("PAsserted-Identity");
		allowed_fields_.insert("PPreferred-Identity");
		allowed_fields_.insert("Max-Forwards");
		allowed_fields_.insert("Reason");
		allowed_fields_.insert("Refer-To");
		allowed_fields_.insert("Referred-By");
		allowed_fields_.insert("Reply-To");
		allowed_fields_.insert("Replaces");
		allowed_fields_.insert("Reject-Contact");
		allowed_fields_.insert("Request-Disposition");
		allowed_fields_.insert("Require");
		allowed_fields_.insert("Route");
		allowed_fields_.insert("Rack");
		allowed_fields_.insert("Session-Expires");
		allowed_fields_.insert("Subscription-State");
		allowed_fields_.insert("AuthenticationInfo");
		allowed_fields_.insert("Error-Info");
		allowed_fields_.insert("Min-Expires");
		allowed_fields_.insert("Min-SE");
		allowed_fields_.insert("Proxy-Authenticate");
		allowed_fields_.insert("Server");
		allowed_fields_.insert("Unsupported");
		allowed_fields_.insert("Warning");
		allowed_fields_.insert("WWW-Authenticate");
		allowed_fields_.insert("RSeq");
		allowed_fields_.insert("Allow");
		allowed_fields_.insert("Content-Encoding");
		allowed_fields_.insert("Content-Length");
		allowed_fields_.insert("Content-Language");
		allowed_fields_.insert("Content-Type");
		allowed_fields_.insert("Expires");
		allowed_fields_.insert("MIME-Version");
	}
} // namespace EasySip
