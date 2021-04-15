#ifndef GAME_H
#define GAME_H

#include "game/Piece.hpp"
#include "gui/Gui.hpp"
#include <array>
#include <vector>

#define DEFAULT_SPEED 1
#define TILE_SIZE 32
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 22
#define MARGIN 40

#define ACTION_MOVE_LEFT 0
#define ACTION_MOVE_RIGHT 1
#define ACTION_MOVE_DOWN 2
#define ACTION_ROTATE 3

class App;

/**
 * A class that represent the game and its logic
 */
class Game : public Gui {
  protected:
	App &app;

	/** Collection of piece that are available in the game */
	std::vector<Piece *> pieceAvailable;
	/** The game board that contains all the tetrominos blocks */
	std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> board;
	/** The current tetromino that is falling */
	Piece *currentPiece, *nextPiece, *ghost;
	/** The user score */
	int score;
	int scoreGoal;
	/** The user current level (ie difficulty) */
	int level;
	/** Tetromino falling speed */
	double timePerBlock;
	/** The frequency of falling tetromino update (1 per second) */
	double movementTimer;
	/** If the game is runnning or paused */
	bool running;

	bool finished;

	int lineFilled;

	Texture *background, *grid, *panel, *title;

	FontGlyph *nextPieceGlyph, *scoreGlyph, *levelGlyph;

	int nextPieceIndex;
	unsigned int seed;

	/** Copy current piece shape to the game board */
	void copyPieceToBoard(
		Piece &piece,
		std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> &board);
	/** Check if the given piece can fall down */
	bool canGoDown(Piece &piece);
	/** Check if there are complete lines in game board */
	void checkLine();
	/**
	 * Delete current piece and replace it with a new random one from
	 * availablePieces
	 */
	virtual void genNextPiece();
	/**
	 * Print the board in stdout
	 * Used for debug
	 */
	void printBoard();

	void updateGhost();

	void updateScore(int lineCleared);

	void renderNextPiece(Renderer &renderer);
	void renderScore(Renderer &renderer);

  public:
	Game(App &app);
	virtual ~Game();
	/**
	 * Start the game
	 */
	void start();
	/** Pause the game */
	void pause();
	/** Resume the game */
	void resume();

	virtual void update(double delta);
	virtual void render(Renderer &renderer);

	/**
	 * Process a given action
	 * Action can be ACTION_MOVE_LEFT, ACTION_MOVE_RIGHT, ACTION_MOVE_DOWN,
	 * ACTION_DOWN, ACTION_ROTATE
	 * @param type
	 */
	void action(int type);

	/** Set tetromino droping	 */
	void setSoftDrop(bool active);

	/**
	 * Check if the given piece is at a valid location
	 * @param piece
	 * @return whether piece location is valid or not
	 */
	bool isValid(Piece &piece);

	bool isDone();

	int getScore();

	int getLineFilled();

	void addLine();

	/**
	 * @return board width in pixels
	 */
	virtual int getWidth() const;

	/**
	 * @return board height in pixels
	 */
	virtual int getHeight() const;
};

#endif
