// vim:tw=78
#ifndef MINESWEEPER_H_
#define MINESWEEPER_H_

#include "GameState.h"

//----------------------------------------------------------------------------
// Global Functions
//----------------------------------------------------------------------------
//
// A proper implementation will also include the following functions in global
// scope (not in a class). Except for main(), these functions should be
// prototyped in the minesweeper.h header file:

// This method is invoked directly by main() and is responsible for the game's
// launch. It should be possible to directly invoke this function after
// including the submitted source and header files in the test suite.
int launch();

// Resets all states/objects and generates a default game state (random board)
// and turns off debug mode if active. The new state should be a default game
// state (25x16 with 50 randomly placed mines).
void restart();

// Draws the all UI elements according to the current gameState and debug mode.
void render();

// Flips the debug mode on/off. (Debug mode should initially be off/false.)
void toggleDebugMode();

// Returns the true if debug mode is active, and false otherwise.
bool getDebugMode();

/****************************************************************************/

#endif
