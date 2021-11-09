#include "game_simulation_app.h"

using conwaysgameoflife::ConwaysGameApp;

void prepareSettings(ConwaysGameApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(ConwaysGameApp, ci::app::RendererGl, prepareSettings);
