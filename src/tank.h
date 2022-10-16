#ifndef TANK_H
#define TANK_H

#include <vector>
#include "SDL.h"
#include "bullet.h"
#include "battlefield.h"

class Tank: public BattleField 
{
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Tank(int pos_x, int pos_y)
      : pos_x(pos_x),
        pos_y(pos_y),
        bullet(pos_x, pos_y) 
        {   
           body.emplace_back(SDL_Point{static_cast<int>(pos_x), static_cast<int>(pos_y)});
        }

  void Update(int const &target_x, int const &target_y);
  std::vector<SDL_Point> GetBulletBody();

  int count{0};

  float speed{0.1f};
  const int frequency{40};
  
  std::vector<SDL_Point> body;
  
  Bullet bullet;
 private:
  int pos_x;
  int pos_y;
};

#endif