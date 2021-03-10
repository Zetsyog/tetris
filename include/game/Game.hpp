#ifndef GAME_H
#define GAME_H

#include "game/Piece.hpp"
#include "graphics/Drawable.hpp"
#include <array>
#include <vector>

#define DEFAULT_SPEED 1
#define TILE_SIZE 32
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 22

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define DIRECTION_BOTTOM 2

class Game : public Drawable {
  private:
	std::vector<Piece *> pieceAvailable;
	std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT> board;
	Piece *currentPiece;
	int score;
	int speed;
	double movementTimer;
	bool running;

  public:
	Game();
	~Game();
	void start();
	void pause();
	void resume();

	virtual void init(Renderer &renderer);
	virtual void update(double delta);
	virtual void render(Renderer &renderer);
	virtual void resize(int width, int height);
	virtual void dispose();

	void movePiece(int direction);

	bool isValid();
	int getWidth();
	int getHeight();
};

#endif
