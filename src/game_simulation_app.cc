#include "game_simulation_app.h"

namespace conwaysgameoflife {

ConwaysGameApp::ConwaysGameApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void ConwaysGameApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color("white"));


  container_.Display();
}

void ConwaysGameApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace conwaysgameoflife
