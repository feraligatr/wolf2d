#include "pch/pch.h"

#include "LuaTestWorld.h"


int main(int argc, char *argv[])
{
	init_global_logs();
	char buffer[1024];
	LuaTestWorld world;
	std::cout << "use lua as intepreter, world is global environment. " << std::endl;
	world.start();
	while(true)
	{
		std::cout << "$ ";
		std::cin.getline(buffer, 1024);
		world.runString(buffer);
	}
	return 0;
}

