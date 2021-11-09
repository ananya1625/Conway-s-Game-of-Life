//
// Created by Ananya Rajagopal on 4/20/21.
//

#include <cinder/Color.h>

#include <glm/vec2.hpp>
#ifndef CONWAYS_GAME_OF_LIFE_CELL_H
#define CONWAYS_GAME_OF_LIFE_CELL_H

#endif  // CONWAYS_GAME_OF_LIFE_CELL_H


namespace conwaysgameoflife {
using glm::vec2;

/** This class represents a cell in the container, which can interact with
 * the cells around it. */
class Cell {
 public:
  Cell(bool is_alive, const glm::vec2& top_left, const glm::vec2& bottom_right); 

  ci::Color GetColor() const;
  vec2 GetTopLeft() const;
  vec2 GetBottomRight() const;

  /**
   * Function that's executed when a cell dies, changing the color.
   */
  void Die();

  /**
   * Function that's executed when a cell comes to life, changing the color.
   */
  void BringToLife();

 private:
  ci::Color color_;
  vec2 top_left_;
  vec2 bottom_right_;
};
}