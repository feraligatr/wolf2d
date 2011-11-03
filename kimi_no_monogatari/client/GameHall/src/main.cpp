#include "pch.h"
#include <QApplication>

#include "GameHallApplication.h"

GameHallApplication *g_app;

int main(int argc, char *argv[])
{
	g_app = new GameHallApplication(argc, argv);
	g_app->init();
	return g_app->run();
}
