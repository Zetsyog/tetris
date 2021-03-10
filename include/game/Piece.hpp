#ifndef PIECE_H
#define PIECE_H

#include "graphics/Drawable.hpp"
#include "graphics/Texture.hpp"
#include <array>
#include <vector>

using namespace std;
class Piece : public Drawable {
  private:
	vector<array<array<int, 4>, 4>> shapes;
	Texture *tmp;
	int currentShape;

  public:
	Piece(std::vector<array<int, 4>> shapes);
	virtual void init(Renderer &renderer);
	virtual void update(double delta);
	virtual void render(Renderer &renderer);
	virtual void resize(int width, int height);
	virtual void dispose();

	void rotate();
};

#endif
