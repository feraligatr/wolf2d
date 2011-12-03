#include "common.h"

#include "LuaTestWorld.h"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	char buffer[1024];
	LuaTestWorld world;
	std::cout << "use lua as intepreter, world is global environment. " << std::endl;
	world.start();
	while(true)
	{
		std::cout << "please input the command" << std::endl;
		std::cin.getline(buffer, 1024);
		world.runString(buffer);
	}
	return 0;
}

