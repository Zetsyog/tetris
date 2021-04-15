#include "resources/ResourceManager.hpp"
#include "App.hpp"
#include "graphics/Color.hpp"

#include <iostream>

using namespace std;

ResourceManager::ResourceManager(App *app) : app(app) {
	registerTextures();
	registerSounds();
}

void ResourceManager::registerSounds() {
	add("music:main", new Music("assets/sound/tetris_sound.wav"));
}

void ResourceManager::registerTextures() {
	Renderer &r = app->getRenderer();

	add("texture:background", new Texture(r, "assets/texture/background.png"));
	add("texture:ui:panel:2",
		new Texture(r, "assets/texture/ui/MainPanel02.png"));
	add("texture:ui:panel:3", new Texture(r, "assets/texture/ui/panel.png"));
	add("texture:ui:title:2",
		new Texture(r, "assets/texture/ui/TitlePanel02.png"));
	add("texture:grid", new Texture(r, "assets/texture/grid.png"));
	add("texture:logo", new Texture(r, "assets/texture/logo.png"));

	add("texture:block:blue", new Texture(r, "assets/texture/block/blue.png"));
	add("texture:block:cyan", new Texture(r, "assets/texture/block/cyan.png"));
	add("texture:block:green",
		new Texture(r, "assets/texture/block/green.png"));
	add("texture:block:orange",
		new Texture(r, "assets/texture/block/orange.png"));
	add("texture:block:purple",
		new Texture(r, "assets/texture/block/purple.png"));
	add("texture:block:red", new Texture(r, "assets/texture/block/red.png"));
	add("texture:block:yellow",
		new Texture(r, "assets/texture/block/yellow.png"));
	add("texture:block:ghost",
		new Texture(r, "assets/texture/block/ghost.png"));
	add("texture:block:gray", new Texture(r, "assets/texture/block/ghost.png"));

	Color::init(*this);
}

void ResourceManager::add(std::string id, Texture *resource) {
	if (textures.find(id) != textures.end()) {
		return;
	}
	textures[id] = resource;
}

void ResourceManager::add(std::string id, Music *resource) {
	if (musics.find(id) != musics.end()) {
		return;
	}
	musics[id] = resource;
}

Texture *ResourceManager::get(std::string id) {
	if (textures.find(id) == textures.end()) {
		cout << "can't find texture " << id << endl;
		return nullptr;
	}
	return textures[id];
}

Music *ResourceManager::getMusic(std::string id) {
	if (musics.find(id) == musics.end()) {
		cout << "can't find music " << id << endl;
		return nullptr;
	}
	return musics[id];
}

ResourceManager::~ResourceManager() {
	for (auto &it : textures) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}

	for (auto &it : musics) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
}
