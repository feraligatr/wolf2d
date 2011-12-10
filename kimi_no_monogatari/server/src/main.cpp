#include "pch/pch.h"

#include "../dummy/DummyServer.h"
#include "MainService.h"
#include "server_pi.h"

int main(int argc, char *argv[])
{
	pi::pi_init();
	DummyServer ds;
	MainService ms(ds);
	RETURN_IF_ERROR(ms.init());
	RETURN_IF_ERROR(ms.run());
	ms.destroy();

	return 0;
}