#ifndef COLOR_H
#define COLOR_H

#include "graphics/Texture.hpp"
#include "resources/ResourceManager.hpp"
#include <vector>

#define COLOR_FIRST_ID 1
#define COLOR_LAST_ID 7

#define COLOR_BLUE 1
#define COLOR_CYAN 2
#define COLOR_GREEN 3
#define COLOR_ORANGE 4
#define COLOR_PURPLE 5
#define COLOR_RED 6
#define COLOR_YELLOW 7

class Color {
  private:
	static std::vector<Color> colors;

	Texture *texture;
	int id;

  public:
	Color();
	Color(int colorId, Texture *texture);
	int getId() const;
	void setId(int id);
	Texture *getTexture() const;
	void setTexture(Texture *texture);

	static Color get(int id);
	static void init(ResourceManager &rm);
};

bool operator==(Color const &a, Color const &b);

#endif
