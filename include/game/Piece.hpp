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
	int x, y, width, height;

	void calculateBounds();

  public:
	Piece(std::vector<array<int, 4>> shapes);
	virtual void init(Renderer &renderer);
	virtual void update(double delta);
	virtual void render(Renderer &renderer);
	virtual void resize(int width, int height);
	virtual void dispose();

	array<array<int, 4>, 4> getCurrentShape();

	void rotate();
	void invRotate();
	void setX(int x);
	void setY(int y);
	void setPosition(int x, int y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void print();
};

#endif
