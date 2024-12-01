// vim:tw=78
#ifndef MINESWEEPER_TILE_H_
#define MINESWEEPER_TILE_H_

#include <array>
#include <SFML/Graphics.hpp>

//----------------------------------------------------------------------------
// Tile Class
//----------------------------------------------------------------------------
//
// This class implements the tile widgets that make up the board. The class
// can be optionally subclassed to further encapsulate special traits. Each
// tile's neighbor configuration can vary (see Figure 1). When a tile is
// adjacent to the edge of the board, the neighbor pointer should be a nullptr
// value.

class Tile : public sf::Drawable
{
public:
  // Represents tile's current UI state (visualization).
  enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };

public:
  // Constructs a new tile object at the designated _position.
  Tile(sf::Vector2f position);
  // Returns the position of this tile.
  sf::Vector2f getLocation(); // ???
  // Returns current state of this tile.
  State getState();
  // Returns pointer to array of Tile pointers (see Figure 2 for ordering).
  std::array<Tile*, 8>& getNeighbors();
  // Sets the state of this tile. Should trigger other behaviors related to
  // the state change (including visualization).
  void setState(State state);
  // Populates / replaces the neighboring tile container.
  void setNeighbors(std::array<Tile*, 8> neighbors);
  // Defines the reveal behavior for a tile when the left mouse button is
  // clicked inside its boundaries.
  void onClickLeft();
  // Toggles this tile's state between FLAGGED and HIDDEN.
  void onClickRight();
  // Render this tile to the screen according to is state.
  void draw();

protected:
  // Based on State and mine content of the tile neighbors, set their state to
  // REVEALED.
  void revealNeighbors();

  /**************************************************************************/

private:
  sf::Vector2f _position;
  bool _mine;
  State _state;
  std::array<Tile*, 8> _neighbors;
  bool _has_content;
  sf::Sprite _base_sprite;
  sf::Sprite _debug_sprite;
  sf::Sprite _content_sprite;

  void reveal_cascade();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
  Tile();
  void init(sf::Vector2f position, bool mine, const std::array<Tile*, 8>& neighbors);
  void reveal();
  void flag();
};

#endif