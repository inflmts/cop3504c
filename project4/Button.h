// vim:tw=78
#ifndef MINESWEEPER_BUTTON_H_
#define MINESWEEPER_BUTTON_H_

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>

//----------------------------------------------------------------------------
// Button Class
//----------------------------------------------------------------------------
//
// This class will be used to implement each button widget. Widgets are
// responsible for rending themselves, originating interaction (e.g.,
// clicking), and conveying state to the user. It will have these public
// methods:

class Button
{
public:
  // Constructs a new object at the specified _position which invokes the
  // _onClick callback when clicked.
  Button(sf::Vector2f position, std::function<void(void)> callback);
  // Returns the position of the button.
  sf::Vector2f getPosition();
  // Returns the current sprite of the button.
  sf::Sprite *getSprite();
  // Sets this button's visualization to the specified _sprite.
  void setSprite(sf::Sprite *sprite);
  // Invokes the button's callback method (usually called when clicked).
  void onClick();

  /**************************************************************************/

private:
  std::function<void(void)> _callback;
  sf::Sprite _sprite;
  std::unique_ptr<sf::RectangleShape> _overlay;
  sf::Sprite *_fake_sprite;

public:
  Button();
  void init(const sf::Texture& texture, std::function<void(void)> callback);
  void position(float x, float y);
  void texture(const sf::Texture& texture);
  bool click(const sf::Event::MouseButtonEvent& event);
  void enable_overlay(const sf::Color& color);
  void disable_overlay();
  void render(sf::RenderStates states);
};

#endif
