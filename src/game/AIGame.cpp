#include "game/AIGame.hpp"

AIGame::AIGame(App &app)
	: Game::Game(app), targetX(0), botSpeed(0.4), actionTimer(0) {
}

void AIGame::genNextPiece() {
	Game::genNextPiece();
	Piece *target  = new Piece(*currentPiece);
	targetX		   = 0;
	int targetY	   = 0;
	int maxY	   = 0;
	targetRotation = 0;
	int emptyScore = 500;

	int bestLineCompleted = 0;
	// for each rotation
	for (int i = 0; i < 4; i++) {
		// for each x
		for (int x = -2; x < BOARD_WIDTH - target->getWidth() + 1; x++) {
			target->setY(0);
			target->setX(x);
			// We move target down to the max valid position
			while (isValid(*target)) {
				target->setY(target->getY() + 1);
			}
			target->setY(target->getY() - 1);
			std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> tmpBoard(
				board);

			array<array<int, 4>, 4> shape = target->getCurrentShape();

			copyPieceToBoard(*target, tmpBoard);

			int completedLines = 0;
			for (int y = 0; y < BOARD_HEIGHT; y++) {
				int lineComplete = 1;
				for (int x = 0; x < BOARD_WIDTH; x++) {
					if (tmpBoard[x][y] == 0) {
						lineComplete = 0;
						break;
					}
				}
				if (lineComplete) {
					completedLines++;
				}
			}
			int tmpScore = countEmptyBlocksUnder(*target, tmpBoard);

			if (completedLines > bestLineCompleted) {
				bestLineCompleted = completedLines;
				targetRotation	  = target->getRotationId();
				targetX			  = target->getX();
				targetY			  = target->getY();
				maxY			  = getMaxY(*target);
				emptyScore		  = tmpScore;
			} else if (completedLines == bestLineCompleted) {
				if (tmpScore < emptyScore) {
					targetRotation = target->getRotationId();
					targetX		   = target->getX();
					targetY		   = target->getY();
					maxY		   = getMaxY(*target);
					emptyScore	   = tmpScore;
				} else if (getMaxY(*target) > maxY) {
					targetRotation = target->getRotationId();
					targetX		   = target->getX();
					targetY		   = target->getY();
					maxY		   = getMaxY(*target);
					emptyScore	   = tmpScore;
				}
			}
		}

		target->rotate();
	}
	setSoftDrop(false);
	delete target;
}

int AIGame::countEmptyBlocksUnder(
	Piece &piece,
	std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> &board) {

	int count					  = 0;
	array<array<int, 4>, 4> shape = piece.getCurrentShape();
	bool xDone[4]				  = {false};

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (shape[x][y] == 1) {
				if (!xDone[x]) {
					int j = y;
					while (j < 4 && shape[x][j] != 0)
						j++;

					for (int i = j + piece.getY(); i < BOARD_HEIGHT; i++) {
						if (board[piece.getX() + x][i] == 0) {
							count++;
						} else {
							break;
						}
					}
					xDone[x] = true;
				}
			}
		}
	}
	return count;
}

int AIGame::getMaxY(Piece &piece) {
	array<array<int, 4>, 4> shape = piece.getCurrentShape();
	int max						  = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shape[i][j] == 1) {
				if (j > max)
					max = j;
			}
		}
	}
	return max + piece.getY();
}

void AIGame::update(double delta) {
	Game::update(delta);

	if (running && !finished) {
		actionTimer += delta;

		if (actionTimer >= botSpeed) {
			actionTimer -= botSpeed;
			if (currentPiece->getRotationId() != targetRotation) {
				action(ACTION_ROTATE);
			} else {
				if (currentPiece->getX() < targetX) {
					action(ACTION_MOVE_RIGHT);
				} else if (currentPiece->getX() > targetX) {
					action(ACTION_MOVE_LEFT);
				} else {
					setSoftDrop(true);
				}
			}
		}
	}
}

void AIGame::render(Renderer &renderer) {
	Game::render(renderer);
}
