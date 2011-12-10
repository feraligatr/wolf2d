#include "pch/pch.h"

#include "Session.h"
#include "SessionManager.h"
#include "msg/MessageDispatcher.h"
#include "msg/MessageManager.h"

using namespace boost::asio;

Session::Session(boost::asio::io_service& io_service, SessionManager& sessionManager, MessageDispatcher& dispatcher, MessageManager& messageManager)
:r_sessionManager(sessionManager)
,m_socket(io_service)
,r_dispatcher(dispatcher)
,r_messageManager(messageManager)
,m_closeTimer(io_service)
,m_writing(false)
{

}

boost::asio::ip::tcp::socket& Session::socket()
{
	return m_socket;
}

void Session::start()
{
	async_read(m_socket, buffer(&m_readHeader, sizeof(m_readHeader)),
				boost::bind(
					&Session::handle_read_header, shared_from_this(),
					placeholders::error));
}

void Session::deliver(Message* msg)
{
	m_pendingList.push_back(msg);
	performWrite();
}

void Session::stop()
{
	m_socket.close();
}

void Session::handle_read_header(const boost::system::error_code& error)
{
	if (!error)
	{
		if (m_readHeader.getSize() == 0)
		{
			handle_read_body(boost::system::error_code());
		}
		else
		{
			m_readMessage = r_messageManager.getFreeMessage(m_readHeader);
			async_read(m_socket,
					buffer(m_readMessage->getBody(), m_readMessage->getBodySize()),
					boost::bind(&Session::handle_read_body, shared_from_this(),
								placeholders::error));
		}
	}
	else
	{
		socketError();
	}
}

void Session::socketError()
{
	r_sessionManager.stop(shared_from_this());
}

void Session::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		r_dispatcher.dispatchMessage(shared_from_this(), m_readMessage);
		async_read(m_socket,
				buffer(&m_readHeader, sizeof(m_readHeader)),
				boost::bind(&Session::handle_read_header, shared_from_this(),
							placeholders::error));
	}
	else
	{
		socketError();
	}
}

void Session::handle_write(const boost::system::error_code& error)
{
	m_writing = false;
	if (!error)
	{
		performWrite();
	}
	else
	{
		socketError();
	}
}

bool Session::canWrite() const
{
	return !m_writing && !m_pendingList.empty();
}

void Session::performWrite()
{
	if (canWrite())
	{
		for (MessageList::iterator iter = m_writingList.begin(); iter != m_writingList.end(); ++iter)
		{
			(*iter)->dispose();
		}
		m_writingList = m_pendingList;
		m_pendingList.clear();
		std::vector<boost::asio::const_buffer> buffers;
		for (MessageList::iterator iter = m_writingList.begin(); iter != m_writingList.end(); ++iter)
		{
			buffers.push_back(boost::asio::const_buffer((*iter)->getBuffer(), (*iter)->getBufferSize()));
		}
		
		async_write(m_socket,
					buffers,
					boost::bind(&Session::handle_write, shared_from_this(),
						placeholders::error));
		m_writing = true;
	}
}
