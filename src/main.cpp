#include "App.hpp"
#include "gui/Screen.hpp"

int main(int argc, char **argv) {
	App *app = new App();
	app->setCurrentScreen(new GameScreen());
	int ret = app->start();
	delete app;
	return ret;
}