#pragma once

#include "cell_container.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace conwaysgameoflife {

/**
 * An app for visualizing Conway's Game of Life.
 */
class ConwaysGameApp : public ci::app::App {
 public:
  ConwaysGameApp();
  /**
   * Displays the results of the cell container's Display() method.
   */
  void draw() override;

  /**
   * Updates the simulation by calling the cell container's AdvanceOneFrame() method.
   */
  void update() override;

  const int kWindowSize = 800;

 private:
  CellContainer container_;
};

}  // namespace conwaysgameoflife

