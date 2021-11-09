#pragma once

#include "cell.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace conwaysgameoflife {

/**
 * The container in which all of the cells are contained. This class
 * stores all of the cells and updates them on each frame of the simulation.
 */
class CellContainer {
 public:
  CellContainer();
  CellContainer(size_t cells_per_row, size_t cell_length, const std::vector<std::string>& starting_board);
  /**
   * Displays the container walls and the current status of the cells.
   */
  void Display() const;

  /**
   * Updates the status of all cells (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  size_t GetCellsPerRow();
  size_t GetCellLength();
  std::vector<std::vector<Cell>> GetCells();

 private:
  std::vector<std::vector<Cell>> cells_;
  size_t cells_per_row_ = 50;
  size_t cell_length_ = 20;
  std::vector<std::string> starting_board_ = {"..................................................",
                                     "...............................O..................",
                                     ".............................O.O..................",
                                    "...................OO......OO............OO.......",
                                     "..................O...O....OO............OO.......",
                                     ".......OO........O.....O...OO.....................",
                                     ".......OO........O...O.OO....O.O..................",
                                     ".................O.....O.......O..................",
                                     "..................O...O...........................",
                                     "...................OO............................."};

  /**
  * This function is a helper for the constructors. It sets up starting board for the container.
  */
  void SetUpGame();

  /**
  *  Counts the neighbors of a given cell, identified by row and col. Returns the number of live neighbors.
  */
  size_t CountLiveNeighbors(size_t row, size_t column);

  /**
   *  Counts the neighbors of a given cell, identified by row and col. Returns the number of live neighbors.
   */
  std::vector<std::vector<bool>> FindNextGeneration();

};

}
// namespace conwaysgameoflife
