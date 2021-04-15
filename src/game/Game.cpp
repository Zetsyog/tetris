#include "game/Game.hpp"
#include "App.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <array>
#include <chrono>
#include <ctime>
#include <random>

Game::Game(App &app)
	: pieceAvailable(), board(), score(0), timePerBlock(DEFAULT_SPEED),
	  movementTimer(0), running(false), currentPiece(nullptr), app(app),
	  nextPiece(nullptr), level(1), scoreGoal(500), finished(false),
	  ghost(nullptr), lineFilled(0), nextPieceIndex(0) {
	std::srand(std::time(nullptr));
	// I piece
	pieceAvailable.push_back(
		new Piece({{4, 5, 6, 7}, {2, 6, 10, 14}, {8, 9, 10, 11}, {1, 5, 9, 13}},
				  Color::get(COLOR_CYAN)));
	// J piece
	pieceAvailable.push_back(
		new Piece({{0, 4, 5, 6}, {1, 2, 5, 9}, {4, 5, 6, 10}, {1, 5, 8, 9}},
				  Color::get(COLOR_BLUE)));
	// L piece
	pieceAvailable.push_back(
		new Piece({{2, 4, 5, 6}, {1, 5, 9, 10}, {4, 5, 6, 8}, {0, 1, 5, 9}},
				  Color::get(COLOR_ORANGE)));
	// O piece
	pieceAvailable.push_back(
		new Piece({{1, 2, 5, 6}}, Color::get(COLOR_YELLOW)));
	// S piece
	pieceAvailable.push_back(
		new Piece({{1, 2, 4, 5}, {1, 5, 6, 10}, {5, 6, 8, 9}, {0, 4, 5, 9}},
				  Color::get(COLOR_GREEN)));
	// T piece
	pieceAvailable.push_back(
		new Piece({{1, 4, 5, 6}, {1, 5, 6, 9}, {4, 5, 6, 9}, {1, 4, 5, 9}},
				  Color::get(COLOR_PURPLE)));
	// Z piece
	pieceAvailable.push_back(
		new Piece({{0, 1, 5, 6}, {2, 5, 6, 9}, {4, 5, 9, 10}, {1, 4, 5, 8}},
				  Color::get(COLOR_RED)));

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	grid	   = app.getResourceManager().get("texture:grid");
	background = app.getResourceManager().get("texture:ui:panel:2");
	panel	   = app.getResourceManager().get("texture:ui:panel:3");
	title	   = app.getResourceManager().get("texture:ui:title:2");

	nextPieceGlyph = new FontGlyph("Next");
	scoreGlyph =
		new FontGlyph(std::string("Score: ").append(std::to_string(score)));
	levelGlyph =
		new FontGlyph(std::string("Level: ").append(std::to_string(level)));
}

void Game::start() {
	genNextPiece();

	resume();
}

void Game::pause() {
	running = false;
}

void Game::resume() {
	running = true;
}

void Game::update(double delta) {
	if (running && !finished) {
		if (lineFilled) {
			lineFilled = 0;
		}

		movementTimer += delta;

		if (movementTimer >= timePerBlock) {
			movementTimer -= timePerBlock;
			action(ACTION_MOVE_DOWN);
		}
	}
}

void Game::render(Renderer &renderer) {
	renderer.pushOrigin(x, y);
	renderer.draw(background, 0, 0, getWidth(), getHeight());

	renderer.pushOrigin(MARGIN, MARGIN);
	renderer.draw(grid, 0, 0, TILE_SIZE * BOARD_WIDTH,
				  TILE_SIZE * BOARD_HEIGHT);

	if (ghost != nullptr) {
		ghost->render(renderer);
	}
	if (currentPiece != nullptr) {
		currentPiece->render(renderer);
	}

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (board[i][j] != 0) {
				renderer.draw(Color::get(board[i][j]).getTexture(),
							  i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,
							  TILE_SIZE);
			}
		}
	}
	renderer.popOrigin();

	renderer.pushOrigin(TILE_SIZE * BOARD_WIDTH + MARGIN, MARGIN);
	renderNextPiece(renderer);
	renderer.popOrigin();

	renderer.pushOrigin(TILE_SIZE * BOARD_WIDTH + MARGIN, MARGIN + 400);
	renderScore(renderer);
	renderer.popOrigin();

	renderer.popOrigin();
}

void Game::renderNextPiece(Renderer &renderer) {
	renderer.draw(panel, MARGIN, 0, 250, 250);
	renderer.pushOrigin(MARGIN + 250 / 2, 250 / 2);

	renderer.draw(title, -200 / 2, 140, 200, 50);
	renderer.drawText(nextPieceGlyph, -nextPieceGlyph->getWidth() / 2, 150);
	renderer.drawRect(0, 0, 0, 0, 0, 0, 0, 0);

	renderer.pushOrigin(-(nextPiece->getWidth() * TILE_SIZE) / 2,
						-(nextPiece->getHeight() * TILE_SIZE) / 2);
	nextPiece->render(renderer);
	renderer.popOrigin();
	renderer.popOrigin();
}

void Game::renderScore(Renderer &renderer) {
	renderer.drawText(scoreGlyph, MARGIN, 0);
	renderer.drawText(levelGlyph, MARGIN, 100);
	renderer.drawRect(0, 0, 0, 0, 0, 0, 0, 0);
}

void Game::checkLine() {
	int lineCleared	 = 0;
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
			lineCleared++;
		}
	}
	this->lineFilled = lineCleared;
	updateScore(lineCleared);
}

void Game::updateScore(int lineCleared) {
	if (lineCleared == 1) {
		score += 100 * level;
	} else if (lineCleared == 2) {
		score += 300 * level;
	} else if (lineCleared == 3) {
		score += 500 * level;
	} else if (lineCleared == 4) {
		score += 800 * level;
	}

	if (score >= scoreGoal) {
		if (level < 20) {
			level++;
		}
		scoreGoal += 500 * level;
	}

	scoreGlyph->setText(std::string("Score: ").append(to_string(score)));
	levelGlyph->setText(std::string("Level: ").append(to_string(level)));
}

void Game::genNextPiece() {
	if (finished)
		return;
	if (currentPiece != nullptr) {
		delete currentPiece;
		delete ghost;
	}

	if (nextPiece == nullptr) {
		std::shuffle(pieceAvailable.begin(), pieceAvailable.end(),
					 std::default_random_engine(seed));
		nextPiece = new Piece(*pieceAvailable[nextPieceIndex]);
		nextPieceIndex++;
	}

	currentPiece = nextPiece;
	currentPiece->setPosition(4, 0);
	ghost = new Piece(*currentPiece);
	ghost->setGhost(true);
	ghost->setColor(Color::get(COLOR_GHOST));

	if (nextPieceIndex >= 7) {
		nextPieceIndex = 0;
		std::shuffle(pieceAvailable.begin(), pieceAvailable.end(),
					 std::default_random_engine(seed));
	}
	nextPiece = new Piece(*pieceAvailable[nextPieceIndex]);
	nextPiece->setPosition(0, 0);
	nextPieceIndex++;

	movementTimer = 0;

	if (!isValid(*currentPiece)) {
		finished = true;
		return;
	}
	updateGhost();
}

void Game::copyPieceToBoard(
	Piece &piece,
	std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> &board) {
	array<array<int, 4>, 4> shape = piece.getCurrentShape();
	for (int i = 0; i < 4; i++) {
		int tmpX = piece.getX() + i;
		if (tmpX < 0 || tmpX >= BOARD_WIDTH)
			continue;
		for (int j = 0; j < 4; j++) {
			int tmpY = piece.getY() + j;
			if (tmpY < 0 || tmpY >= BOARD_HEIGHT)
				continue;
			if (shape[i][j] == 1) {
				board[tmpX][tmpY] = piece.getColor().getId();
			}
		}
	}
}

void Game::action(int type) {
	if (type == ACTION_MOVE_LEFT) {
		currentPiece->setX(currentPiece->getX() - 1);
		if (!isValid(*currentPiece)) {
			currentPiece->setX(currentPiece->getX() + 1);
		}
		ghost->setX(currentPiece->getX());
		updateGhost();
	} else if (type == ACTION_MOVE_RIGHT) {
		currentPiece->setX(currentPiece->getX() + 1);
		if (!isValid(*currentPiece)) {
			currentPiece->setX(currentPiece->getX() - 1);
		}
		ghost->setX(currentPiece->getX());
		updateGhost();
	} else if (type == ACTION_MOVE_DOWN) {
		if (!canGoDown(*currentPiece)) {
			copyPieceToBoard(*currentPiece, board);
			checkLine();
			genNextPiece();
		} else {
			currentPiece->setY(currentPiece->getY() + 1);
		}
	} else if (type == ACTION_ROTATE) {
		currentPiece->rotate();
		ghost->rotate();
		if (!isValid(*currentPiece)) {
			currentPiece->invRotate();
			ghost->invRotate();
		}
		updateGhost();
	}
}

bool Game::canGoDown(Piece &piece) {
	array<array<int, 4>, 4> &shape = piece.getCurrentShape();

	for (int i = 0; i < 4; i++) {
		int j = 0;
		while (j < 4 && shape[i][j] == 0) {
			j++;
		}
		if (j < 4) {
			while (shape[i][j] != 0 && j < 4) {
				j++;
			}
			int x = piece.getX() + i;
			int y = piece.getY() + j;
			if (y >= BOARD_HEIGHT || board[x][y] != 0) {
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
					board[x][y] != 0) {
					return false;
				}
			}
		}
	}

	return true;
}

void Game::setSoftDrop(bool active) {
	double newTimePerBlock;
	if (active) {
		newTimePerBlock = std::pow((0.8 - ((20 - 1) * 0.007)), 20 - 1);
	} else {
		newTimePerBlock = std::pow((0.8 - ((level - 1) * 0.007)), level - 1);
	}
	movementTimer = (movementTimer * newTimePerBlock) * timePerBlock;
	timePerBlock  = newTimePerBlock;
}

int Game::getWidth() const {
	return TILE_SIZE * BOARD_WIDTH + 2 * MARGIN + 300;
}

int Game::getHeight() const {
	return TILE_SIZE * BOARD_HEIGHT + 2 * MARGIN;
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

void Game::updateGhost() {
	if (finished)
		return;
	ghost->setY(currentPiece->getY());
	while (isValid(*ghost)) {
		ghost->setY(ghost->getY() + 1);
	}
	ghost->setY(ghost->getY() - 1);
}

bool Game::isDone() {
	return finished;
}

int Game::getScore() {
	return score;
}

int Game::getLineFilled() {
	return lineFilled;
}

void Game::addLine() {
	for (int j = 0; j < BOARD_HEIGHT - 1; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			board[i][j] = board[i][j + 1];
		}
	}

	int r = std::rand() / ((RAND_MAX + 1u) / BOARD_WIDTH);
	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (i != r)
			board[i][BOARD_HEIGHT - 1] = COLOR_GRAY;
		else
			board[i][BOARD_HEIGHT - 1] = 0;
	}
}

Game::~Game() {
	delete nextPieceGlyph;
	delete scoreGlyph;
	delete levelGlyph;

	for (const auto &piece : pieceAvailable) {
		delete piece;
	}
	if (currentPiece != nullptr) {
		delete currentPiece;
	}
	if (nextPiece != nullptr) {
		delete nextPiece;
	}
	if (ghost != nullptr) {
		delete ghost;
	}
}
