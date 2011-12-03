#ifndef _TEST_CLIENT_H_
#define _TEST_CLIENT_H_

class TestClient
{
public:
	TestClient(boost::asio::io_service& io_service);

	bool isConnected();

private:
	bool m_isConnected;

};


#endif /* _TEST_SERVER_H_ */
