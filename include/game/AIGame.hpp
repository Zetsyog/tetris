#ifndef AIGAME_H
#define AIGAME_H

#include "game/Game.hpp"

class AIGame : public Game {
  protected:
	double actionTimer;
	double botSpeed;
	int targetX, targetRotation;
	virtual void genNextPiece();
	int getMaxY(Piece &piece);
	int countEmptyBlocksUnder(
		Piece &piece,
		std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> &board);

	void updateTarget();

  public:
	AIGame(App &app);
	virtual void update(double delta);
	virtual void render(Renderer &renderer);

	virtual void addLine();
};

#endif
