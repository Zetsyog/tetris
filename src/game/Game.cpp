#include "game/Game.hpp"
#include "App.hpp"

Game::Game(App &app)
	: pieceAvailable(), board(), score(0), speed(DEFAULT_SPEED),
	  movementTimer(0), running(false), currentPiece(nullptr), app(app) {
	// T piece
	pieceAvailable.push_back(
		new Piece({{0, 4, 5, 8}, {4, 5, 6, 9}, {2, 6, 10, 5}, {5, 8, 9, 10}},
				  app.getResourceManager().get("texture:block:blue")));
	// L piece
	pieceAvailable.push_back(
		new Piece({{0, 4, 8, 9}, {4, 5, 6, 8}, {0, 1, 5, 9}, {2, 4, 5, 6}},
				  app.getResourceManager().get("texture:block:blue")));
	pieceAvailable.push_back(
		new Piece({{1, 5, 8, 9}, {0, 4, 5, 6}, {1, 2, 5, 9}, {4, 5, 6, 10}},
				  app.getResourceManager().get("texture:block:blue")));
	// O piece
	pieceAvailable.push_back(new Piece(
		{{0, 1, 4, 5}}, app.getResourceManager().get("texture:block:blue")));
	// S piece
	pieceAvailable.push_back(
		new Piece({{0, 1, 5, 6}, {1, 5, 4, 8}},
				  app.getResourceManager().get("texture:block:blue")));
	pieceAvailable.push_back(
		new Piece({{1, 2, 4, 5}, {1, 5, 6, 10}},
				  app.getResourceManager().get("texture:block:blue")));
	// I piece
	pieceAvailable.push_back(
		new Piece({{0, 4, 8, 12}, {4, 5, 6, 7}},
				  app.getResourceManager().get("texture:block:blue")));

	tmp		   = app.getResourceManager().get("texture:block:blue");
	background = app.getResourceManager().get("texture:background");
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

void Game::update(double delta) {
	if (running) {
		movementTimer += delta;

		if (movementTimer >= 1 / speed) {
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
	int lineComplete = 0;
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		lineComplete = 1;
		for (int x = 0; x < BOARD_WIDTH; x++) {
			if (board[x][y] == 0) {
				lineComplete = 0;
				break;
			}
		}
		if (lineComplete) {
			for (int x = 0; x < BOARD_WIDTH; x++) {
				board[x][y] = 0;
				for (int i = y; i > 1; i--) {
					board[x][i] = board[x][i - 1];
				}
			}
		}
	}
}
void Game::nextPiece() {
	if (currentPiece != nullptr) {
		delete currentPiece;
	}
	currentPiece = new Piece(*pieceAvailable[std::rand() % 7]);
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

Game::~Game() {
	for (const auto &piece : pieceAvailable) {
		delete piece;
	}
	delete currentPiece;
}