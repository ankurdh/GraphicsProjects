#pragma once

#include<vector>
using namespace std;

#define GRID_CELL_SIZE 1000
#define NO_OF_DISCS 100000

typedef struct point 
    {
    int x;
    int y;

    point(int _x, int _y){ x = _x, y = _y;}
    point(){}
    } MyPoint ;

#pragma region Disk class Defn.
class Disk
    {
    private:
	MyPoint center;

    public:
	static const int radius = 250;

	Disk();
	Disk(MyPoint c);
	MyPoint getCenter();
	void setCenter(MyPoint p);
	int getCenterX();
	int getCenterY();
	void setCenterX(int x);
	void setCenterY(int y);
    };
#pragma endregion

class GridCell
    {
    private:
	MyPoint base;		//base represents the left bottom corner of a cell.
	int intersectedDiscCount;
	Disk * intersectedDiscs[50];

    public:
	GridCell();
	MyPoint getBasePoint();
	void setBaseXY(int x, int y);
	void addIntersectedDisk(Disk *d);
	Disk ** getIntersectedDiskList();
	int getIntersectedDiscCount();
    };

class Grid 
    {
    private:

	//Data structures for parallelogram & line intersections
	MyPoint intersectedGridCells[5000];
	MyPoint otherEdgeIntersectedGridCells[5000];
	int lineIntersectedGridCellCounter;
	int otherLineIntersectedGridCellCounter;
	
	//parallelogram vertices.
	MyPoint parallelogramVertices[4];

	//Data structures for holding the grid cells. 
	GridCell gridCells[GRID_CELL_SIZE][GRID_CELL_SIZE];

	//height and width of the pan zoom window.
	int height, width;

	//right click variables. 
	MyPoint firstRightClickCellBase, secondRightClickCellBase;
	int rightClickCounter;
	bool twoRightClicks;

	//space bar variables
	int spacebarCounter;
	bool twoSpaceBarsHit;

	//private methods. 
	void generateDisks();
	void initializeGridCells();
	float getMForXY(int x, int y, int deltaX, int deltaY , float c);
	void markIntersectedCellsForPositiveSlope(int * xP, int *yP, int *x, int *y, int deltaX, int deltaY, float c);
	void markIntersectedCellsForNegativeSlope(int * xP, int *yP, int *x, int *y, int deltaX, int deltaY, float c);

	//methods to calculate disc intersections
	void calculateIntersectedDiscs();
	void calculateParallelogramIntersectingDiscs();
	int getMForTwoPtEquation(int x, int y, int deltaX, int deltaY, int x1, int y1);

	//get the distance between two points.
	float getPointDistance(int x1, int y1, int x2, int y2);

	//get the dot product of two vectors
	int getDotProduct(MyPoint p1, MyPoint p2, MyPoint p3);

	//get the perpendicular distance 
	float getPerpendicularDistance(MyPoint p, MyPoint edgeVertex1, MyPoint edgeVertex2);
	
	//data structures for highlighting intersected discs.
	MyPoint discsToHighlight[1000];
	int discsToHighlightCounter;
	bool highlightDiscs;

    public:
	Grid(int height, int width);
	~Grid();

	void computeDiscIntersectedGridCells(Disk &d);
	void computeIntersectedCells();

	//getters for parallelogram intersected grid cells.
	MyPoint * getIntersectedGridCells();
	MyPoint * getOtherLineIntersectedGridCells();

	//methods to handle right click.
	bool rightClickedTwice();
	void resetGridRightClickParameters();	
	MyPoint getFirstRightClickCell();
	MyPoint getSecondRightClickCell();
	void registerRightClick(float x, float y);

	Disk gridDisks[NO_OF_DISCS];

	//getter for the parallelogram vertices.
	MyPoint * getParallelogramVertices();

	//getters for the intersected cells.
	int getLineIntersectedCellCount();
	int getOtherLineIntersectedCellCount();

	//spacebar handlers
	void registerSpaceBar();

	//highlighting discs getters
	bool highlightCells();
	MyPoint * getCellsToHighlight();
	int getHighlightingDiscsCount();

	//get the disks
	Disk * getDisks();
	
    };