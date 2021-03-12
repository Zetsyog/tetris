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

/**
 * A class that represent the game and its logic
 */
class Game : public Drawable {
  private:
	/** Collection of piece that are available in the game */
	std::vector<Piece *> pieceAvailable;
	/** The game board that contains all the tetrominos blocks */
	std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> board;
	/** The current tetromino that is falling */
	Piece *currentPiece;
	/** The user score */
	int score;
	/** Tetromino falling speed */
	double speed;
	/** The frequency of falling tetromino update (1 per second) */
	double movementTimer;
	/** If the game is runnning or paused */
	bool running;

	Texture *tmp, *background;

	/** Copy current piece shape to the game board */
	void copyPieceToBoard(Piece &piece);
	/** Check if the given piece can fall down */
	bool canGoDown(Piece &piece);
	/** Check if there are complete lines in game board */
	void checkLine();
	/**
	 * Delete current piece and replace it with a new random one from
	 * availablePieces
	 */
	void nextPiece();
	/**
	 * Print the board in stdout
	 * Used for debug
	 */
	void printBoard();

  public:
	Game();
	~Game();
	/**
	 * Start the game
	 */
	void start();
	/** Pause the game */
	void pause();
	/** Resume the game */
	void resume();

	virtual void init(Renderer &renderer);
	virtual void update(double delta);
	virtual void render(Renderer &renderer);
	virtual void resize(int width, int height);
	virtual void dispose();

	/**
	 * Process a given action
	 * Action can be ACTION_MOVE_LEFT, ACTION_MOVE_RIGHT, ACTION_MOVE_DOWN,
	 * ACTION_DOWN, ACTION_ROTATE
	 * @param type
	 */
	void action(int type);

	/** Set tetromino falling speed	 */
	void setSpeed(double speed);

	/**
	 * Check if the given piece is at a valid location
	 * @param piece
	 * @return whether piece location is valid or not
	 */
	bool isValid(Piece &piece);

	/**
	 * @return board width in pixels
	 */
	int getWidth();

	/**
	 * @return board height in pixels
	 */
	int getHeight();
};

#endif
