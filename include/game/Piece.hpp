#ifndef PIECE_H
#define PIECE_H

#include "graphics/Color.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Texture.hpp"
#include <array>
#include <vector>

using namespace std;

/**
 * Represents a tetromino
 */
class Piece : public Drawable {
  private:
	/**
	 * List of tetrominos shapes
	 * The tetrominate iterate through this list for rotation
	 */
	vector<array<array<int, 4>, 4>> shapes;

	/** Index of current shape in shapes collection */
	int currentShape;

	/** X coordinate on the board */
	int x;
	/** Y coordinate on the board */
	int y;
	/** Width of current shape */
	int width;
	/** Height of current shape */
	int height;

	Color color;

	/** Calculate current shape width and height */
	void calculateBounds();

  public:
	/**
	 * Create a new tetromino
	 * Shape is a collection of array of 4 int
	 * Each array is a tetromino shape where each int define the cell index
	 * where there is a block
	 * Indexes are as it follows :
	 * 0  1  2  3
	 * 4  5  6  7
	 * 8  9  10 11
	 * 12 13 14 15
	 * @param shapes
	 */
	Piece(std::vector<array<int, 4>> shapes, Color color);

	virtual void update(double delta);
	virtual void render(Renderer &renderer);
	virtual void resize(int width, int height);

	/** Return current shape */
	array<array<int, 4>, 4> getCurrentShape();

	/**
	 * @brief Rotate this tetromino
	 * This methods only increment currentShape, modulo the size of shapes
	 */
	void rotate();

	/**
	 * @brief Rotate this termino in inverse order
	 * Decrements currentShape, module the size of shapes
	 */
	void invRotate();

	/** Set x position */
	void setX(int x);
	/** Set y position */
	void setY(int y);

	/** Set position */
	void setPosition(int x, int y);

	void setColor(Color color);
	Color getColor();

	/**
	 * @return x position in board coordinate
	 */
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void print();
};

#endif
