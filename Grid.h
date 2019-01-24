#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include <tuple>

class Grid {
public:
	//Initializes an empty grid, with both dimensions equal to 0.
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

private:
  	int m,n,startpoint[2],endpoint[2]; //grid is (m-1)x(n-1)
  	std::vector<std::tuple<int,int,int>> gridvec; //gridvec stores the grid
  	std::vector<std::tuple<int,int>> pathvec; //pathvec stores the path from start to goal
};

//additional functions used

std::vector<std::vector<std::tuple<int,int>>> ForwardPath(std::vector<std::tuple<int,int,int>> grid, std::vector<std::tuple<int,int>> path);
void AppendVec(std::vector<std::vector<std::tuple<int,int>>> &vec1, std::vector<std::vector<std::tuple<int,int>>> &vec2);
void PrintPaths(std::vector<std::vector<std::tuple<int,int>>> vec1);
void PrintPath(std::vector<std::tuple<int,int>> vec1);
bool PointInPath(int x, int y, std::vector<std::tuple<int,int>> path);

#endif /* GRID_H_ */
