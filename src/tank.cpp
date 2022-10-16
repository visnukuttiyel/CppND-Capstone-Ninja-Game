#include "tank.h"
#include <cmath>
#include <iostream>



void Tank::Update(int const &target_x, int const &target_y) {

//  if (count > 1 ){
//   bullet.Update(target_x,target_y);
//   count =0;
//  } 
count++;
bullet.SetTarget(target_x,target_y);
bullet.Update();

}

std::vector<SDL_Point> Tank::GetBulletBody()
{
  return bullet.GetBulletBody();
}