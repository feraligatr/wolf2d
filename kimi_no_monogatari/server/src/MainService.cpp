#include "server_pch.h"

#include "MainService.h"

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
		time_ms_t last_time = getCurrentTime();
		m_io_service.poll();
		time_ms_t elapsed = getCurrentTime() - last_time;
		if (elapsed < m_update_interval)
		{
			rest(m_update_interval - elapsed);
		};
	}
	return GSTATUS_OK;
}

void MainService::destroy()
{
}

time_ms_t MainService::getCurrentTime()
{
	return 1;
}

void MainService::rest(time_ms_t rest_time)
{
}