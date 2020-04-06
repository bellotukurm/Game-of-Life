/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 931478
 * @date 06, March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...
#include "grid.h"

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
    private:
        int width;
        int height;
        Grid currentGrid;
        Grid nextGrid;

        int count_neighbours(int x, int y, bool toroidal);

    public:
        World();
        World(int square_size);
        World(int width, int height);
        World(Grid initial_state);

        int get_width();
        int get_height();
        int get_total_cells();
        int get_alive_cells();
        int get_dead_cells();

        Grid get_state();
        void resize(int square_size);
        void resize(int new_width, int new_height);

        void step(bool toroidal = false);
        void advance(int steps, bool toroidal = false);

    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.

};