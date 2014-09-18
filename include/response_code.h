/*
 * include/response_code.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "parameter.h"

namespace EasySip
{
	typedef CodeMap RespCode;
	typedef CodeMap WarnCode;
	typedef std::set<RespCode> RespCodeList;
	
	// RFC-3261
	// 1xx provisional
	const RespCode SIP_RESPONSE_TRYING(100, "Trying");
	const RespCode SIP_RESPONSE_RINGING(180, "Ringing");
	const RespCode SIP_RESPONSE_FORWARDING(181, "Call is Being Forwared");
	const RespCode SIP_RESPONSE_QUEUED(182, "Queued");
	const RespCode SIP_RESPONSE_SESSION_PROGRESS(183, "Session Progress");
	// 2xx successful
	const RespCode SIP_RESPONSE_SUCCESSFUL(200, "OK");
	const RespCode SIP_RESPONSE_ACCEPTED(202, "Accepted");
	// 3xx redirection
	const RespCode SIP_RESPONSE_MULTI_CHOICES(300, "Multiple Choices");
	const RespCode SIP_RESPONSE_MOVE_PERM(301, "Moved Permanently");
	const RespCode SIP_RESPONSE_MOVE_TEMP(302, "Moved Temporarily");
	const RespCode SIP_RESPONSE_USE_PROXY(305, "Use Proxy");
	const RespCode SIP_RESPONSE_ALTER_SERVICE(380, "Alternative Service");
	// 4xx request failure
	const RespCode SIP_RESPONSE_BAD_REQUEST(400, "Bad Request");
	const RespCode SIP_RESPONSE_UNAUTHORIZED(401, "Unauthorized");
	const RespCode SIP_RESPONSE_REQUIRE_PAYMENT(402, "Payment Required");
	const RespCode SIP_RESPONSE_FORBIDDEN(403, "Forbidden");
	const RespCode SIP_RESPONSE_NOT_FOUND(404, "Not Found");
	const RespCode SIP_RESPONSE_METHOD_NOT_ALLOWED(405, "Method Not Allowed");
	const RespCode SIP_RESPONSE_NOT_ACCEPTABLE(406, "Not Acceptable");
	const RespCode SIP_RESPONSE_REQUIRE_PROXY_AUTHENTICATION(407, "Proxy Authentication Required");
	const RespCode SIP_RESPONSE_REQUIRE_REQUEST_TIMEOUT(408, "Request Timeout");
	const RespCode SIP_RESPONSE_RESOURCE_NOT_AVAIL(410, "Gone");
	const RespCode SIP_RESPONSE_REQUEST_ENTITY_TOO_LARGE(413, "Request Entity Too Large");
	const RespCode SIP_RESPONSE_REQUEST_URI_TOO_LONG(414, "Request-URI Too Large");
	const RespCode SIP_RESPONSE_UNSUPPORTED_MEDIA_TYPE(415, "Unsupported Media Type");
	const RespCode SIP_RESPONSE_UNSUPPORTED_URI_SCHEME(416, "Unsupported URI Scheme");
	const RespCode SIP_RESPONSE_BAD_EXTENSION(420, "Bad Extension");
	const RespCode SIP_RESPONSE_REQUIRE_EXTENSION(421, "Extension Required");
	const RespCode SIP_RESPONSE_INTERVAL_TOO_BRIEF(423, "Interval Too Brief");
	const RespCode SIP_RESPONSE_UNAVAIL_TEMP(480, "Temporarily not available");
	const RespCode SIP_RESPONSE_CALL_OR_TRANSACTION_NOT_EXIST(481, "Call Leg/Transaction Does Not Exist");
	const RespCode SIP_RESPONSE_LOOP_DETECTED(482, "Loop Detected");
	const RespCode SIP_RESPONSE_TOO_MANY_HOPS(483, "Too Many Hops");
	const RespCode SIP_RESPONSE_ADDRESS_INCOMPLETE(484, "Address Incomplete");
	const RespCode SIP_RESPONSE_AMBIGUOUS_URI(485, "Ambiguous");
	const RespCode SIP_RESPONSE_BUSY(486, "Busy Here");
	const RespCode SIP_RESPONSE_REQUEST_TERMINATED(487, "Request Terminated");
	const RespCode SIP_RESPONSE_NOT_ACCEPTABLE_HERE(488, "Not Acceptable Here");
	const RespCode SIP_RESPONSE_REQUEST_PENDING(491, "Request Pending");
	const RespCode SIP_RESPONSE_UNDECIPHERABLE(493, "Undecipherable");
	// 5xx server failure
	const RespCode SIP_RESPONSE_SERVER_INTERNAL_ERROR(500, "Internal Server Error");
	const RespCode SIP_RESPONSE_FUNC_NOT_IMPLEMENTED(501, "Not Implemented");
	const RespCode SIP_RESPONSE_BAD_GATEWAY(502, "Bad Gateway");
	const RespCode SIP_RESPONSE_SERVICE_UNAVAIL(503, "Service Unavailable");
	const RespCode SIP_RESPONSE_SERVICE_TIMEOUT(504, "Service Time-out");
	const RespCode SIP_RESPONSE_UNSUPPORTED_VERSION(505, "SIP Version not supported");
	const RespCode SIP_RESPONSE_MESSAGE_TOO_LARGE(513, "Message Too Large");
	// 6xx global failures
	const RespCode SIP_RESPONSE_GLOBAL_BUSY(600, "Busy Everywhere");
	const RespCode SIP_RESPONSE_CALLEE_DECLINE(603, "Decline");
	const RespCode SIP_RESPONSE_GLOBAL_NOT_EXIST(604, "Does not exist anywhere");
	const RespCode SIP_RESPONSE_GLOBAL_NOT_ACCEPTABLE(606, "Not Acceptable");

	// Warning codes in response (Warning hearder field)
	// RFC-3261
	const WarnCode SIP_WARNING_300(300, "Incompatible network protocol");
	const WarnCode SIP_WARNING_301(301, "Incompatible network address formats");
	const WarnCode SIP_WARNING_302(302, "Incompatible transport protocol");
	const WarnCode SIP_WARNING_303(303, "Incompatible bandwidth units");
	const WarnCode SIP_WARNING_304(304, "Media type not available");
	const WarnCode SIP_WARNING_305(305, "Incompatible media format");
	const WarnCode SIP_WARNING_306(306, "Attribute not understood");
	const WarnCode SIP_WARNING_307(307, "Session description parmeter not understood");
	const WarnCode SIP_WARNING_330(330, "Multicast not available");
	const WarnCode SIP_WARNING_331(331, "Unicast not available");
	const WarnCode SIP_WARNING_370(370, "Insufficient bandwidth");
	// RFC-5630
	const WarnCode SIP_WARNING_380(380, "SIPS Not Allowed");
	const WarnCode SIP_WARNING_381(381, "SIPS Required");
	// RFC-3261
	const WarnCode SIP_WARNING_399(399, "Miscellaneous warning");

} // namespace EasySip
