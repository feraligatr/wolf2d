#ifndef _MAIN_SERVICE_H_
#define _MAIN_SERVICE_H_

typedef int time_ms_t;

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

	static const time_ms_t m_update_interval = 100;
	time_ms_t getCurrentTime();
	void rest(time_ms_t rest_time);
};

#endif // #ifndef _MAIN_SERVICE_H_
