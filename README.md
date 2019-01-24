The goal of this program is to find a path from a start point to a goal point in a rectangular grid.
Some cells in the grid may be blocked. The grid should be provided in a text file "grid.txt".
The format of this should be:

START(0,0)

GOAL(0,2)

ooox

xxoo

ooox

where the o's and x's denote a graphical representation of the grid. The bottom left corner is the cell (0,0).
If a cell is denoted with an 'o' then it is open and can be traversed, whereas 'x' shows a cell that is blocked.
In this example the cells (3,0), (0,1), (1,1) and (3,2) are blocked.

The code in main.cpp will then test to see if a path between the start and goal point exists, and if so this path will be output.
