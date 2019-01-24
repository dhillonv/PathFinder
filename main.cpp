#include <iostream>

#include "Grid.h"

using std::cout;
using std::endl;

using namespace std;

int main() {

    //outputs the directions from START to
    //GOAL as provided in grid.txt

	Grid grid;

    grid.loadFromFile("grid");
    bool exists = grid.existsPath();

    if(exists){
    grid.outputPath(cout);
    cout << endl;
    grid.outputDirections(cout);
    } else {
    cout << "No path exists" << endl;
    }

	return 0;
}

