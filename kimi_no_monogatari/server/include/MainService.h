#ifndef _MAIN_SERVICE_H_
#define _MAIN_SERVICE_H_

class MainService
{
public:
	MainService();
	virtual ~MainService();
public:
	GSTATUS init();
	GSTATUS run();
	void destroy();
private:
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::acceptor m_acceptor;

	pi::time_ms_t m_update_interval;
};

#endif // #ifndef _MAIN_SERVICE_H_
