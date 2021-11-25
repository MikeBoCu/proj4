#include <iostream>
#include "maze.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    Maze newMaze = Maze(4);
    newMaze.generateMaze();
    newMaze.printAllEdges();
    newMaze.printMaze();
    return 0;
}
