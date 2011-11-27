#include "server_pch.h"

#include "MainService.h"

#define DEFAULT_UPDATE_INTERVAL 100

MainService::MainService()
: m_acceptor(m_io_service)
{
}

MainService::~MainService()
{
	destroy();
}

GSTATUS MainService::init()
{
	m_update_interval = DEFAULT_UPDATE_INTERVAL;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 92);
	m_acceptor.open(endpoint.protocol());
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(endpoint);
	m_acceptor.listen();
	return GSTATUS_OK;
}

GSTATUS MainService::run()
{
	while (TRUE)
	{
		pi::time_ms_t last_time = pi::getTickSinceStartup();
		// other.run();
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
