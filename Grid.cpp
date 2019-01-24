#include "Grid.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <math.h>

Grid::Grid(){
    //initialise empty grid
    m=0;
    n=0;
}

Grid::~Grid(){
}

void Grid::loadFromFile(const std::string& filename){
    //load file - we assume the name of the file we are opening is of type .txt

    std::ifstream inputfile;
    std::string fline,blockcheck;
    std::string startstr = "START";
    std::string endstr = "GOAL";

    inputfile.open(filename);
    if(!inputfile.is_open()){
        inputfile.open(filename + ".txt");
    }
    if(!inputfile.is_open()){
        std::cout << "File not found" << std::endl;
        return;
    }

    int counter=0,stringint;
    std::tuple<int,int,int> point;
    std::string index;

    //store each line of the file in fline

    while(getline(inputfile,fline)){
        if(!fline.empty()){

                //first line
                if(fline.find(startstr)!=std::string::npos){
                    //line is of the form START(X1,X2)
                    //store X1 and X2 in the array startpoint
                    index = fline[6];
                    std::istringstream (index) >> stringint;
                    startpoint[0] = stringint;
                    index = fline[8];
                    std::istringstream (index) >> stringint;
                    startpoint[1] = stringint;
                }

                //goal line
                else if(fline.find(endstr)!=std::string::npos){
                    //string is of the form GOAL(X1,X2)
                    //store X1 and X2 in the array endpoint
                    index = fline[5];
                    std::istringstream (index) >> stringint;
                    endpoint[0] = stringint; //5,7
                    index = fline[7];
                    std::istringstream (index) >> stringint;
                    endpoint[1] = stringint;
                }

                else{
                    //initialise m, this should be constant
                    if(m==0){m = fline.length();}

                    //make sure m is constant
                    if(m!=fline.length()){
                        std::cout << "Error loading grid description." << std::endl;
                        return;
                    }

                    for(int y=0;y<m;++y){

                        blockcheck = fline[y];

                        //point is open, add this to the grid
                        if(blockcheck == "o"){
                            point = {y,-counter,0};
                            gridvec.push_back(point);
                        }
                        //point is blocked, add this to the grid
                        else if(blockcheck == "x"){
                            point = {y,-counter,1};
                            gridvec.push_back(point);
                        }

                        //grid should only consist of o's and x's
                        else{
                            std::cout << "Error loading grid description." << std::endl;
                            return;
                        }
                    }
                    //counter will give a count of the height of the grid
                    counter++;
                }
        }
    }

    n = counter - 1; //the height of the grid - 1, will be adjusted
    //now adjust the y coordinate
    for(int x=0;x<gridvec.size();++x){
        std::get<1>(gridvec[x]) +=n;
    }
    //adjust n
    n++;
    //close file
    inputfile.close();
    }


bool Grid::isStart(int x,int y) const{
	// Returns true if (x,y) is the start position, and
	// returns false otherwise.
	// If (x,y) is outside of the grid, throw
	// "Position outside of the range of the grid."

	if((x>m-1)||(y>n-1)){
        std::cout << "Position outside of the range of the grid." << std::endl;
        return false;
	}

	if((startpoint[0]==x)&&(startpoint[1]==y)){return true;}

	return false;

}
bool Grid::isGoal(int x,int y) const{
    // Returns true if (x,y) is the end position, and
	// returns false otherwise.
	// If (x,y) is outside of the grid, throw
	// "Position outside of the range of the grid."

    if((x>m-1)||(y>n-1)){
        std::cout << "Position outside of the range of the grid." << std::endl;
        return false;
	}

	if((endpoint[0]==x)&&(endpoint[1]==y)){return true;}

	return false;

}
bool Grid::blocked(int x, int y) const{
    // Returns true if (x,y) is a blocked cell, and
	// returns false otherwise.
	// If (x,y) is outside of the grid, throw
	// "Position outside of the range of the grid."
    if((x>m-1)||(y>n-1)){
        std::cout << "Position outside of the range of the grid." << std::endl;
        return false;
	}

    int gridx,gridy;

	for(int y=0;y<gridvec.size();++y){
        gridx = std::get<0>((gridvec[y]));
        gridy = std::get<1>((gridvec[y]));

        if((gridx==x)&&(gridy==y)){
            if (std::get<2>((gridvec[y])) == 1){
                return true;}
            else{return false;}
        }
	}

}
void Grid::setStart(int x, int y){
    // Sets (x,y) to be the start position.
	// If  (x,y) is outside of the grid,
	// throw "Position outside of the range of the grid."
    if((x>m-1)||(y>n-1)){
        std::cout << "Position outside of the range of the grid." << std::endl;
        return;
	}

    startpoint[0] = x;
    startpoint[1] = y;
}

void Grid::setGoal(int x, int y){
    // Sets (x,y) to be the goal position.
	// If (x,y) is outside of the grid,
	// throw "Position outside of the range of the grid."
    if((x>m-1)||(y>n-1)){
        std::cout << "Position outside of the range of the grid." << std::endl;
        return;
	}

	endpoint[0]=x;
	endpoint[1]=y;
}

void Grid::unblock(int x, int y){
    // Sets cell (x,y) to empty (can be entered).
	// If (x,y) is outside of the grid,
	// throw "Position outside of the range of the grid."

    if((x>m-1)||(y>n-1)){
        std::cout << "Position outside of the range of the grid." << std::endl;
        return;
	}

    int gridx,gridy;

	for(int y=0;y<gridvec.size();++y){
        gridx = std::get<0>((gridvec[y]));
        gridy = std::get<1>((gridvec[y]));

        if((gridx==x)&&(gridy==y)){
            std::get<2>((gridvec[y]))=0;
                return;}
	}
}

void Grid::block(int x, int y){
	// Sets cell (x,y) to blocked (cannot be entered).
    // If (x,y) is outside of the grid,
    // throw "Position outside of the range of the grid."

    if((x>m-1)||(y>n-1)){
        std::cout << "Position outside of the range of the grid." << std::endl;
        return;
	}

    int gridx,gridy;

	for(int y=0;y<gridvec.size();++y){
        gridx = std::get<0>((gridvec[y]));
        gridy = std::get<1>((gridvec[y]));

        if((gridx==x)&&(gridy==y)){
            std::get<2>((gridvec[y]))=1;
                return;}
	}

}

bool Grid::existsPath(){
    // Returns true if there is a path from the current
	// start to the current end position, and false otherwise.
	// A path cannot pass through blocked cells or exit the
	// grid, and from a given cell can move in one step in each
	// of the four neighboring cells, in the cardinal directions:
	// North, East, West, South

    if((blocked(startpoint[0],startpoint[1]))||(blocked(endpoint[0],endpoint[1]))){
        std::cout << "Error. Either start or goal point is blocked" << std::endl;
        return false;
    }
    pathvec.clear();
    std::tuple<int,int> currentpoint = {startpoint[0],startpoint[1]};

    pathvec.push_back(currentpoint);
    //so we have initialised our starting point in pathvec

    //now we need an algorithm to find a path.
    int gx,gy,numpaths;

    gx = endpoint[0];
    gy = endpoint[1];

    std::vector<std::vector<std::tuple<int,int>>> paths,proxypaths,temppaths;
    std::vector<std::tuple<int,int>> proxypath;

    paths.push_back(pathvec);

    int checker=0,cx,cy,pathlen;
    paths = ForwardPath(gridvec,pathvec); //first movement

    while(1){
        //check if any of the paths reached the end point
        if(paths.size()==0){return false;}

        pathlen = (paths[0]).size();

        for (int y=0;y<paths.size();++y){
        //delete any paths with dead ends
            proxypath = paths[y];
            cx = std::get<0>(proxypath[pathlen-1]);
            cy = std::get<1>(proxypath[pathlen-1]);

            if((cx==-1)&&(cy==-1)){
                //delete this path
                paths.erase(paths.begin()+y);
                --y;
            }

            if((cx==gx)&&(cy==gy)){
                pathvec = proxypath;
                return true;
            }
        }

        if(paths.size()==0){return false;}

        numpaths = paths.size();
        for(int y=0;y<numpaths;++y){
            proxypaths = ForwardPath(gridvec,paths[y]);
            //add these paths to the paths vec
            paths.insert(paths.end(), proxypaths.begin(), proxypaths.end());

        }

        //now go through our list of paths and remove the old paths

        numpaths = paths.size();
        for(int y=0;y<numpaths;++y){
            if((paths[y]).size()==pathlen){
                paths.erase(paths.begin()+y);
                --y;
            }
        }
    }
}
void Grid::outputPath(std::ostream& o){
	/*
	Outputs the path from the start to the goal position as
	follows:

	g**x
	xx*o
    s**x

	where s denotes the start position (here (0,0)),
	g denotes the end position, and the * symbols denote the cells
	visited in this path from start to goal.
	Note that the letters s and g overwrite the * symbols from the
	corresponding cells. If the start and the goal are
	the same cell, then the cell should be marked with g.
	If there is no path, throw "No path from start to goal".
	*/

	bool pathcheck;
	int opencheck,x1,y1;
	pathvec.clear();
	pathcheck = existsPath();

	if(!pathcheck){
        o << "No path from start to goal" << std::endl;
        return;
	}

	//grid is mxn
	for(int y=n-1; y>-1;--y){

        for(int x=0;x<m;++x){
            //cases
            //case 1 we are on the start point
            if((x==startpoint[0])&&(y==startpoint[1])){
                o << "s";
            }

            //case 2 we are at the goal point
            else if((x==endpoint[0])&&(y==endpoint[1])){
                o << "g";
            }

            //case 3 point is in the path
            else if(PointInPath(x,y,pathvec)){
                o << "*";
            }

            //case 4 point is not on the path
            else{
                //find point x,y in gridvec
                for(int q=0;q<gridvec.size();q++){
                    x1 = std::get<0>(gridvec[q]);
                    y1 = std::get<1>(gridvec[q]);
                    opencheck = std::get<2>(gridvec[q]);
                    if((x1==x)&&(y1==y)&&(opencheck==0)){
                        o << "o";
                    }
                    if((x1==x)&&(y1==y)&&(opencheck==1)){
                        o << "x";
                    }
                }
            }
        }
        o<<std::endl;
	}

}
void Grid::outputDirections(std::ostream& o){
		/* Outputs the navigation directions for the path from
	the start to the goal position as a sequence of
	instructions of the following form:
	move from (X1,Y1) to (X1,Y2)
	turn North
	turn South
	turn East
	turn West
	You have arrived at your destination.


	For example, for the example above, it should output

	Move from (0,0) to (2,0).
	Turn North.
	Move from (2,0) to (2,2).
	Turn West.
	Move from (2,2) to (0,2).
	You have arrived at your destination.

	The output should not contain empty lines.
	If there is no path, throw "No path from start to goal".

	If start and goal are the same, should just output
	You have arrived at your destination.
	*/

    bool pathcheck;
	int x1,y1,y2,x2,nx,ny;

	if((startpoint[0]==startpoint[1])&&(endpoint[0]==endpoint[1])){
        o << "You have arrived at your destination." << std::endl;
	}

	pathvec.clear();
	pathcheck = existsPath();

	if(!pathcheck){
        o << "No path from start to goal" << std::endl;
        return;
	}

	//now output directions for the path in pathvec

	int counter=0;
    int pathsize,pathindex=0,newpathindex=0;
    pathsize = pathvec.size();
    int direction[2]; //a vector of the direction we are going

    //initialise direction
    x1=std::get<0>(pathvec[pathindex]);
    y1=std::get<1>(pathvec[pathindex]);
    x2=std::get<0>(pathvec[pathindex+1]);
    y2=std::get<1>(pathvec[pathindex+1]);
    direction[0] = x1-x2;
    direction[1]=y1-y2;
    //the current point is x1,y1
    //the next point is x2,y2

    while(counter!=pathsize-1){
        //move forward one step
        counter++;
        x1=std::get<0>(pathvec[counter-1]); //the current point
        y1=std::get<1>(pathvec[counter-1]);
        x2=std::get<0>(pathvec[counter]); //the next point
        y2=std::get<1>(pathvec[counter]);

        //check we are still going in the same direction
        if((direction[0]==x1-x2)&&(direction[1] == y1-y2)){
            //nothing needs to be done, unless the next point is the goal
            if(counter==pathsize-1){
                o << "Move from (" << std::get<0>(pathvec[pathindex]) <<","<< std::get<1>(pathvec[pathindex]) << ")" << " to (" << std::get<0>(pathvec[counter]) <<","<< std::get<1>(pathvec[counter]) << ")." << std::endl;
            }
        }
        else{
            //update direction
            direction[0] = x1-x2;
            direction[1]=y1-y2;
            //we have changed direction!, so now output the movements and the turn
             o << "Move from (" << std::get<0>(pathvec[pathindex]) <<","<< std::get<1>(pathvec[pathindex]) << ")" << " to (" << std::get<0>(pathvec[counter-1]) <<","<< std::get<1>(pathvec[counter-1]) << ")." << std::endl;
             pathindex=counter-1;
             //only need a direction if we are not at the goal point
             if(pathindex!=pathsize-1){
                nx=std::get<0>(pathvec[pathindex+1]);
                ny=std::get<1>(pathvec[pathindex+1]);

                //we want to travel in the x direction
                if(x1-nx>0){o << "Turn West." << std::endl;}
                if(x1-nx<0){o << "Turn East." << std::endl;}
                //we want to travel in the y direction
                if(y1-ny>0){o << "Turn South." << std::endl;}
                if(y1-ny<0){o << "Turn North." << std::endl;}
                }
             }
        }
        //we should be at the goal now
        o << "You have arrived at your destination." << std::endl;
    }

std::vector<std::vector<std::tuple<int,int>>> ForwardPath(std::vector<std::tuple<int,int,int>> grid, std::vector<std::tuple<int,int>> path){

    //returns all the current one step movements according to grid
    std::vector<std::vector<std::tuple<int,int>>> output;
    std::vector<std::tuple<int,int>> proxypath;
    //assumes we are given a path in path, we do not want to go backwards
    std::tuple<int,int> currentpoint,newpoint;
    //find the current point we are at
    int pathsize = path.size();
    currentpoint = path[pathsize-1];

    int cx,cy,nx,ny,open,px=-1,py=-1;
    cx = std::get<0>(currentpoint);
    cy = std::get<1>(currentpoint);

    if(pathsize>1){
        px = std::get<0>(path[pathsize-2]);
        py = std::get<1>(path[pathsize-2]);
    }

    for (int z=0;z<grid.size();++z){
        nx = std::get<0>(grid[z]);
        ny = std::get<1>(grid[z]);
        open = std::get<2>(grid[z]);

        if((std::abs(cx-nx) + std::abs(cy-ny) == 1)&&(open==0)){
            if((nx!=px)||(ny!=py)){
                //so if we can move to a point and its not the previous
                //point then move there
                newpoint = {nx,ny};
                proxypath = path;
                proxypath.push_back(newpoint);
                output.push_back(proxypath);
            }
        }
    }

    //if we didnt move anywhere lets go to point (-1,-1) so we know not to use this path
    if(output.empty()){
        proxypath = path;
        newpoint = {-1,-1};
        proxypath.push_back(newpoint);
        output.push_back(proxypath);
    }

return output;}

void AppendVec(std::vector<std::vector<std::tuple<int,int>>> &vec1, std::vector<std::vector<std::tuple<int,int>>> &vec2){
    //appends vec2 to vec1
    //ie we have [vec1 vec2]

    for(int y=0;y<vec2.size();++y){
        vec1.push_back(vec2[y]);
    }
}

void PrintPaths(std::vector<std::vector<std::tuple<int,int>>> vec1){
    //outputs the paths for a pathvec vec1, used for testing purposes.
    std::vector<std::tuple<int,int>> path;
    for (int y=0; y<vec1.size();++y){
        path = vec1[y];
        for(int x=0; x<path.size(); ++x){
            std::cout << "(" << std::get<0>(path[x]) << "," << std::get<1>(path[x]) << ") ";
        }
    std::cout << std::endl;
    }
    }

bool PointInPath(int x, int y, std::vector<std::tuple<int,int>> path){
    //checks whether a point x,y is in path
    int x1,y1;
    for(int z=0;z<path.size();++z){
        x1 = std::get<0>(path[z]);
        y1 = std::get<1>(path[z]);
        if((x1==x)&&(y1==y)){
            return true;
        }
    }
    return false;
    }

void PrintPath(std::vector<std::tuple<int,int>> vec1){
    //outputs the paths for a pathvec vec1, used for testing purposes.
    std::vector<std::tuple<int,int>> path;
        path = vec1;
        for(int x=0; x<path.size(); ++x){
            std::cout << "(" << std::get<0>(path[x]) << "," << std::get<1>(path[x]) << ") ";
        }
    std::cout << std::endl;
    }
