#ifndef _SESSION_H_
#define _SESSION_H_

class SessionManager;
class MessageDispatcher;
class MessageManager;

#include "msg/Message.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

class Session : public boost::enable_shared_from_this<Session>,
	private boost::noncopyable
{
public:
	explicit Session(boost::asio::io_service& io_service,
		SessionManager* sm, MessageDispatcher* dispatcher, MessageManager* mm);

	virtual ~Session() {}

	boost::asio::ip::tcp::socket& socket();

	void start();
	void stop();

	void deliver(Message* msg);
	
	void handle_read_header(const boost::system::error_code& error);
	
	void handle_read_body(const boost::system::error_code& error);
	
	void handle_write(const boost::system::error_code& error);
protected:
	void socketError();

	boost::asio::ip::tcp::socket m_socket;

	// TODO: write here for Session timeout things.
	boost::asio::deadline_timer m_closeTimer;

	MessageDispatcher* m_pDispatcher;
	SessionManager* m_pSessionManager;
	MessageManager* m_pMessageManager;

	MessageHeader m_readHeader;
	Message* m_readMessage;

	typedef std::vector<Message*> MessageList;
	MessageList m_writingList;
	MessageList m_pendingList;
};

typedef boost::shared_ptr<Session> SessionPtr;

#endif /* _SESSION_H_ */