#include "cell_container.h"

using glm::vec2;

namespace conwaysgameoflife {

    CellContainer:: CellContainer(size_t cells_per_row, size_t cell_length,
                                  const std::vector<std::string>& starting_board) {
        cells_per_row_ = cells_per_row;
        cell_length_ = cell_length;
        starting_board_ = starting_board;

        SetUpGame();
    }
    CellContainer::CellContainer() {
        SetUpGame();
    }

    void CellContainer::SetUpGame() {
        cells_ = std::vector<std::vector<Cell>>(cells_per_row_);

        //fill board with dead cells
        for(size_t i = 0; i < cells_per_row_; i++) {
            for(size_t j = 0; j < cells_per_row_; j++) {
                cells_[i].push_back(Cell(false,
                                         vec2(cell_length_*j, cell_length_ * i),
                                         vec2((j+1)*cell_length_,cell_length_*(i + 1))));
            }
        }
        //populate live cells using the starter board
        for(size_t i = 0; i < starting_board_.size(); i++) {
            for (size_t j = 0; j < starting_board_[i].size(); j++) {
                if (starting_board_[i][j] == 'O') {
                    cells_[i][j].BringToLife();
                }
            }
        }
    }

    void CellContainer::Display() const {

        for (size_t i = 0; i < cells_.size(); i++) {
            for (size_t j = 0; j < cells_[i].size(); j++) {
                //need to change color each time cuz cells might be different colors
                ci::gl::color(cells_[i][j].GetColor());
                ci::gl::drawSolidRect(ci::Rectf(cells_[i][j].GetTopLeft(),
                                                cells_[i][j].GetBottomRight()));
                //draw outlines for each cell
                ci::gl::color(ci::Color("white"));
                ci::gl::drawStrokedRect(ci::Rectf(cells_[i][j].GetTopLeft(),
                                                cells_[i][j].GetBottomRight()));
            }
        }
    }

    void CellContainer::AdvanceOneFrame() {
        std::vector<std::vector<bool>> next_frame = FindNextGeneration();
        //iterate through the cells and kill/bring to life as necessary
        for (size_t i = 0; i < cells_per_row_; i++) {
            for(size_t j = 0; j < cells_per_row_; j++) {
                if (next_frame[i][j]) {
                    cells_[i][j].BringToLife();
                } else {
                    cells_[i][j].Die();
                }
            }
        }
    }

size_t CellContainer::CountLiveNeighbors(size_t row, size_t column) {
    size_t count = 0;
    //using int instead of size_t because I need negative numbers
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!(i == 0 && j == 0) && row + i < cells_per_row_ && row + i >= 0
            && column + j < cells_per_row_ && column + j >= 0) {
                if (cells_[row + i][column + j].GetColor() ==
                    ci::Color("green")) {
                    count++;
                }
            }
        }
    }
    return count;
}

    std::vector<std::vector<bool>> CellContainer::FindNextGeneration() {
        //uses less space if we just store the next generation as a 2D vector of boolean values
        std::vector<std::vector<bool>> next_cycle = std::vector<std::vector<bool>>(cells_per_row_,
                std::vector<bool>(cells_per_row_));

        for (size_t i = 0; i < cells_per_row_; i++) {
            for (size_t j = 0; j < cells_per_row_; j++) {
                size_t count = CountLiveNeighbors(i, j);
                //check 2 conditions that would make a cell alive
                if (count == 3) {
                    next_cycle[i][j] = true;
                } else if (cells_[i][j].GetColor() == ci::Color("green") && count == 2) {
                    next_cycle[i][j] = true;
                }
            }
        }
        return next_cycle;
    }

    size_t CellContainer::GetCellsPerRow() {
        return cells_per_row_;
    }

    size_t CellContainer::GetCellLength() {
        return cell_length_;
    }

    std::vector<std::vector<Cell>> CellContainer::GetCells() {
        return cells_;
    }

}  // namespace conwaysgameoflife
