/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * 931478
 * 15 March, 2020
 */
#pragma once
#ifndef GRID

// Add the minimal number of includes you need in order to declare the class.
// #include ...
#include <vector>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = '0',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
    private:
        int width;
        int height;
        std::vector<Cell> gridCells;

        int get_index(int x, int y) const;
    public:
        Grid();
        Grid(int height);
        Grid(int width, int height);

        int get_width();
        int get_height();
        int get_total_cells();
        int get_alive_cells();
        int get_dead_cells();

        void resize(int square_size);
        void resize(int width, int height);


        Cell get(int x, int y);
        void set(int x, int y, Cell value);

        Cell& operator()( int x, int y);
        const Cell& operator()( int x, int y)const;

        Grid crop(int x0, int y0, int x1, int y1);

        void merge(other, x0, y0, alive_only = false)
        // How to draw an owl:
        //      Step 1. Draw a circle.
        //      Step 2. Draw the rest of the owl.
};

#endif
