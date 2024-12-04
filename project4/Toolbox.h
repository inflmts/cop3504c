// vim:tw=78
#ifndef MINESWEEPER_TOOLBOX_H_
#define MINESWEEPER_TOOLBOX_H_

#include <memory>
#include <random>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"
#include "Toolbox.h"

//----------------------------------------------------------------------------
// Toolbox Class
//----------------------------------------------------------------------------
//
// A toolbox class is often used to contain variables that would otherwise be
// accessed throughout an application; it is a mechanism to avoid truly global
// variables. The Toolbox class will be a singleton (class with only one
// instance) and will contain at least the following attributes and methods:

class Toolbox
{
  // Default constructor; should be accessible only from within the class
  // itself. This method initializes the buttons, window, game board, and any
  // other elements necessary to play the game.
  Toolbox();

public:
  sf::RenderWindow window; // SFML application window
  GameState *gameState;    // Primary game state representation
  Button *debugButton;     // Reveals mines in debug mode
  Button *newGameButton;   // Resets / starts new game
  Button *testButton1;     // Loads test board #1
  Button *testButton2;     // Loads test board #2

  // Returns a reference to the singular Toolbox instance.
  static Toolbox& getInstance();

  /**************************************************************************/

private:
  bool _debug;
  void reset(GameState *g);
  void load_image(sf::Image& image, const char *filename);
  void load_texture(sf::Texture& texture, const char *filename);
  void load_texture(sf::Texture& texture, const sf::Image& image);

public:
  std::unique_ptr<GameState> game;
  std::mt19937 random;
  float dt;

  // I was told this is kosher.
  struct {
    sf::Texture mine;
    sf::Texture mine_debug;
    sf::Texture tile_hidden;
    sf::Texture tile_revealed;
    sf::Texture number[8];
    sf::Texture flag;
    sf::Texture face_happy;
    sf::Texture face_win;
    sf::Texture face_lose;
    sf::Texture digits;
    sf::Texture debug;
    sf::Texture test1;
    sf::Texture test2;
    sf::Texture test3;
  } textures;

  struct {
    Button debug;
    Button restart;
    Button test1;
    Button test2;
    Button test3;
  } buttons;

  sf::Sprite flag_counter[3];

  void launch();
  void reset_random();
  void reset_from_file(const char *filename);
  void render();

  void update_view();
  void update_flag_counter();
  bool debug();
  void debug(bool debug);
  void toggle_debug();
  float randomfloat(float a, float b);

  static Toolbox instance;
};

#endif
