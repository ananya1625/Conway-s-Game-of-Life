<h1>Conway's Game of Life</h1>

<h3>Background</h3>

This is a Conway's Game of Life simulation. The game, created by John Conway in 1970, simulates the life cycles of a group of square cells on a 2D plane. A cell's life depends on the (up to) 8 cells that surround it with a few simple rules.

For live cells:
* If between 2 and 3 cells of the neighboring cells are alive, the cell continues to live. 
* If fewer than 2 neighboring cells are alive, the cell dies, representing underpopulation.
* If more than 3 neighboring cells are alive, the cell dies, reprepresenting overpopulation.

For dead cells:
* If exactly 3 neighboring cells are alive and the cell is dead, the cell comes to life.

These simple rules can create some fantastic simulations, like [Bill Gosper's Glider Gun](https://en.wikipedia.org/wiki/Gun_(cellular_automaton)).

![GIF of glider gun simulation](https://miro.medium.com/max/960/1*1Bm-25IS8YlJ8oG6mMKRzQ.gif)

<h3>Running The Simulation</h3>

You will need to install Cinder on your computer to run this simulation. You can find steps at [this link](https://docs.openstack.org/cinder/latest/install/). Once installed, copy this repository into the cinder/my-projects directory.

To run the simulation, run conways-game-of-life or the cinder-app-main.cc file. Enjoy!
