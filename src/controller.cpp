#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::GetGestures() {
  gesture_tracker->init();
  gesture_tracker->startGestureDetection();
  this->gestures = gesture_tracker->getGestures();
}

void Controller::HandleGestureInput(bool &running, Snake &snake) const {
  gesture_tracker->update();
  //
  for(auto gesture : gestures)
  {
    switch(gesture){
      case GESTURE_SWIPE_UP:
        ChangeDirection(snake, Snake::Direction::kUp,
                            Snake::Direction::kDown);
        break;
      case GESTURE_SWIPE_DOWN:
        ChangeDirection(snake, Snake::Direction::kDown,
                            Snake::Direction::kUp);
        break;
      case GESTURE_SWIPE_LEFT:
        ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
        break;
      case GESTURE_SWIPE_RIGHT:
        ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
        break;
    }
  }
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}