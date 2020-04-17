/**
 * Declares a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 * Rich documentation for the api and behaviour the Zoo namespace can be found in zoo.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 931478
 * @date 17th April, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the namespace.
// #include ...
#include "grid.h"
#include "world.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <bits/stdc++.h>

/**
 * Declare the interface of the Zoo namespace for constructing lifeforms and saving and loading them from file.
 */
namespace Zoo {

    Grid load_ascii(std::string path);
    void save_ascii(std::string path, Grid grid);
    Grid load_binary(std::string path);
    void save_binary(std::string path, Grid grid);

    Grid glider();
    Grid r_pentomino();
    Grid light_weight_spaceship();

    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.

};