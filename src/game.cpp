#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : ninja(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
  PlaceTank(static_cast<int>(grid_width), static_cast<int>(grid_height));
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, ninja);
    Update();
    renderer.Render(ninja, food, tanks);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    if (!ninja.alive)
    {
      break;
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a ninja item before placing
    // food.
    if (!ninja.NinjaCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!ninja.alive) return;

  ninja.Update();

  int new_x = static_cast<int>(ninja.head_x);
  int new_y = static_cast<int>(ninja.head_y);

  for (auto tank:tanks)
  {
    tank->Update(new_x,new_y);

    SDL_Point bullet_postion = tank->bullet.GetBulletBody().back();
    ninja.alive = ninja.alive && !ninja.NinjaCell(bullet_postion.x, bullet_postion.y);
    tank->bullet.SetTargetStatus(ninja.alive);

  }

   for (auto tank:tanks)
  {
    tank->bullet.SetTargetStatus(ninja.alive);
  }


  // Check if there's food over here
  if (ninja.NinjaCell(food.x, food.y)) {
    score++;
    PlaceFood();
    // Grow ninja and increase speed.
    ninja.speed += 0.02;
  }

}

int Game::GetScore() const { return score; }

void Game::PlaceTank(int grid_width, int grid_height) {

tanks.push_back(std::make_shared<Tank>(0,0));
tanks.push_back(std::make_shared<Tank>(grid_width, 0));
tanks.push_back(std::make_shared<Tank>(0, grid_height));
tanks.push_back(std::make_shared<Tank>(grid_width, grid_height));

}