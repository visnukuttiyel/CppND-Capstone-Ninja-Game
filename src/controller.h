#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ninja.h"

class Controller {
 public:
  void HandleInput(bool &running, Ninja &ninja) const;

 private:
  void ChangeDirection(Ninja &Ninja, Ninja::Direction input,
                       Ninja::Direction opposite) const;
};

#endif