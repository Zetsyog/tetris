#include "App.hpp"
#include "gui/Screen.hpp"

int main(int argc, char **argv) {
	App *app = App::create();
	app->setCurrentScreen(new GameOverScreen(50));
	int ret = app->start();
	App::destroy();
	return ret;
}