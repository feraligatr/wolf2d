#include "server_pch.h"

#include "MainService.h"
#include "SessionManager.h"

#define DEFAULT_UPDATE_INTERVAL 100

MainService::MainService(Server* server)
: m_acceptor(m_io_service)
, m_signals(m_io_service)
, m_pServer(server)
{
}

MainService::~MainService()
{
	destroy();
}

GSTATUS MainService::init()
{
	m_update_interval = DEFAULT_UPDATE_INTERVAL;
	m_signals.add(SIGINT);
	m_signals.add(SIGTERM);
#if defined(SIGQUIT)
	m_signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
	m_signals.async_wait(boost::bind(&MainService::handle_stop, this));

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 92);
	m_acceptor.open(endpoint.protocol());
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(endpoint);
	m_acceptor.listen();

	startAccept();
	return GSTATUS_OK;
}

GSTATUS MainService::run()
{
	while (true)
	{
		pi::time_ms_t last_time = pi::getTickSinceStartup();
		m_pServer->update();
		while(m_io_service.poll() > 0 && (pi::getTickSinceStartup() - last_time < m_update_interval))
		{
			
		}
		pi::time_ms_t elapsed = pi::getTickSinceStartup() - last_time;
		if (elapsed < m_update_interval)
		{
			pi::thread_sleep((u32)(m_update_interval - elapsed));
		};
	}
	return GSTATUS_OK;
}

void MainService::destroy()
{
}

void MainService::startAccept()
{
	m_newSession.reset(m_pServer->getNewSession(m_io_service));
	m_acceptor.async_accept(m_newSession->socket(),
		boost::bind(&MainService::handleAccept, this,
			boost::asio::placeholders::error));
}

void MainService::handleAccept(const boost::system::error_code& e)
{
	if (!m_acceptor.is_open())
	{
		return;
	}
	if (!e)
	{
		m_pServer->getSessionManager()->start(m_newSession);
	}
	startAccept();
}
	
void MainService::handle_stop()
{
	// TODO. other clear work?
	m_acceptor.close();
	m_pServer->destroy();
}
