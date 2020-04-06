/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author YOUR_STUDENT_NUMBER
 * @date March, 2020
 */
#include "zoo.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider(){
    Grid grid = Grid(3);
    grid.set(1,0,Cell::ALIVE);
    grid.set(2,1,Cell::ALIVE);
    grid.set(0,2,Cell::ALIVE);
    grid.set(1,2,Cell::ALIVE);
    grid.set(2,2,Cell::ALIVE);
    return grid;
}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino(){
    Grid grid = Grid(3);
    grid.set(1,0,Cell::ALIVE);
    grid.set(2,0,Cell::ALIVE);
    grid.set(0,1,Cell::ALIVE);
    grid.set(1,1,Cell::ALIVE);
    grid.set(1,2,Cell::ALIVE);
    return grid;
}


/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship(){
    Grid grid = Grid(5,4);
    grid.set(1,0,Cell::ALIVE);
    grid.set(4,0,Cell::ALIVE);
    grid.set(0,1,Cell::ALIVE);
    grid.set(0,2,Cell::ALIVE);
    grid.set(4,2,Cell::ALIVE);
    grid.set(0,3,Cell::ALIVE);
    grid.set(1,3,Cell::ALIVE);
    grid.set(2,3,Cell::ALIVE);
    grid.set(3,3,Cell::ALIVE);
    return grid;
}


/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(std::string path){
    std::ifstream inputFile(path);
    if(!inputFile.is_open()){
        throw std::runtime_error("can't be opened");
    }
    int width;
    int height;
    inputFile >> width;
    inputFile >> height;
    if(width < 1 || height < 1){
        throw std::runtime_error("width or height not a positive integer");
    }
    Grid grid = Grid(width,height);

    char ch;
    std::vector<char> cVector;

    for(std::string line; getline(inputFile, line);){
        std::stringstream lineS(line);
        while(lineS >> std::noskipws >> ch){
            cVector.push_back(ch);
        }
    }
    for(int j = 0; j < grid.get_height(); j++){
        for(int i = 0; i < grid.get_width(); i++){
            if(cVector.at(i + (width * j)) == ' '){
                grid.set(i,j,DEAD);
            }else if(cVector.at(i + (width * j)) == '#'){
                grid.set(i,j,ALIVE);
            }else{
                throw std::runtime_error("char not alive or dead");
            }
        }
    }

    return grid;
}


/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(std::string path, Grid grid){
    std::ofstream outputFile;
    outputFile.open(path);
    if(!outputFile.is_open()){
        throw std::runtime_error("can't be opened");
    }

    outputFile << grid.get_width();
    outputFile << " ";
    outputFile << grid.get_height();
    outputFile << "\n";

    std::vector<char> cVector;
    for(int j = 0; j < grid.get_height(); j++){
        for(int i = 0; i < grid.get_width(); i++){
            outputFile << char(grid.get(i,j));
        }
        outputFile << "\n";
    }

    outputFile.close();
}


/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(std::string path){
    int width;
    int height;

    std::ifstream inputFile(path,std::ios::binary);
    if(!inputFile.is_open()){
        throw std::runtime_error("can't be opened");
    }
    inputFile.read((char*)&width, 4);
    inputFile.read((char*)&height, 4);

    Grid grid = Grid(width,height);
    std::vector<bool> gridVector;
    char c;
    while(inputFile.good()){
        inputFile.read((char*)&c, 1);
        std::bitset<8> bit = c;
        for(int i = 0; i < 8; i++){
            gridVector.push_back(bit.test(i));
        }
    }

    std::cout << "\n";
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if(gridVector.at(i + (width * j)) == 0){
                grid.set(i,j,DEAD);
            }else if(gridVector.at(i + (width * j)) == 1){
                grid.set(i,j,ALIVE);
            }else{
                std::cout << "woops" ;
            }
        }
    }

    return grid;
}


/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_binary(std::string path, Grid grid){
    std::ofstream outputFile;
    outputFile.open(path);
    if(!outputFile.is_open()){
        throw std::runtime_error("can't be opened");
    }

    int width = grid.get_width();
    int height = grid.get_height();
    outputFile.write((char*)&width, 4);
    outputFile.write((char*)&height, 4);

    std::string cVector = "";

    std::vector<char> dVector;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if(grid.get(i,j) == ALIVE){
                cVector = cVector + "1";
            }else if(grid.get(i,j) == DEAD){
                cVector = cVector + "0";
            }

            if(cVector.length() == 8){
                reverse(cVector.begin(),cVector.end());
                std::bitset<8> bit(cVector);
                unsigned long i = bit.to_ulong();
                char f = static_cast<char>(i);
                dVector.push_back(f);
                cVector = "";
            }else if(i == width-1 && j == height-1){
                reverse(cVector.begin(),cVector.end());
                std::bitset<8> bit(cVector);
                unsigned long i = bit.to_ulong();
                char f = static_cast<char>(i);
                dVector.push_back(f);
            }
        }
    }

    for(unsigned int i = 0; i < dVector.size(); i++){
        outputFile.write((char*)&dVector.at(i), sizeof(dVector.at(i)));
    }

    outputFile.close();

}

