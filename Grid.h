#ifndef GRID_H_
#define GRID_H_

#include <iosfwd>
#include <string>
#include <vector>
#include <tuple>

/*

In this exercise you will implement a class representing
 a terrain in the form of a rectangular grid. The cells of the
 grid are indexed with pairs of integers, where (0,0)
 represents the lower left cell, and (m-1,n-1) represents
 the top right cell, where m is the width and n is the height
 of the grid. For example, a grid of width 4 and height 3 is
 indexed in the following way:

(0,2)(1,2)(2,2)(3,2)
(0,1)(1,1)(2,1)(3,1)
(0,0)(1,0)(2,0)(3,0)

Some of the cells of the grid are blocked by obstacles.
We are interested in determining whether there is a path to
reach a given goal cell from a given start cell by moving
one cell at a time in each of the four cardinal directions:
North, East, West, South, and never entering a blocked cell
or stepping outside of the grid. You will write functions
that compute and output such a path if it exists.

In the example above, suppose that cells (3,0), (3,2),
(0,1) and (1,1) are blocked. If the start is (0,0) and
the goal is (0,2), then we have the following path
(0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2).

You are advised to use the STL containers for storing
information. This should help you implement this class.

*/

class Grid {
public:
	// Default constructor. Initializes an empty grid,
	// with both dimensions equal to 0.
	Grid();

	// Destructor
	~Grid();

	// No need to implement copy and move constructors
	Grid(const Grid&) = delete;
	Grid(Grid&&) = delete;
	// No need to implement assignment operators
	Grid& operator=(const Grid& other) = delete;
	Grid& operator=(Grid&& other) = delete;

	void loadFromFile(const std::string& filename);

	bool isStart(int x,int y) const;

	bool isGoal(int x,int y) const;

	bool blocked(int x, int y) const;

	void setStart(int x, int y);

	void setGoal(int x, int y);

	void unblock(int x, int y);

	void block(int x, int y);

	bool existsPath();

	void outputPath(std::ostream& o);

	void outputDirections(std::ostream& o);

    int m,n,startpoint[2],endpoint[2]; //grid is (m-1)x(n-1)
  	std::vector<std::tuple<int,int,int>> gridvec;
  	std::vector<std::tuple<int,int>> pathvec;


private:
  	//int m,n,startpoint[2],endpoint[2]; //grid is (m-1)x(n-1)
  	//std::vector<std::tuple<int,int,int>> gridvec;
  	//std::vector<std::tuple<int,int>> pathvec;
  	//gridvec stores the points that can be traversed
  	//pathvec stores the path from start to end
};

std::vector<std::vector<std::tuple<int,int>>> ForwardPath(std::vector<std::tuple<int,int,int>> grid, std::vector<std::tuple<int,int>> path);

void AppendVec(std::vector<std::vector<std::tuple<int,int>>> &vec1, std::vector<std::vector<std::tuple<int,int>>> &vec2);
void PrintPaths(std::vector<std::vector<std::tuple<int,int>>> vec1);
void PrintPath(std::vector<std::tuple<int,int>> vec1);
bool PointInPath(int x, int y, std::vector<std::tuple<int,int>> path);
#endif /* GRID_H_ */
