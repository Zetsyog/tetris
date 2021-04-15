#include "App.hpp"
#include "gui/Screen.hpp"

int main(int argc, char **argv) {
	App *app = App::create();
	app->setCurrentScreen(new MainMenuScreen());
	int ret = app->start();
	App::destroy();
	return ret;
}