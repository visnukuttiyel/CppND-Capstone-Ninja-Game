#ifndef NINJA_H
#define NINJA_H

#include <vector>
#include "SDL.h"

class Ninja {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Ninja(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height-5) {}

  void Update();

  bool NinjaCell(int x, int y);
  float Clip(float n, float lower, float upper);

  Direction direction = Direction::kUp;

  float speed{0.3f};
  const float THETA_MAX{3.14/6};
  float theta{3.14/6};
  float delta_theta{0.01};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  int grid_width;
  int grid_height;
};

#endif