#ifndef IMAGE_H
#define IMAGE_H

#include "graphics/Texture.hpp"
#include "gui/Gui.hpp"

class Image : public Gui {
  private:
	Texture *texture;

  public:
	Image(Texture *texture);
	Image(Texture *texture, int width, int height);

	virtual void update(double delta);
	virtual void render(Renderer &renderer);
};

#endif
