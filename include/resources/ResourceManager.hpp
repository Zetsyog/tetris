#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "graphics/Texture.hpp"
#include "resources/Music.hpp"
#include <unordered_map>
#include <vector>

class App;

class ResourceManager {
  private:
	App *app;
	std::unordered_map<std::string, Texture *> textures;
	std::unordered_map<std::string, Music *> musics;

	void registerTextures();
	void registerSounds();

  public:
	ResourceManager(App *app);
	~ResourceManager();

	void add(std::string id, Texture *resource);
	void add(std::string id, Music *resource);

	Texture *get(std::string id);
	Music *getMusic(std::string id);

	void unload(std::string id);
};

#endif
