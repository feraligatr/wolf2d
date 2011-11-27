#include "server_pch.h"

#include "MainService.h"

int main(int argc, char *argv[])
{
	pi::pi_init();
	MainService ms;
	RETURN_IF_ERROR(ms.init());
	RETURN_IF_ERROR(ms.run());
	ms.destroy();

	return 0;
}