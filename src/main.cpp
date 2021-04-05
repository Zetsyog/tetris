#include "App.hpp"
#include "gui/Screen.hpp"

int main(int argc, char **argv) {
	App *app = App::getInstance();
	app->init();
	app->setCurrentScreen(new GameScreen());
	int ret = app->start();
	delete app;
	return ret;
}