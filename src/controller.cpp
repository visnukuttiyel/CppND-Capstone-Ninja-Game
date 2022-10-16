#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "ninja.h"

void Controller::ChangeDirection(Ninja &ninja, Ninja::Direction input,
                                 Ninja::Direction opposite) const {
  ninja.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Ninja &Ninja) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(Ninja, Ninja::Direction::kUp,
                          Ninja::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(Ninja, Ninja::Direction::kDown,
                          Ninja::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(Ninja, Ninja::Direction::kLeft,
                          Ninja::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(Ninja, Ninja::Direction::kRight,
                          Ninja::Direction::kLeft);
          break;
      }
    }
  }
}