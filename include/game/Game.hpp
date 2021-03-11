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

#define ACTION_MOVE_LEFT 0
#define ACTION_MOVE_RIGHT 1
#define ACTION_DOWN 2
#define ACTION_ROTATE 3
#define ACTION_MOVE_DOWN 4

class Game : public Drawable {
  private:
	std::vector<Piece *> pieceAvailable;
	std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> board;
	Piece *currentPiece;
	int score;
	double speed;
	double movementTimer;
	bool running;
	Texture *tmp, *background;

	void copyPieceToBoard(Piece &piece);
	bool canGoDown(Piece &piece);
	void checkLine();
	void nextPiece();
	void printBoard();

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

	void action(int type);

	void setSpeed(double speed);

	bool isValid(Piece &piece);
	int getWidth();
	int getHeight();
};

#endif
