#ifndef GAME_H
#define GAME_H

#include "game/Piece.hpp"
#include <vector>

class Game {
  private:
	std::vector<Piece> pieceAvailable;
	int score;

  public:
	Game();
	~Game();
	void start();
	void pause();
	void update(double delta);
	void resume();
};

#endif
