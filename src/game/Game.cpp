#include "game/Game.hpp"

Game::Game()
	: pieceAvailable(), board(), score(0), speed(DEFAULT_SPEED),
	  movementTimer(0), running(false) {
	// T piece
	pieceAvailable.push_back(
		new Piece({{0, 4, 5, 8}, {4, 5, 6, 9}, {2, 6, 10, 5}, {5, 8, 9, 10}}));
}

Game::~Game() {
}

void Game::start() {
	// TODO : real random piece
	currentPiece = new Piece(*pieceAvailable[0]);
	currentPiece->setPosition(4, 0);
	resume();
}

void Game::pause() {
	running = false;
}

void Game::resume() {
	running = true;
}

void Game::init(Renderer &renderer) {
}

void Game::update(double delta) {
	if (running) {
		movementTimer += delta;

		if (movementTimer > speed) {
			movementTimer -= speed;
			movePiece(DIRECTION_BOTTOM);
		}
	}
}

void Game::render(Renderer &renderer) {
}

void Game::resize(int width, int height) {
}

void Game::dispose() {
}

void Game::movePiece(int direction) {
}

bool Game::isValid() {
	return true;
}

int Game::getWidth() {
	return TILE_SIZE * BOARD_WIDTH;
}

int Game::getHeight() {
	return TILE_SIZE * BOARD_HEIGHT;
}
