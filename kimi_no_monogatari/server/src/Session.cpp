#include "server_pch.h"

#include "Session.h"
#include "SessionManager.h"
#include "msg/MessageDispatcher.h"
#include "MessageManager.h"

using namespace boost::asio;

Session::Session(boost::asio::io_service& io_service, SessionManager* sm, MessageDispatcher* dispatcher, MessageManager* mm)
:m_pSessionManager(sm)
,m_socket(io_service)
,m_pDispatcher(dispatcher)
,m_pMessageManager(mm)
,m_closeTimer(io_service)
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
			m_readMessage = m_pMessageManager->getFreeMessage(m_readHeader);
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
	m_pSessionManager->stop(shared_from_this());
}

void Session::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		m_pDispatcher->dispatchMessage(this, m_readMessage);
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
	if (!error)
	{
		if (!m_pendingList.empty())
		{
			for (MessageList::iterator iter = m_writingList.begin(); iter != m_writingList.end(); ++iter)
			{
				(*iter)->dispose();
			}
			m_writingList = m_pendingList;
			std::vector<boost::asio::const_buffer> buffers;
			for (MessageList::iterator iter = m_writingList.begin(); iter != m_writingList.end(); ++iter)
			{
				buffers.push_back(boost::asio::const_buffer((*iter)->getBuffer(), (*iter)->getBufferSize()));
			}
			
			async_write(m_socket,
						buffers,
						boost::bind(&Session::handle_write, shared_from_this(),
							placeholders::error));
		}
	}
	else
	{
		socketError();
	}
}
