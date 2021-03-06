/**
 * Implements a class representing a 2d grid world for simulating a cellular automaton.
 *      - Worlds can be constructed empty, from a size, or from an existing Grid with an initial state for the world.
 *      - Worlds can be resized.
 *      - Worlds can return counts of the alive and dead cells in the current Grid state.
 *      - Worlds can return their current Grid state.
 *
 *      - A World holds two equally sized Grid objects for the current state and next state.
 *          - These buffers are swapped after each update step.
 *
 *      - Stepping a world forward in time applies the rules of Conway's Game of Life.
 *          - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 *      - Worlds have a private helper function used to count the number of alive cells in a 3x3 neighbours
 *        around a given cell.
 *
 *      - Updating the world state can conditionally be performed using a toroidal topology.
 *          - Moving off the left edge you appear on the right edge and vice versa.
 *          - Moving off the top edge you appear on the bottom edge and vice versa.
 *
 * @author 931478
 * @date 17th April, 2020
 */
#include "world.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * World::World()
 *
 * Construct an empty world of size 0x0.
 *
 * @example
 *
 *      // Make a 0x0 empty world
 *      World world;
 *
 */
World::World(){
    this->width = 0;
    this->height = 0;
}

/**
 * World::World(square_size)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x16 world
 *      World x(16);
 *
 *      // Also make a 16x16 world
 *      World y = World(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the world.
 */
World::World(int square_size){
    this->width = square_size;
    this->height = square_size;

    currentGrid = Grid(width, height);
    nextGrid = Grid(width, height);

    //nested loop to fill current and next grid cells with dead cells
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            currentGrid.set(x,y,Cell::DEAD);
            nextGrid.set(x,y,Cell::DEAD);
        }
    }
}


/**
 * World::World(width, height)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 world
 *      World world(16, 9);
 *
 * @param width
 *      The width of the world.
 * @param height
 *      The height of the world.
 */
World::World(int width, int height){
    this->width = width;
    this->height = height;

    currentGrid = Grid(width, height);
    nextGrid = Grid(width, height);

    //nested loop to fill current and next grid cells with dead cells
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            currentGrid.set(x,y,Cell::DEAD);
            nextGrid.set(x,y,Cell::DEAD);
        }
    }
}


/**
 * World::World(initial_state)
 *
 * Construct a world using the size and values of an existing grid.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 *      // Make a world by using a grid as an initial state
 *      World world(grid);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World bad_world = grid; // All around me are familiar faces...
 *
 * @param initial_state
 *      The state of the constructed world.
 */
World::World(Grid initial_state){
    this->width = initial_state.get_width();
    this->height = initial_state.get_height();

    currentGrid = Grid(width, height);
    nextGrid = Grid(width, height);

    //nested loop to fill current and next grid cells with the cells for the grid passed
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            currentGrid.set(x,y,initial_state.get(x,y));
            nextGrid.set(x,y,Cell::DEAD);
        }
    }
}


/**
 * World::get_width()
 *
 * Gets the current width of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << world.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << read_only_world.get_width() << std::endl;
 *
 * @return
 *      The width of the world.
 */
int World::get_width(){
    return this->width;
}


/**
 * World::get_height()
 *
 * Gets the current height of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << world.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << read_only_world.get_height() << std::endl;
 *
 * @return
 *      The height of the world.
 */
int World::get_height(){
    return this->height;
}


/**
 * World::get_total_cells()
 *
 * Gets the total number of cells in the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << world.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << read_only_world.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
int World::get_total_cells(){
    return (this->height * this->width);
}


/**
 * World::get_alive_cells()
 *
 * Counts how many cells in the world are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << world.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
int World::get_alive_cells(){
    int count = 0;

    //nested loop to get number of all alive cells in the world
    for (int y = 0; y < currentGrid.get_height(); y++) {
        for (int x = 0; x < currentGrid.get_width(); x++) {
            if(currentGrid.get(x, y) == Cell::ALIVE){
                count++;
            }
        }
    }
    return count;
}


/**
 * World::get_dead_cells()
 *
 * Counts how many cells in the world are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << world.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
int World::get_dead_cells(){
    int count = 0;

    //nested loop to get number of all dead cells in the world
    for (int y = 0; y < currentGrid.get_height(); y++) {
        for (int x = 0; x < currentGrid.get_width(); x++) {
            if(currentGrid.get(x, y) == Cell::DEAD){
                count++;
            }
        }
    }
    return count;
}


/**
 * World::get_state()
 *
 * Return a read-only reference to the current state
 * The function should be callable from a constant context.
 * The function should not invoke a copy the current state.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << world.get_state() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << read_only_world.get_state() << std::endl;
 *
 * @return
 *      A reference to the current state.
 */
const Grid& World::get_state(){
    return currentGrid;
}


/**
 * World::resize(square_size)
 *
 * Resize the current state grid in to the new square width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 8x8
 *      world.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void World::resize(int square_size){
    this->width = square_size;
    this->height = square_size;
    currentGrid.resize(square_size, square_size);
}

/**
 * World::resize(new_width, new_height)
 *
 * Resize the current state grid in to the new width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 2x8
 *      world.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void World::resize(int new_width, int new_height){
    this->width = new_width;
    this->height = new_height;
    currentGrid.resize(new_width, new_height);
}


/**
 * World::count_neighbours(x, y, toroidal)
 *
 * Private helper function to count the number of alive neighbours of a cell.
 * The function should not be visible from outside the World class.
 *
 * Neighbours are considered within the 3x3 square centred around the cell at x,y in the current state grid.
 * Ignore the centre coordinate, a cell is not its own neighbour.
 * Attempt to keep the logic as simple, expressive, and readable as possible.
 *
 * If toroidal = false then skip any neighbours that would be outside of the grid,
 * this assumes the grid is Cell::DEAD outside its bounds.
 *
 * If toroidal = true then correctly wrap out of bounds coordinates to the opposite side of the grid.
 *
 * This function is in World and not Grid because the 3x3 sized neighbourhood is specific to Conway's Game of Life,
 * while Grid is more generic to any 2D grid based cellular automaton.
 *
 * @param x
 *      The x coordinate of the centre of the neighbourhood.
 *
 * @param y
 *      The y coordinate of the centre of the neighbourhood.
 *
 * @param toroidal
 *      If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom.
 *
 * @return
 *      Returns the number of alive neighbours.
 */
int World::count_neighbours(int x, int y, bool toroidal){
    int counter = 0;

    //nested loop that goes through all neighbour cell and the cell at (x,y)
    for(int j = y-1; j <= y+1; j++){
        for(int i = x-1; i <= x+1; i++){
            //conditional to do nothing when at cell (x,y)
            if(i==x && j==y){}
            else{
                if(toroidal){
                    /*conditional that checks what value of cell should be when out of
                    bounds brfore counting the neighbour if alive*/
                    if(i >= get_width() || j >= get_height() || i<0 || j<0){

                        int a = i;
                        int b = j;
                        if(i < 0){
                            a = get_width() + i;
                        }
                        else if(i >= get_width()){
                            a = i-get_width();
                        }
                        if(j < 0){
                            b = get_height() + j;
                        }
                        else if(j >= get_height()){
                            b = j-get_height();
                        }

                        if(currentGrid.get(a,b) == Cell::ALIVE){counter++;}
                    }
                    else if(currentGrid.get(i,j) == Cell::ALIVE){
                        counter++;
                    }
                }else{
                    //conditional that checks if value of cell out of bounds
                    if(i >= get_width() || j >= get_height() || i<0 || j<0){}
                    else if(currentGrid.get(i,j) == Cell::ALIVE){
                        counter++;
                    }
                }
            }
        }
    }
    return counter;
}

/**
 * World::step(toroidal)
 *
 * Take one step in Conway's Game of Life.
 *
 * Reads from the current state grid and writes to the next state grid. Then swaps the grids.
 * Should be implemented by invoking World::count_neighbours(x, y, toroidal).
 * Swapping the grids should be done in O(1) constant time, and should not invoke a copy.
 * Try and boil the logic down to the fewest and most simple conditional statements.
 *
 * Rules: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *      - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 *      - Any live cell with two or three live neighbours lives on to the next generation.
 *      - Any live cell with more than three live neighbours dies, as if by overpopulation.
 *      - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */
void World::step(bool toroidal){

    /*nested loop to check every cell in world and analyse whether cell will
    be dead or alive in the next step*/
    for(int y = 0; y < get_height(); y++){
        for(int x = 0; x < get_width(); x++){
            int aliveNeighbours = count_neighbours(x, y, toroidal);
            if(aliveNeighbours == 2 || aliveNeighbours == 3){
                if(currentGrid.get(x,y) == Cell::ALIVE){
                    nextGrid.set(x,y, ALIVE);
                }else if(currentGrid.get(x,y) == Cell::DEAD && aliveNeighbours == 3){
                    nextGrid.set(x,y, ALIVE);
                }
            }else{
                nextGrid.set(x,y, DEAD);
            }
        }
    }
    //take the next step
    currentGrid = nextGrid;
}


/**
 * World::advance(steps, toroidal)
 *
 * Advance multiple steps in the Game of Life.
 * Should be implemented by invoking World::step(toroidal).
 *
 * @param steps
 *      The number of steps to advance the world forward.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */
void World::advance(int steps, bool toroidal){
    //change world the number of steps
    for(int i = 0; i < steps; i++){
        step(toroidal);
    }
}
