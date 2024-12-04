//////////////////////////////////////////////////////////////////////////////
// vim:tw=78
//
//  --------------------------------------------------------------------------
//    Project 4: Minesweeper
//  --------------------------------------------------------------------------
//
//    Author: Daniel Li
//    Course: COP3504C
//    Section: 25452
//    Date: Nov 31 2024
//
//////////////////////////////////////////////////////////////////////////////

#include <algorithm> // std::min()
#include <cmath> // floor()
#include <cstdlib>
#include <cstring>
#include <ctime> // time()
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "Button.h"
#include "GameState.h"
#include "Tile.h"
#include "Toolbox.h"
#include "minesweeper.h"

static Toolbox& msw = Toolbox::instance;

static void load_test1() { msw.reset_from_file("boards/testboard1.brd"); }
static void load_test2() { msw.reset_from_file("boards/testboard2.brd"); }
static void load_test3() { msw.reset_from_file("boards/testboard3.brd"); }

static inline float ease_in(float t) {
  return t * t * t;
}

static inline float ease_out(float t) {
  t = 1.0f - t;
  return 1.0f - t * t * t;
}

//----------------------------------------------------------------------------
// Toolbox Class
//----------------------------------------------------------------------------

Toolbox::Toolbox()
{
  gameState = nullptr;
  debugButton = &buttons.debug;
  newGameButton = &buttons.restart;
  testButton1 = &buttons.test1;
  testButton2 = &buttons.test2;

  _debug = false;

  unsigned char buf[4096];
  unsigned char *ptr, *end;
  sf::Image image;
  load_image(image, "images/mine.png");
  load_texture(textures.mine, image);
  memcpy(buf, image.getPixelsPtr(), 4096);
  end = buf + 4096;
  for (ptr = buf; ptr < end; ptr += 4) {
    ptr[2] = 0xff;
    ptr[3] >>= 1;
  }
  image.create(32, 32, buf);
  load_texture(textures.mine_debug, image);

  load_texture(textures.tile_hidden, "images/tile_hidden.png");
  load_texture(textures.tile_revealed, "images/tile_revealed.png");

  static const char number_file_template[] = "images/number_#.png";
  char number_file[sizeof(number_file_template)];
  memcpy(number_file, number_file_template, sizeof(number_file));
  for (int i = 0; i < 8; i++) {
    number_file[14] = '1' + i;
    load_texture(textures.number[i], number_file);
  }

  load_texture(textures.flag, "images/flag.png");
  load_texture(textures.face_happy, "images/face_happy.png");
  load_texture(textures.face_win, "images/face_win.png");
  load_texture(textures.face_lose, "images/face_lose.png");
  load_texture(textures.digits, "images/digits.png");
  load_texture(textures.debug, "images/debug.png");
  load_texture(textures.test1, "images/test_1.png");
  load_texture(textures.test2, "images/test_2.png");
  load_texture(textures.test3, "images/Test_3.png");

  buttons.debug.init(textures.debug, toggleDebugMode);
  buttons.restart.init(textures.face_happy, restart);
  buttons.test1.init(textures.test1, load_test1);
  buttons.test2.init(textures.test2, load_test2);
  buttons.test3.init(textures.test3, load_test3);

  flag_counter[0].setTexture(textures.digits);
  flag_counter[1].setTexture(textures.digits);
  flag_counter[2].setTexture(textures.digits);
}

Toolbox& Toolbox::getInstance()
{
  return msw;
}

void Toolbox::reset(GameState *g)
{
  gameState = g;
  game.reset(g);
  buttons.restart.texture(textures.face_happy);
  update_view();
  update_flag_counter();
}

void Toolbox::load_image(sf::Image& image, const char *filename)
{
  if (!image.loadFromFile(filename))
    exit(-1);
}

void Toolbox::load_texture(sf::Texture& texture, const char *filename)
{
  if (!texture.loadFromFile(filename))
    exit(-1);
}

void Toolbox::load_texture(sf::Texture& texture, const sf::Image& image)
{
  if (!texture.loadFromImage(image))
    exit(-1);
}

void Toolbox::launch()
{
  //random.seed(0x20241201);
  msw.random.seed(time(nullptr));

  std::cout <<
    "\n"
    "  ------------------------------------------------------------------\n"
    "                        Project 4: Minesweeper\n"
    "  ------------------------------------------------------------------\n"
    "\n"
    "    Author: Daniel Li                Keyboard shortcuts:\n"
    "    Course: COP3504C                   q   quit\n"
    "    Section: 25452                     d   toggle debug mode\n"
    "    Date: Nov 31 2024                  r   restart\n"
    "                                       1-3 load test boards\n"
    "\n"
    "    Random number: " << random() << "\n"
    "\n"
  ;

  window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Daniel Li");

  // reset the game
  reset_random();
  update_view();

  sf::Clock clock;
  dt = 0.0f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          return;
        case sf::Event::Resized:
          update_view();
          break;
        case sf::Event::MouseButtonPressed:
          if ((game && game->click(event.mouseButton)) ||
              buttons.test3.click(event.mouseButton) ||
              buttons.test2.click(event.mouseButton) ||
              buttons.test1.click(event.mouseButton) ||
              buttons.restart.click(event.mouseButton) ||
              buttons.debug.click(event.mouseButton))
            break;
          break;
        case sf::Event::KeyPressed:
          switch (event.key.code) {
            case sf::Keyboard::Q:
            case sf::Keyboard::Escape:
              window.close();
              return;
            case sf::Keyboard::D:
              toggle_debug();
              break;
            case sf::Keyboard::R:
              reset_random();
              break;
            case sf::Keyboard::Num1:
              load_test1();
              break;
            case sf::Keyboard::Num2:
              load_test2();
              break;
            case sf::Keyboard::Num3:
              load_test3();
              break;
            default: ;
          }
          break;
        default:
          break;
      }
    }

    render();

    dt = clock.getElapsedTime().asSeconds();
    if (dt < 0.016f)
      sf::sleep(sf::seconds(0.016f - dt));
    dt = clock.restart().asSeconds();
  }
}

void Toolbox::reset_random()
{
  reset(new GameState());
}

void Toolbox::reset_from_file(const char *filename)
{
  reset(new GameState(filename));
}

void Toolbox::render()
{
  sf::RenderStates states;
  window.clear(sf::Color::White);
  if (game)
    game->render(states);
  buttons.debug.render(states);
  buttons.restart.render(states);
  buttons.test1.render(states);
  buttons.test2.render(states);
  buttons.test3.render(states);
  window.draw(flag_counter[0], states);
  window.draw(flag_counter[1], states);
  window.draw(flag_counter[2], states);
  window.display();
}

void Toolbox::update_view()
{
  sf::Vector2u size = window.getSize();
  unsigned int width = size.x;
  unsigned int height = size.y;
  window.setView(sf::View(sf::FloatRect(0, 0, width, height)));

  buttons.debug.position(12, height - 76);
  buttons.restart.position(width / 2 - 32, height - 76);
  buttons.test1.position(width - 204, height - 76);
  buttons.test2.position(width - 140, height - 76);
  buttons.test3.position(width - 76, height - 76);

  flag_counter[0].setPosition(88, height - 60);
  flag_counter[1].setPosition(109, height - 60);
  flag_counter[2].setPosition(130, height - 60);

  if (game)
    game->update_transform();
}

void Toolbox::update_flag_counter()
{
  int value = game ? game->getFlagCount() : 0;
  flag_counter[0].setTextureRect(sf::IntRect(value < 0 ? 210 : value / 100 % 10 * 21, 0, 21, 32));
  if (value < 0) value = -value;
  flag_counter[1].setTextureRect(sf::IntRect(value / 10 % 10 * 21, 0, 21, 32));
  flag_counter[2].setTextureRect(sf::IntRect(value % 10 * 21, 0, 21, 32));
}

bool Toolbox::debug()
{
  return _debug;
}

void Toolbox::debug(bool debug)
{
  _debug = debug;
  if (_debug)
    buttons.debug.enable_overlay(sf::Color(0x00, 0x50, 0xff, 0x40));
  else
    buttons.debug.disable_overlay();
}

void Toolbox::toggle_debug()
{
  debug(!_debug);
}

float Toolbox::randomfloat(float a, float b)
{
  return a + (float)random() / random.max() * (b - a);
}

Toolbox Toolbox::instance;

//----------------------------------------------------------------------------
// Button Class
//----------------------------------------------------------------------------

Button::Button(sf::Vector2f position, std::function<void(void)> callback)
{
  _callback = callback;
  _sprite.setPosition(position);
  _fake_sprite = &_sprite;
}

sf::Vector2f Button::getPosition()
{
  return _sprite.getPosition();
}

sf::Sprite *Button::getSprite()
{
  return _fake_sprite;
}

void Button::setSprite(sf::Sprite *sprite)
{
  _fake_sprite = sprite;
}

void Button::onClick()
{
  _callback();
}

Button::Button()
{
  _fake_sprite = &_sprite;
}

void Button::init(const sf::Texture& texture, std::function<void(void)> callback)
{
  _sprite.setTexture(texture);
  _callback = callback;
}

void Button::position(float x, float y)
{
  _sprite.setPosition(x, y);
  if (_overlay)
    _overlay->setPosition(x, y);
}

void Button::texture(const sf::Texture& texture)
{
  _sprite.setTexture(texture);
}

bool Button::click(const sf::Event::MouseButtonEvent& event)
{
  if (!_sprite.getGlobalBounds().contains(event.x, event.y))
    return false;
  if (event.button == sf::Mouse::Button::Left)
    _callback();
  return true;
}

void Button::enable_overlay(const sf::Color& color)
{
  if (!_overlay) {
    _overlay = std::make_unique<sf::RectangleShape>(sf::Vector2f(64, 64));
    _overlay->setFillColor(color);
    _overlay->setPosition(_sprite.getPosition());
  }
}

void Button::disable_overlay()
{
  _overlay.reset();
}

void Button::render(sf::RenderStates states)
{
  msw.window.draw(_sprite, states);
  if (_overlay)
    msw.window.draw(*_overlay, states);
}

//----------------------------------------------------------------------------
// Tile Class
//----------------------------------------------------------------------------

// Don't use these

Tile::Tile(sf::Vector2f position) { _position = position; }
sf::Vector2f Tile::getLocation() { return _position; }
Tile::State Tile::getState() { return _state; }
void Tile::setState(Tile::State state) { _state = state; }
std::array<Tile*, 8>& Tile::getNeighbors() { return _neighbors; }
void Tile::setNeighbors(std::array<Tile*, 8> neighbors) { _neighbors = neighbors; }
void Tile::onClickLeft() { reveal(); }
void Tile::onClickRight() { flag(); }
void Tile::draw() { render(sf::RenderStates::Default); }

void Tile::revealNeighbors()
{
  for (Tile *tile : _neighbors) {
    if (tile && !tile->_mine && tile->_state == State::HIDDEN) {
        tile->setState(State::REVEALED);
    }
  }
}

// Use these

void Tile::reveal_cascade(float delay)
{
  for (int i = 0; i < 8; i++)
    if (_neighbors[i])
      _neighbors[i]->reveal(delay);
}

Tile::Tile() {}

void Tile::init(sf::Vector2f position, bool mine, const std::array<Tile*, 8>& neighbors)
{
  _position = position;
  _mine = mine;
  _state = State::HIDDEN;
  _neighbors = neighbors;

  _base_sprite.setTexture(msw.textures.tile_hidden);
  if (_mine)
    _debug_sprite = std::make_unique<sf::Sprite>(msw.textures.mine_debug);
}

void Tile::reveal(float delay)
{
  if (msw.game->getPlayStatus() != GameState::PlayStatus::PLAYING)
    return;
  if (_state != State::HIDDEN)
    return;

  _state = State::REVEALED;
  _base_sprite.setTexture(msw.textures.tile_revealed);
  _base_sprite.setColor(sf::Color(0xd0, 0xd0, 0xd0));
  _reveal_sprite = std::make_unique<sf::Sprite>(msw.textures.tile_hidden);
  _reveal_sprite->setOrigin(16, 16);
  _reveal_progress = -delay;
  _reveal_angle = msw.randomfloat(-60, 60);
  if (_mine) {
    _content_sprite = std::make_unique<sf::Sprite>(msw.textures.mine);
    msw.game->lose();
  } else {
    int count = 0;
    for (int i = 0; i < 8; i++)
      if (_neighbors[i] && _neighbors[i]->_mine)
        ++count;
    if (count)
      _content_sprite = std::make_unique<sf::Sprite>(msw.textures.number[count - 1]);
    else
      reveal_cascade(delay + 0.01f);
    msw.game->decrement_hidden_count();
  }
}

void Tile::flag()
{
  if (msw.game->getPlayStatus() != GameState::PlayStatus::PLAYING)
    return;
  if (_state == State::HIDDEN) {
    _state = State::FLAGGED;
    _content_sprite = std::make_unique<sf::Sprite>(msw.textures.flag);
    msw.game->adjust_flag_count(-1);
  } else if (_state == State::FLAGGED) {
    _state = State::HIDDEN;
    _content_sprite.reset();
    msw.game->adjust_flag_count(1);
  }
}

void Tile::render(sf::RenderStates states)
{
  states.transform.translate(_position);

  msw.window.draw(_base_sprite, states);
  if (_debug_sprite && msw.debug())
    msw.window.draw(*_debug_sprite, states);
  if (_content_sprite)
    msw.window.draw(*_content_sprite, states);
}

void Tile::render2(sf::RenderStates states)
{
  if (_reveal_sprite) {
    float t = (_reveal_progress += msw.dt) / 0.3f;
    if (t < 1.0f) {
      if (t < 0.0f)
        t = 0.0f;
      float i = ease_in(t);
      float rotation = t * _reveal_angle;
      float scale = 1.0f + 0.25f * i;
      float opacity = 1.0f - t;
      float offset = 32.0f * i;
      _reveal_sprite->setPosition(16, 16 + offset);
      _reveal_sprite->setRotation(rotation);
      _reveal_sprite->setScale(scale, scale);
      _reveal_sprite->setColor(sf::Color(0xff, 0xff, 0xff, (unsigned char)(opacity * 255.0f)));

      states.transform.translate(_position);
      msw.window.draw(*_reveal_sprite, states);
    } else {
      _reveal_sprite.reset();
    }
  }
}

//----------------------------------------------------------------------------
// GameState Class
//----------------------------------------------------------------------------

GameState::GameState(sf::Vector2i dim, int mines)
{
  int total = dim.x * dim.y;
  // sanity check
  if (total > 4096) {
    std::cerr << "Attempted to construct board with more than 4096 tiles\n";
    exit(-1);
  }
  int empty = total;
  char grid[4096];
  char *index[4096];
  memset(grid, 0, total);
  for (int i = 0; i < total; i++)
    index[i] = &grid[i];

  while (mines > 0) {
    char*& p = index[msw.random() % empty]; // Bad idea? I could care less
    *p = 1;
    p = index[--empty];
    --mines;
  }

  init(dim.x, dim.y, grid);
}

GameState::GameState(const char *filepath)
{
  char buf[32];
  char grid[4096];
  int i = 0;
  unsigned int linewidth = 0;
  unsigned int width = 0;
  unsigned int height = 0;
  std::ifstream stream(filepath, std::ios::binary);
  if (!stream) {
    std::cerr << "Failed to open '" << filepath << "'\n";
    exit(-1);
  }
  while (stream.read(buf, sizeof(buf))) {
    char *end = buf + stream.gcount();
    for (char *cur = buf; cur < end; cur++) {
      switch (*cur) {
        case '0':
          grid[i++] = 0;
          ++linewidth;
          break;
        case '1':
          grid[i++] = 1;
          ++linewidth;
          break;
        case '\n':
        case '\r':
          if (!height)
            width = linewidth;
          break;
      }
      if (linewidth == width) {
        linewidth = 0;
        ++height;
      }
    }
  }
  if (!height) {
    width = linewidth;
    height = 1;
  }
  init(width, height, grid);
}

int GameState::getFlagCount()
{
  return _flag_count;
}

int GameState::getMineCount()
{
  return _mine_count;
}

Tile *GameState::getTile(int x, int y)
{
  if (x >= 0 && x < _width && y >= 0 && y < _height)
    return &_tiles[y * _width + x];
  else
    return nullptr;
}

GameState::PlayStatus GameState::getPlayStatus()
{
  return _status;
}

void GameState::setPlayStatus(GameState::PlayStatus status)
{
  _status = status;
}

void GameState::init(int width, int height, char *grid)
{
  _width = width;
  _height = height;
  _status = GameState::PlayStatus::PLAYING;
  _mine_count = 0;
  _tiles = new Tile[width * height];
  _tiles_end = _tiles + width * height;
  _shake = 10;

  std::array<Tile*, 8> neighbors;
  for (int i = 0, y = 0; y < height; y++) {
    for (int x = 0; x < width; x++, i++) {
      bool mine = grid[i];
      neighbors[0] = getTile(x - 1, y - 1);
      neighbors[1] = getTile(x, y - 1);
      neighbors[2] = getTile(x + 1, y - 1);
      neighbors[3] = getTile(x - 1, y);
      neighbors[4] = getTile(x + 1, y);
      neighbors[5] = getTile(x - 1, y + 1);
      neighbors[6] = getTile(x, y + 1);
      neighbors[7] = getTile(x + 1, y + 1);
      _tiles[i].init(sf::Vector2f(x, y) * 32.0f, mine, neighbors);
      if (mine)
        ++_mine_count;
    }
  }

  _flag_count = _mine_count;
  _hidden_count = width * height;
}

GameState::~GameState()
{
  delete[] _tiles;
}

void GameState::update_transform()
{
  sf::Vector2u size = msw.window.getSize();
  sf::FloatRect rect(12, 12, size.x - 24, size.y - 100);
  float pxwidth = _width * 32;
  float pxheight = _height * 32;
  float scale = std::min(rect.width / pxwidth, rect.height / pxheight);
  float tx = rect.left + (rect.width - (pxwidth * scale)) / 2;
  float ty = rect.top + (rect.height - (pxheight * scale)) / 2;
  _transform = sf::Transform(scale, 0, tx, 0, scale, ty, 0, 0, 1);
  _inverse_transform = sf::Transform(1 / scale, 0, -tx / scale, 0, 1 / scale, -ty / scale, 0, 0, 1);
}

bool GameState::click(const sf::Event::MouseButtonEvent& event)
{
  sf::Vector2f coords = _inverse_transform * sf::Vector2f(event.x, event.y);
  Tile *tile = getTile(floor(coords.x / 32), floor(coords.y / 32));
  if (tile) {
    if (event.button == sf::Mouse::Button::Left)
      tile->reveal();
    else if (event.button == sf::Mouse::Button::Right)
      tile->flag();
    return true;
  }
  return false;
}

void GameState::adjust_flag_count(int diff)
{
  _flag_count += diff;
  msw.update_flag_counter();
}

void GameState::decrement_hidden_count()
{
  if ((--_hidden_count) == _mine_count)
    win();
}

void GameState::win()
{
  if (_status != PlayStatus::PLAYING)
    return;
  _status = PlayStatus::WIN;
  msw.buttons.restart.texture(msw.textures.face_win);
}

void GameState::lose()
{
  if (_status != PlayStatus::PLAYING)
    return;
  _status = PlayStatus::LOSS;
  _shake = 45;
  msw.buttons.restart.texture(msw.textures.face_lose);
}

void GameState::render(sf::RenderStates states)
{
  states.transform *= _transform;

  if (_shake) {
    float dx = msw.randomfloat(-1.0f, 1.0f);
    float dy = msw.randomfloat(-1.0f, 1.0f);
    states.transform.translate(sf::Vector2f(dx * _shake, dy * _shake));
    --_shake;
  }

  for (Tile *tile = _tiles; tile < _tiles_end; tile++)
    tile->render(states);
  for (Tile *tile = _tiles; tile < _tiles_end; tile++)
    tile->render2(states);
}

//----------------------------------------------------------------------------
// Global Functions
//----------------------------------------------------------------------------

int launch() { msw.launch(); return 0; }
void restart() { msw.reset_random(); }
void render() { msw.render(); }
void toggleDebugMode() { msw.toggle_debug(); }
bool getDebugMode() { return msw.debug(); }

// Finally, the main() function should be defined exactly as follows:
int main() { return launch(); } // OK
