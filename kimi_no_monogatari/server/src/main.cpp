#include "server_pch.h"

#include "../dummy/DummyServer.h"
#include "MainService.h"

int main(int argc, char *argv[])
{
	pi::pi_init();
	DummyServer ds;
	MainService ms(&ds);
	RETURN_IF_ERROR(ms.init());
	RETURN_IF_ERROR(ms.run());
	ms.destroy();

	return 0;
}