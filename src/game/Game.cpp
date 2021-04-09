#include "game/Game.hpp"

Game::Game()
	: pieceAvailable(), board(), score(0), speed(DEFAULT_SPEED),
	  movementTimer(0), running(false), currentPiece(nullptr) {
	// T piece
	pieceAvailable.push_back(
		new Piece({{0, 4, 8, 9}, {4, 5, 6, 9}, {2, 6, 10, 5}, {5, 8, 9, 10}}));
	// L piece
	pieceAvailable.push_back(
		new Piece({{0, 4, 5, 8}, {4, 5, 6, 8}, {0, 1, 5, 9}, {2, 4, 5, 6}}));
	pieceAvailable.push_back(
		new Piece({{1, 5, 8, 9}, {0, 4, 5, 6}, {1, 2, 5, 9}, {4, 5, 6, 10}}));
	// O piece
	pieceAvailable.push_back(
		new Piece({{0, 1, 4, 5}}));
	// S piece
	pieceAvailable.push_back(
		new Piece({{0, 1, 5, 6}, {1, 5, 4, 8}}));
	pieceAvailable.push_back(
		new Piece({{1, 2, 4, 5}, {1, 5, 6, 10}}));
	// I piece
	pieceAvailable.push_back(
		new Piece({{0, 4, 8, 12}, {4, 5, 6, 7}}));
	

}

Game::~Game() {
}

void Game::start() {
	nextPiece();

	resume();
}

void Game::pause() {
	running = false;
}

void Game::resume() {
	running = true;
}

void Game::init(Renderer &renderer) {
	tmp		   = new Texture(renderer, "assets/texture/block/blue.png");
	background = new Texture(renderer, "assets/texture/background.png");
	for (const auto &piece : pieceAvailable) {
		piece->init(renderer);
	}
}

void Game::update(double delta) {
	if (running) {
		movementTimer += delta;

		if (movementTimer > 1 / speed) {
			movementTimer -= 1 / speed;
			action(ACTION_MOVE_DOWN);
		}
	}
}

void Game::render(Renderer &renderer) {
	renderer.draw(background, 0, 0, TILE_SIZE * BOARD_WIDTH,
				  TILE_SIZE * BOARD_HEIGHT);
	if (currentPiece != nullptr) {
		currentPiece->render(renderer);
	}

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (board[i][j] == 1) {
				renderer.draw(tmp, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,
							  TILE_SIZE);
			}
		}
	}
}

void Game::resize(int width, int height) {
}

void Game::checkLine() {
	// TODO
	int y;
	for (y=0; y<22; y++) {
		if(board[0][y] == board[1][y] == board[2][y] == board[3][y] == board[4][y] ==
			board[5][y] == board[6][y] == board[7][y] == board[8][y] == board[9][y]== 1)
				board[0][y] = board[1][y] = board[2][y] = board[3][y] = board[4][y] =
				board[5][y] = board[6][y] = board[7][y] = board[8][y] = board[9][y] = O;
	} 
}

void Game::nextPiece() {
	if (currentPiece != nullptr) {
		currentPiece->dispose();
		delete currentPiece;
	}
	// TODO : real random piece
	currentPiece = new Piece(*pieceAvailable[std::rand()%7]);
	currentPiece->setPosition(4, 0);
}

void Game::copyPieceToBoard(Piece &piece) {
	array<array<int, 4>, 4> shape = piece.getCurrentShape();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shape[i][j] == 1) {
				board[piece.getX() + i][piece.getY() + j] = 1;
			}
		}
	}
}

void Game::action(int type) {
	if (type == ACTION_MOVE_LEFT) {
		currentPiece->setX(currentPiece->getX() - 1);
		if (!isValid(*currentPiece))
			currentPiece->setX(currentPiece->getX() + 1);
	} else if (type == ACTION_MOVE_RIGHT) {
		currentPiece->setX(currentPiece->getX() + 1);
		if (!isValid(*currentPiece))
			currentPiece->setX(currentPiece->getX() - 1);
	} else if (type == ACTION_MOVE_DOWN) {
		if (!canGoDown(*currentPiece)) {
			copyPieceToBoard(*currentPiece);
			checkLine();
			nextPiece();
		} else {
			currentPiece->setY(currentPiece->getY() + 1);
		}
	} else if (type == ACTION_DOWN) {

	} else if (type == ACTION_ROTATE) {
		currentPiece->rotate();
		if (!isValid(*currentPiece))
			currentPiece->invRotate();
	}
}

bool Game::canGoDown(Piece &piece) {
	array<array<int, 4>, 4> shape = piece.getCurrentShape();

	for (int i = 0; i < 4; i++) {
		int j = 0;
		while (shape[i][j] == 0 && j < 4) {
			j++;
		}
		if (j < 4) {
			while (shape[i][j] == 1 && j < 4) {
				j++;
			}
			int x = piece.getX() + i;
			int y = piece.getY() + j;
			if (y >= BOARD_HEIGHT || board[x][y] == 1) {
				return false;
			}
		}
	}
	return true;
}

bool Game::isValid(Piece &piece) {
	array<array<int, 4>, 4> shape = piece.getCurrentShape();
	int x, y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shape[i][j] == 1) {
				x = piece.getX() + i;
				y = piece.getY() + j;
				if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT ||
					board[x][y] == 1) {
					return false;
				}
			}
		}
	}

	return true;
}

void Game::setSpeed(double speed) {
	this->speed = speed;
}

int Game::getWidth() {
	return TILE_SIZE * BOARD_WIDTH;
}

int Game::getHeight() {
	return TILE_SIZE * BOARD_HEIGHT;
}

void Game::printBoard() {
	Piece &piece				  = *currentPiece;
	array<array<int, 4>, 4> shape = piece.getCurrentShape();

	cout << "------------------" << endl;

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i >= piece.getY() && i < piece.getY() + 4 &&
				j >= piece.getX() && j < piece.getX() + 4 &&
				shape[j - piece.getX()][i - piece.getY()] == 1) {
				cout << "2 ";
			} else {
				cout << board[j][i] << " ";
			}
		}
		cout << endl;
	}
}

void Game::dispose() {
	for (const auto &piece : pieceAvailable) {
		piece->dispose();
		delete piece;
	}
	currentPiece->dispose();
	tmp->dispose();
	background->dispose();
	delete background;
	delete tmp;
	delete currentPiece;
}