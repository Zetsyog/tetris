#include "App.hpp"
#include "gui/Screen.hpp"

int main(int argc, char **argv) {
	App app;
	app.init();
	app.setCurrentScreen(new MainScreen());
	return app.start();
}