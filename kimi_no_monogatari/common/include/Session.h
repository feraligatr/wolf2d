#ifndef _SESSION_H_
#define _SESSION_H_

class SessionManager;
class MessageDispatcher;
class MessageManager;

#include "msg/Message.h"

class Session : public boost::enable_shared_from_this<Session>,
	private boost::noncopyable
{
public:
	explicit Session(boost::asio::io_service& io_service,
		SessionManager& sessionManager, MessageDispatcher& dispatcher, MessageManager& messageManager);

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
	void performWrite();
	bool canWrite() const;
	bool m_writing;


	boost::asio::ip::tcp::socket m_socket;

	// TODO: write here for Session timeout things.
	boost::asio::deadline_timer m_closeTimer;

	MessageDispatcher& r_dispatcher;
	SessionManager& r_sessionManager;
	MessageManager& r_messageManager;

	MessageHeader m_readHeader;
	Message* m_readMessage;

	typedef std::vector<Message*> MessageList;
	MessageList m_writingList;
	MessageList m_pendingList;
};

#endif /* _SESSION_H_ */