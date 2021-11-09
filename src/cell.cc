//
// Created by Ananya Rajagopal on 4/20/21.
//
#include "cell.h"
#include <cinder/Color.h>
#include <glm/vec2.hpp>

using glm::vec2;
using std::vector;

namespace conwaysgameoflife {
Cell::Cell(const bool is_alive, const vec2& top_left, const vec2& bottom_right) {
  if (is_alive) {
      color_ = ci::Color("green");
  } else {
      color_ = ci::Color("black");
  }

  top_left_ = top_left;
  bottom_right_ = bottom_right;
}
ci::Color Cell::GetColor() const {
  return color_;
}
vec2 Cell::GetTopLeft() const {
  return top_left_;
}
vec2 Cell::GetBottomRight() const {
  return bottom_right_;
}

void Cell::Die()  {
    color_ = ci::Color("black");
}

void Cell::BringToLife() {
    color_ = ci::Color("green");
}

}
