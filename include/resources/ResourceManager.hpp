#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "graphics/Texture.hpp"
#include <unordered_map>
#include <vector>

class App;

class ResourceManager {
  private:
	App *app;
	std::unordered_map<std::string, Texture *> textures;

	void registerTextures();
	void registerSounds();

  public:
	ResourceManager(App *app);
	~ResourceManager();

	void add(std::string id, Texture *resource);

	Texture *get(std::string id);

	void unload(std::string id);
};

#endif
