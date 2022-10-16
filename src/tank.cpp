#include "tank.h"
#include <cmath>
#include <iostream>



void Tank::Update(int const &target_x, int const &target_y) {

bullet.SetTarget(target_x,target_y);
if (!bullet_fired_)
{
  bullet.Fire(); // Fire bullet
  bullet_fired_ = true;
}
}

std::vector<SDL_Point> Tank::GetBulletBody()
{
  return bullet.GetBulletBody();
}