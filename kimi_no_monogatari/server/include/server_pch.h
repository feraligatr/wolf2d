#ifndef _SERVER_PCH_H_
#define _SERVER_PCH_H_

#include "common.h"
#include "MessageDefine.h"
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "server_pi.h"

/*
	create a session. after session got new message. session invoke the global handler for message, the default global handler should 
	
	push the new message into global queue(with the needed parameters. 
	like room id, user id). and the global queue will send the parameters to different queue by the ids. then the different queue
	will handle the message.

	session has basic information about the other things.

	we will have a global message manager to create message for session. or the session should got message from the global handler?
*/

#endif // _SERVER_PCH_H_