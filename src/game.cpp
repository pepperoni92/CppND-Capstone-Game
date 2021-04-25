#include "game.h"
#include <iostream>
#include "SDL.h"
#include "player.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : _snake(grid_width, grid_height),
      _engine(_dev()),
      _randomW(0, static_cast<int>(grid_width - 1)),
      _randomH(0, static_cast<int>(grid_height - 1)) {
  _player = new Player();
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {

  renderer.LoadTextures(_player);

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // INPUT
    controller.HandleInput(running, _snake, _player);

    // UPDATE
    Update();

    // RENDER
    renderer.Render(_snake, _food, _player);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    //std::cout << "Frame " << frame_count << "\n";

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = _randomW(_engine);
    y = _randomH(_engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_snake.SnakeCell(x, y)) {
      _food.x = x;
      _food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!_snake.alive) return;

  _snake.Update();
  _player->Update();

  int new_x = static_cast<int>(_snake.head_x);
  int new_y = static_cast<int>(_snake.head_y);

  // Check if there's food over here
  if (_food.x == new_x && _food.y == new_y) {
    _score++;
    PlaceFood();
    // Grow snake and increase speed.
    _snake.GrowBody();
    _snake.speed += 0.02;
  }
}

int Game::GetScore() const { return _score; }
int Game::GetSize() const { return _snake.size; }