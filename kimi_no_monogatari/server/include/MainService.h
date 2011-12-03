#ifndef _MAIN_SERVICE_H_
#define _MAIN_SERVICE_H_

#include "Server.h"
#include "Session.h"
class SessionManager;

class MainService
{
public:
	MainService(Server *server);
	virtual ~MainService();
public:
	GSTATUS init();
	GSTATUS run();
	void destroy();

protected:
	void startAccept();

	void handleAccept(const boost::system::error_code& e);
	void handle_stop();

private:
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::signal_set m_signals;

	pi::time_ms_t m_update_interval;

	SessionManager* m_sessionManager;
	SessionPtr m_newSession;
	Server *m_pServer;
};

#endif // #ifndef _MAIN_SERVICE_H_
