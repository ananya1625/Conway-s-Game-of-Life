//
// Created by Ananya Rajagopal on 4/27/21.
//

#include <catch2/catch.hpp>
#include <cell_container.h>

using namespace conwaysgameoflife;

//Let's just confirm that a 50x50 board can be built.
TEST_CASE("Sanity checks") {
    SECTION("Sanity check for 50x50 board") {
        CellContainer cell_container;
        REQUIRE(cell_container.GetCellLength() == 20);
        REQUIRE(cell_container.GetCellsPerRow() == 50);
        REQUIRE(cell_container.GetCells()[5][7].GetColor() == ci::Color("green"));
    }

    SECTION("Sanity check using constructor with parameters") {
        CellContainer cell_container(3, 5, {"o..", ".o."});
        REQUIRE(cell_container.GetCellLength() == 5);
        REQUIRE(cell_container.GetCellsPerRow() == 3);
        REQUIRE(cell_container.GetCells()[1][1].GetColor() == ci::Color("black"));
    }

    SECTION("Sanity check for live Cell class") {
        Cell cell(true, vec2(1,1), vec2(2,2));
        REQUIRE(cell.GetColor() == ci::Color("green"));
        REQUIRE(cell.GetTopLeft() == vec2(1,1));
        REQUIRE(cell.GetBottomRight() == vec2(2,2));
    }

    SECTION("Sanity check for dead Cell class") {
        Cell cell(false, vec2(1,1), vec2(2,2));
        REQUIRE(cell.GetColor() == ci::Color("black"));
    }
}

//Test basic rules of the game

TEST_CASE("Test that a live cell with 2-3 live neighbors lives") {
    SECTION("Test that a live cell with 2 live neighbors lives") {
        std::vector<std::string> board = {"...O", "..O.", "...O", "...."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        std::vector<std::vector<Cell>> cells = container.GetCells();

        REQUIRE(cells[1][2].GetColor() == ci::Color("green"));
    }

    SECTION("Test that a live cell with 3 live neighbors lives") {
        std::vector<std::string> board = {".O.O", "..O.", "...O", "...."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        std::vector<std::vector<Cell>> cells = container.GetCells();

        REQUIRE(cells[1][2].GetColor() == ci::Color("green"));
    }
}

TEST_CASE("Test that a live cell without 2-3 live neighbors dies") {
    SECTION("Test that a live cell with 0 live neighbors dies") {
        std::vector<std::string> board = {"....", "..O.", "....", "...."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        REQUIRE(container.GetCells()[1][2].GetColor() == ci::Color("black"));
    }

    //checking 1 live neighbor and 4 live neighbors because off by 1 error
    SECTION("Test that a live cell with 1 live neighbors dies") {
        std::vector<std::string> board = {"....", ".OO.", "....", "...."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        std::vector<std::vector<Cell>> cells = container.GetCells();
        REQUIRE(cells[1][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][2].GetColor() == ci::Color("black"));
    }

    SECTION("Test that a live cell with 4 live neighbors dies") {
        std::vector<std::string> board = {"....", ".OO.", ".O..", ".O.."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        REQUIRE(container.GetCells()[2][2].GetColor() == ci::Color("black"));
    }
}

TEST_CASE("Test that a dead cell with exactly 3 live neighbors comes to life") {
    SECTION("Test with 3 live neighbors brings the dead cell to life") {
        std::vector<std::string> board = {".O..", ".OO.", "....", "...."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        REQUIRE(container.GetCells()[0][1].GetColor() == ci::Color("green"));
    }

    //checking that 2 doesn't bring a dead cell to life because 2 should only keep a live cell alive
    SECTION("Test that 2 live neighbors doesn't bring cells to life") {
        std::vector<std::string> board = {".O..", ".O..", "....", "...."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        std::vector<std::vector<Cell>> cells = container.GetCells();
        REQUIRE(cells[0][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][2].GetColor() == ci::Color("black"));
    }
}

//Now that that's out of the way, we can test some (literal) edge case board states.

TEST_CASE("Corners follow rules of game"){
    std::vector<std::string> board = {".OO.", "OOOO", "OOOO", ".OO.",};
    CellContainer container(4, 10, board);
    container.AdvanceOneFrame();

    std::vector<std::vector<Cell>> cells = container.GetCells();

    SECTION("Check configurations with corners come to life with exactly 3 live neighbors") {
        REQUIRE(cells[0][0].GetColor() == ci::Color("green"));
        REQUIRE(cells[0][3].GetColor() == ci::Color("green"));
        REQUIRE(cells[3][0].GetColor() == ci::Color("green"));
        REQUIRE(cells[3][3].GetColor() == ci::Color("green"));
    }

    SECTION("Check non corner edges") {
        REQUIRE(cells[0][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][2].GetColor() == ci::Color("black"));
    }

    SECTION("Check that center area dies") {
        REQUIRE(cells[1][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][2].GetColor() == ci::Color("black"));
    }
    //advance frame
    container.AdvanceOneFrame();
    cells = container.GetCells();

    SECTION("Check that corners die without live neighbors") {
        REQUIRE(cells[0][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][3].GetColor() == ci::Color("black"));
    }
}

TEST_CASE("Test that edges die off with only 2 cells on the edge") {

    SECTION("Testing left edge") {
        std::vector<std::string> board = {"....", "....", "O...", "O..."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        std::vector<std::vector<Cell>> cells = container.GetCells();

        REQUIRE(cells[0][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][0].GetColor() == ci::Color("black"));
    }

    SECTION("Testing right edge") {
        std::vector<std::string> board = {"....", "...O", "...O", "...."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        std::vector<std::vector<Cell>> cells = container.GetCells();

        REQUIRE(cells[0][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][3].GetColor() == ci::Color("black"));
    }

    SECTION("Testing top edge") {
        std::vector<std::string> board = {"OO...", "....", "....", "...."};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        std::vector<std::vector<Cell>> cells = container.GetCells();

        REQUIRE(cells[0][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][3].GetColor() == ci::Color("black"));
    }

    SECTION("Testing bottom edge") {
        std::vector<std::string> board = {"....", "....", "....", "..OO"};
        CellContainer container(4, 10, board);
        container.AdvanceOneFrame();
        std::vector<std::vector<Cell>> cells = container.GetCells();

        REQUIRE(cells[3][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][3].GetColor() == ci::Color("black"));
    }
}

TEST_CASE("Test board with just center pieces") {
    std::vector<std::string> board = {"....", ".OO.", ".OO.", "...."};
    CellContainer container(4, 10, board);
    container.AdvanceOneFrame();
    std::vector<std::vector<Cell>> cells = container.GetCells();

    SECTION("Check that one advancement keeps center alive") {
        REQUIRE(cells[1][1].GetColor() == ci::Color("green"));
        REQUIRE(cells[1][2].GetColor() == ci::Color("green"));
        REQUIRE(cells[2][1].GetColor() == ci::Color("green"));
        REQUIRE(cells[2][2].GetColor() == ci::Color("green"));
    }
    SECTION("Check that one advancement doesn't make anything else alive") {
        REQUIRE(cells[0][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][3].GetColor() == ci::Color("black"));
    }

    //advance a few times
    container.AdvanceOneFrame();
    container.AdvanceOneFrame();
    container.AdvanceOneFrame();
    cells = container.GetCells();

    SECTION("Check that the center stays the same after several frames") {
        REQUIRE(cells[1][1].GetColor() == ci::Color("green"));
        REQUIRE(cells[1][2].GetColor() == ci::Color("green"));
        REQUIRE(cells[2][1].GetColor() == ci::Color("green"));
        REQUIRE(cells[2][2].GetColor() == ci::Color("green"));
    }

    SECTION("Check that everything else stays the same after several frames") {
        REQUIRE(cells[0][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][3].GetColor() == ci::Color("black"));
    }
}

TEST_CASE("Test empty board") {
    std::vector<std::string> board = {"....", "....", "....", "...."};
    CellContainer container(4, 10, board);
    container.AdvanceOneFrame();
    std::vector<std::vector<Cell>> cells = container.GetCells();

    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            REQUIRE(cells[i][j].GetColor() == ci::Color("black"));
        }
    }
}

TEST_CASE("Test full board") {
    std::vector<std::string> board = {"OOOO", "OOOO", "OOOO", "OOOO"};
    CellContainer container(4, 10, board);
    container.AdvanceOneFrame();
    std::vector<std::vector<Cell>> cells = container.GetCells();

    SECTION("Check that most of the board dies") {
        REQUIRE(cells[0][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[0][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[1][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][0].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][2].GetColor() == ci::Color("black"));
        REQUIRE(cells[2][3].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][1].GetColor() == ci::Color("black"));
        REQUIRE(cells[3][2].GetColor() == ci::Color("black"));
    }
    SECTION("Check that corners stay alive") {
        REQUIRE(cells[0][0].GetColor() == ci::Color("green"));
        REQUIRE(cells[0][3].GetColor() == ci::Color("green"));
        REQUIRE(cells[3][0].GetColor() == ci::Color("green"));
        REQUIRE(cells[3][3].GetColor() == ci::Color("green"));
    }
}

