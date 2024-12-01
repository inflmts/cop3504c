// vim:tw=78
#ifndef MINESWEEPER_GAMESTATE_H_
#define MINESWEEPER_GAMESTATE_H_

#include <SFML/Graphics.hpp>
#include "Tile.h"

//----------------------------------------------------------------------------
// GameState Class
//----------------------------------------------------------------------------
//
// The GameState object should contain the Tile objects that represent the
// locations in the game and play status.

class GameState
{
public:
  // Tracks the play status of the game, which is reflected in the behavior of
  // the user interface and visualizations.
  enum PlayStatus { WIN, LOSS, PLAYING };
  // Constructs a new random game state with specified tile _dimensions and
  // the specified _numberOfMines.
  GameState(sf::Vector2i dim = sf::Vector2i(25, 16), int mine_count = 50);
  // Constructs a game state based on the size, mine placement, and mine
  // number specified at filepath.
  GameState(const char *filepath);
  // Current count of the number of flags placed on the screen.
  int getFlagCount();
  // Current count of the number of mines actually on the board.
  int getMineCount();
  // Returns a pointer to the Tile at the specified coordinates, or nullptr if
  // out of bounds.
  Tile *getTile(int x, int y);
  // Returns the play status of the game.
  PlayStatus getPlayStatus();
  // Sets the play status of the game.
  void setPlayStatus(PlayStatus status);

  /**************************************************************************/

private:
  int _width;
  int _height;
  PlayStatus _status;
  int _flag_count;
  int _mine_count;
  int _hidden_count;
  Tile *_tiles;
  Tile *_tiles_end;
  unsigned int _shake;

  sf::Transform _transform;
  sf::Transform _inverse_transform;

  void init(int width, int height, char *grid);

public:
  ~GameState();
  void update_transform();
  //const sf::Transform& transform();
  //const sf::Transform& inverse_transform();
  bool click(const sf::Event::MouseButtonEvent& event);
  void adjust_flag_count(int diff);
  void decrement_hidden_count();
  void win();
  void lose();
  void render(sf::RenderStates states);
};

#endif
