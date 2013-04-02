#include "Grid.h"
#include<iostream>

#pragma region Grid class implementation.
Grid::Grid(const int height, const int width)
    {

    cout<<"Initializing Grid..."<<endl;
    //initialize the height and width
    this->height = height;
    this->width = width;

    //initialize grid cells.
    cout<<"Initializing grid cells.."<<endl;
    for(int i = 0 ; i < GRID_CELL_SIZE; i ++)
	{
	for(int j = 0 ; j < GRID_CELL_SIZE ; j ++)
	    {
	    gridCells[i][j].setBaseXY(i * GRID_CELL_SIZE, j * GRID_CELL_SIZE);
	    }
	}
    cout<<"Finished initializing grid cells."<<endl;

    //initialize the counters
    rightClickCounter = 1;
    lineIntersectedGridCellCounter = 0;
    otherLineIntersectedGridCellCounter = 0;
    twoRightClicks = false;

    //initialize disc highlighting params
    discsToHighlightCounter = 0;
    highlightDiscs = false;

    //initialize right click cells
    firstRightClickCellBase.x = -1;
    firstRightClickCellBase.y = -1;

    secondRightClickCellBase.x = -1;
    secondRightClickCellBase.y = -1;

    //initialize the spacebar parameters
    spacebarCounter = 0;
    twoSpaceBarsHit = false;

    //generate disks
    cout<<"Computing random locations and grid cell intersections for the discs.."<<endl;
    generateDisks();

    }

void Grid::generateDisks()
    {
    for(int i = 0 ; i < NO_OF_DISCS ; i ++)
	{
	MyPoint p;
	p.x = (rand() * 12343) % width; 
	p.y = (rand() * 12345) % height;

	//now we have our disk.
	Disk d(p);
	
	//compute the intersected grid cells.
	//cout<<"Evaluated "<<i<<" discs"<<"X: "<<p.x<<" Y: "<<p.y<<endl;
	//add the disk to the grid disk list
	gridDisks[i] = d;

	MyPoint center = d.getCenter();

	int discCenterX = d.getCenterX();
	int discCenterY = d.getCenterY();

	//straight forward case.
	gridCells[center.x/GRID_CELL_SIZE][center.y/GRID_CELL_SIZE].addIntersectedDisk(&gridDisks[i]);

	//\todo: calculate other intersected cells.
	int xBase = (gridCells[center.x/GRID_CELL_SIZE][center.y/GRID_CELL_SIZE].getBasePoint().x);
	int yBase = (gridCells[center.x/GRID_CELL_SIZE][center.y/GRID_CELL_SIZE].getBasePoint().y);
	int xEnd = xBase + GRID_CELL_SIZE;
	int yEnd = yBase + GRID_CELL_SIZE;

	//check intersection with the cell on the left of the current cell.
	if((discCenterX - xBase) <= Disk::radius && (center.x)/GRID_CELL_SIZE > 0)
	    gridCells[(center.x/GRID_CELL_SIZE) - 1][center.y/GRID_CELL_SIZE].addIntersectedDisk(&gridDisks[i]);

	//check intersection with the cell on top of the current cell.
	if((yEnd - discCenterY) <= Disk::radius)
	    gridCells[center.x/GRID_CELL_SIZE][center.y/GRID_CELL_SIZE + 1].addIntersectedDisk(&gridDisks[i]);

	//check intersection with the cell under the current cell.
	if((discCenterY - yBase) <= Disk::radius && (center.y/GRID_CELL_SIZE) > 0)
	    gridCells[center.x/GRID_CELL_SIZE][center.y/GRID_CELL_SIZE - 1].addIntersectedDisk(&gridDisks[i]);

	//check intersection with the cell on the right of the current cell.
	if((xEnd - discCenterX) <= Disk::radius)
	    gridCells[center.x/GRID_CELL_SIZE + 1][center.y/GRID_CELL_SIZE].addIntersectedDisk(&gridDisks[i]);

	//check intersection with the left-top cell
	if(fabs(getPointDistance(discCenterX, discCenterY, xBase, yBase + GRID_CELL_SIZE)) <= Disk::radius && (center.x)/GRID_CELL_SIZE > 0)
	    gridCells[center.x/GRID_CELL_SIZE - 1][center.y/GRID_CELL_SIZE + 1].addIntersectedDisk(&gridDisks[i]);

	//check intersection with the right-top cell
	if(fabs(getPointDistance(discCenterX, discCenterY, xBase + GRID_CELL_SIZE, yBase + GRID_CELL_SIZE)) <= Disk::radius)
	    gridCells[center.x/GRID_CELL_SIZE + 1][center.y/GRID_CELL_SIZE + 1].addIntersectedDisk(&gridDisks[i]);

	//check intersection with the right bottom cell
	if(fabs(getPointDistance(discCenterX, discCenterY, xBase + GRID_CELL_SIZE, yBase)) <= Disk::radius && (center.y/GRID_CELL_SIZE) > 0)
	    gridCells[center.x/GRID_CELL_SIZE + 1][center.y/GRID_CELL_SIZE - 1].addIntersectedDisk(&gridDisks[i]);

	//check intersection with the left bottom cell
	if(fabs(getPointDistance(discCenterX, discCenterY, xBase, yBase)) <= Disk::radius && (center.y/GRID_CELL_SIZE) > 0 && (center.x/GRID_CELL_SIZE) > 0)
	    gridCells[center.x/GRID_CELL_SIZE + 1][center.y/GRID_CELL_SIZE - 1].addIntersectedDisk(&gridDisks[i]);

	}
    std::cout<<"Finished generating and computing disk intersections"<<std::endl;
    }

float Grid::getPointDistance(int x1, int y1, int x2, int y2)
    {
    return sqrtf(pow((float)(y2-y1), 2) + pow((float)(x2-x1), 2));
    }

void Grid::calculateIntersectedDiscs()
    {
    cout<<"Calculating intersected discs..."<<endl;
    for(int i = 0; i < lineIntersectedGridCellCounter; i++)
	{
	//Disk** intersectedDiskList = 
	int gridDiscsCount = gridCells[(intersectedGridCells[i].x)/GRID_CELL_SIZE][(intersectedGridCells[i].y)/GRID_CELL_SIZE].getIntersectedDiscCount();

	if(gridDiscsCount == 0)
	    continue;;
	Disk ** discs = gridCells[(intersectedGridCells[i].x)/GRID_CELL_SIZE][(intersectedGridCells[i].y)/GRID_CELL_SIZE].getIntersectedDiskList();
	cout<<"Intersected a disc at cell: ("<<intersectedGridCells[i].x<<","<<intersectedGridCells[i].y<<")"<<endl;
	for(int i = 0 ; i < gridDiscsCount ; i++)
	    {
	    highlightDiscs = true;
	    discsToHighlight[discsToHighlightCounter].x = (**(discs + i)).getCenterX();
	    discsToHighlight[discsToHighlightCounter++].y = (**(discs + i)).getCenterY();	    
	    }
	}
    for(int i = 0; i < otherLineIntersectedGridCellCounter; i++)
	{
	//Disk** intersectedDiskList = 
	int gridDiscsCount = gridCells[(otherEdgeIntersectedGridCells[i].x)/GRID_CELL_SIZE][(otherEdgeIntersectedGridCells[i].y)/GRID_CELL_SIZE].getIntersectedDiscCount();

	if(gridDiscsCount == 0)
	    continue;;
	Disk ** discs = gridCells[(otherEdgeIntersectedGridCells[i].x)/GRID_CELL_SIZE][(otherEdgeIntersectedGridCells[i].y)/GRID_CELL_SIZE].getIntersectedDiskList();
	cout<<"Intersected a disc at cell: ("<<otherEdgeIntersectedGridCells[i].x<<","<<otherEdgeIntersectedGridCells[i].y<<")"<<endl;
	for(int i = 0 ; i < gridDiscsCount ; i++)
	    {
	    highlightDiscs = true;
	    discsToHighlight[discsToHighlightCounter].x = (**(discs + i)).getCenterX();
	    discsToHighlight[discsToHighlightCounter++].y = (**(discs + i)).getCenterY();	    
	    }
	}
    cout<<"Finished calculating discs intersection."<<endl;
    }

int Grid::getMForTwoPtEquation(int x, int y, int deltaX, int deltaY, int x1, int y1) 
    {
    int ans = deltaX *(y - y1) - deltaY * (x - x1);
    if(ans > 0)
	return 1;
    else if ( ans < 0 )
	return -1;
    else return 0;
    }

void Grid::calculateParallelogramIntersectingDiscs()
    {

    for(int i = 0 ; i < discsToHighlightCounter ; i ++)
	{
	int x = discsToHighlight[i].x;
	int y = discsToHighlight[i].y;

	//the below loop evaluates the point (x,y) against the parallelogram.
	//the disc might be inside the parallelogram, or intersecting it, or touching it.
	//the below loop does the above mentioned checks iteratively against each edge.

	int insideEdges = 0;
	//first: check if the point is inside the parallelogram.
	for(int j = 0 ; j < 4 ; j ++)
	    {
	    MyPoint edgeStartPoint = parallelogramVertices[j];
	    MyPoint edgeEndPoint = parallelogramVertices[(j+1)%4];

	    int deltaX = edgeEndPoint.x - edgeStartPoint.x;
	    int deltaY = edgeEndPoint.y - edgeStartPoint.y;

	    float slope = (float)(deltaY/deltaX);
	    float c = edgeStartPoint.y - (slope * edgeStartPoint.x);

	    //take another vertex to evaluate for the sign of f(x,y) for the 'inside' of this edge.
	    MyPoint testPoint = parallelogramVertices[(j+2)%4];
	    int testPointVal = getMForTwoPtEquation(testPoint.x, testPoint.y, deltaX, deltaY, edgeStartPoint.x, edgeStartPoint.y);
	    int discCenterVal = getMForTwoPtEquation(x, y, deltaX, deltaY, edgeStartPoint.x, edgeStartPoint.y);

	    if(discCenterVal == 0) //the point is on the edge, so it has to be inside the polygon
		{
		insideEdges = 4; //we don't have to evaluate other edges. 
		break;
		}
	    else if( testPointVal < 0.0 && discCenterVal < 0.0)
		insideEdges++;
	    else if( testPointVal > 0.0 && discCenterVal > 0.0)
		insideEdges++;
	    else //they're of both opp signs
		break;
	    }

	    if(insideEdges == 4)
		{
		discsToHighlight[i].x = -1;
		discsToHighlight[i].y = -1;
		continue; //ok, now that this disc has to disappear, no further processing is required. Continue with the next disc.
		}

	    //test code
	    MyPoint p, a, b, p1;
	    p.x = 2;
	    p.y = 0;

	    a.x = 0;
	    a.y = -1;

	    b.x = 0;
	    b.y = 1;

	    p1.x = 2;
	    p1.y = 2;
	    //int l = getPerpendicularDistance(p, a, b);
	    int l = getDotProduct(a, b, p);
	    int q = getDotProduct(a, b, p1);

	    //check if the disc has a valid projection on an edge. If yes, then the distance is the 
	    //horizontal distance between the disc and the edge, otherwise, the distance is the 
	    //distance between the center of the disc and the nearest vertex of the edge. 
	    for(int j = 0 ; j < 4 ; j ++)
		{
		MyPoint edgeStartPoint = parallelogramVertices[j];
		MyPoint edgeEndPoint = parallelogramVertices[(j+1)%4];

		int dotProduct = getDotProduct(edgeStartPoint, edgeEndPoint, discsToHighlight[i]);

		/*
		NOTE: the implementation of the discs intersecting the parallelogram at their vertices is not done. There was a
		bug that returned invalid answers for the dot product. That could be probably because of the varying nature of the 
		selection of edges of parallelogram. Hence, the cells those intersect the vertices of the parallelogram from a cell
		other than the start and the end cells are not highlighted and deleted on the second space bar hit.
		*/
		if(1)
		    {// the disc has a valid projection on the line. 
		    float distance = getPerpendicularDistance(discsToHighlight[i], edgeStartPoint, edgeEndPoint);

		    if(distance <= Disk::radius) 
			{    //the disc intersects the parallelogram
			discsToHighlight[i].x = -1;
			discsToHighlight[i].y = -1;
			}
		    }
		else
		    {
		    float dist1 = getPointDistance(discsToHighlight[i].x, discsToHighlight[i].y, edgeStartPoint.x, edgeStartPoint.y);
		    float dist2 = getPointDistance(discsToHighlight[i].x, discsToHighlight[i].y, edgeEndPoint.x, edgeEndPoint.y);

		    if((dist1 < dist2 && dist1 <= Disk::radius) || (dist2 < dist1 && dist2 <= Disk::radius))
			{
			discsToHighlight[i].x = -1;
			discsToHighlight[i].y = -1;
			}
		    }
		}
	}
    }

void Grid::registerSpaceBar()
    {
    if(!rightClickedTwice())
	{
	cout<<"Right click not done twice yet. Nothing to calculate, returning..."<<endl;
	return;
	}

    spacebarCounter = (++spacebarCounter) % 3;

    switch(spacebarCounter)
	{
    case 1: //spacebar hit for the first time.
	calculateIntersectedDiscs();
	break;

    case 2:
	calculateParallelogramIntersectingDiscs();
	break;

    case 0:
	resetGridRightClickParameters();
	break;
	}
    }

bool Grid::highlightCells()
    {
    return highlightDiscs;
    }

MyPoint* Grid::getCellsToHighlight()
    {
    return discsToHighlight;
    }

int Grid::getHighlightingDiscsCount()
    {
    return discsToHighlightCounter;
    }

void Grid::registerRightClick(float x, float y)
    {
    switch(rightClickCounter)
	{
    case 1: //first click.
	firstRightClickCellBase.x = ((int)x - ((int)x)%GRID_CELL_SIZE);
	firstRightClickCellBase.y = ((int)y - ((int)y)%GRID_CELL_SIZE);
	rightClickCounter++;

	break;

    case 2: //second click
	secondRightClickCellBase.x = ((int)x - ((int)x)%GRID_CELL_SIZE);
	secondRightClickCellBase.y = ((int)y - ((int)y)%GRID_CELL_SIZE);

	computeIntersectedCells();
	rightClickCounter++;

	twoRightClicks = true;

	break;
    case 3:
	resetGridRightClickParameters();
	break;
	}
    }

void Grid::resetGridRightClickParameters()
    {

    //reset counter and flag.
    rightClickCounter = 1;
    twoRightClicks = false;

    //reset the parallelogram
    for(int i = 0 ; i < 4 ; i ++)
	{
	parallelogramVertices[i].x = -1;
	parallelogramVertices[i].y = -1;
	}

    //reset the first and second right click cells.
    firstRightClickCellBase.x = -1;
    firstRightClickCellBase.y = -1;

    secondRightClickCellBase.x = -1;
    secondRightClickCellBase.y = -1;

    //reset the intersected cells
    lineIntersectedGridCellCounter = 0 ;
    otherLineIntersectedGridCellCounter = 0;

    //reset the highlighted discs
    discsToHighlightCounter = 0;

    //reset the spacebar counter
    spacebarCounter = 0;

    }

bool Grid::rightClickedTwice()
    {
    return twoRightClicks;
    }

MyPoint * Grid::getParallelogramVertices()
    {
    return parallelogramVertices;
    }

void Grid::markIntersectedCellsForPositiveSlope(int * xP, int *yP, int *x, int *y, int deltaX, int deltaY, float c)
    {
    float fXY = getMForXY(*xP, *yP, deltaX, deltaY, c);
    if(fXY == 0) //the line passes through M
	{
	//mark the diagonally opposite cell
	intersectedGridCells[lineIntersectedGridCellCounter].x = ((*x) + 1) * GRID_CELL_SIZE;
	intersectedGridCells[lineIntersectedGridCellCounter++].y = (*y) * GRID_CELL_SIZE;

	intersectedGridCells[lineIntersectedGridCellCounter].x = (*x) * GRID_CELL_SIZE;
	intersectedGridCells[lineIntersectedGridCellCounter++].y = ((*y) + 1) * GRID_CELL_SIZE;

	(*x)++;
	(*y)++;
	}
    else if (fXY > 0) 
	(*y)++;
    else
	(*x)++;

    intersectedGridCells[lineIntersectedGridCellCounter].x = (*x) * GRID_CELL_SIZE;
    intersectedGridCells[lineIntersectedGridCellCounter++].y = (*y) * GRID_CELL_SIZE;

    *xP = *x + 1;
    *yP = *y + 1;
    }

void Grid::markIntersectedCellsForNegativeSlope(int *xP, int *yP, int *x, int *y, int deltaX, int deltaY, float c)
    {
    float fXY = getMForXY(*xP, *yP, deltaX, deltaY, c);
     if(fXY == 0) //the line passes through M
	{
	
	//the adjecent cells are also intersected!
	intersectedGridCells[lineIntersectedGridCellCounter].x = (*x) * GRID_CELL_SIZE;
	intersectedGridCells[lineIntersectedGridCellCounter++].y = ((*y) - 2) * GRID_CELL_SIZE;
	
	intersectedGridCells[lineIntersectedGridCellCounter].x = ((*x) + 1) * GRID_CELL_SIZE;
	intersectedGridCells[lineIntersectedGridCellCounter++].y = ((*y) - 1) * GRID_CELL_SIZE;

	//mark the diagonally opposite cell
	(*x)++;
	(*y)--;
	}
    else if (fXY > 0) 
	(*x)++;
    else
	(*y)--;

    intersectedGridCells[lineIntersectedGridCellCounter].x = (*x) * GRID_CELL_SIZE;
    intersectedGridCells[lineIntersectedGridCellCounter++].y = ((*y) - 1) * GRID_CELL_SIZE;

    *xP = *x + 1;
    *yP = *y - 1;
    }

void Grid::computeIntersectedCells()
    {

    //calculate the slope first. Based on the slope, the way we have to 
    //calculate the intersected cells is decided.


    //set the cell with lowest 'x' value to be stored in the first right click variable.
    if(secondRightClickCellBase.x < firstRightClickCellBase.x)
	{
	MyPoint p = secondRightClickCellBase;
	secondRightClickCellBase = firstRightClickCellBase;
	firstRightClickCellBase = p;
	}


    int deltaX = (secondRightClickCellBase.x - firstRightClickCellBase.x)/GRID_CELL_SIZE;
    int deltaY = (secondRightClickCellBase.y - firstRightClickCellBase.y)/GRID_CELL_SIZE;

    float c = 0.0f;

    float slope = ((float)deltaY)/((float)deltaX);

    //first case
    if(slope>0.0)
	{

	//calculate the parallelogram vertices;
	parallelogramVertices[0].x = firstRightClickCellBase.x + GRID_CELL_SIZE;
	parallelogramVertices[0].y = firstRightClickCellBase.y;

	parallelogramVertices[1].x = firstRightClickCellBase.x;
	parallelogramVertices[1].y = firstRightClickCellBase.y + GRID_CELL_SIZE;

	parallelogramVertices[2].x = secondRightClickCellBase.x;
	parallelogramVertices[2].y = secondRightClickCellBase.y + GRID_CELL_SIZE;

	parallelogramVertices[3].x = secondRightClickCellBase.x + GRID_CELL_SIZE;
	parallelogramVertices[3].y = secondRightClickCellBase.y;

	//suppose the line is defined as y = mx + c, m is the slope, which is calculated.
	//set the start and the end points.
	MyPoint startPoint, endPoint;

	startPoint.x = (firstRightClickCellBase.x + GRID_CELL_SIZE)/GRID_CELL_SIZE;
	startPoint.y = (firstRightClickCellBase.y)/GRID_CELL_SIZE;

	endPoint.x = (secondRightClickCellBase.x + GRID_CELL_SIZE)/GRID_CELL_SIZE;
	endPoint.y = (secondRightClickCellBase.y)/GRID_CELL_SIZE;

	//calculating 'C'>>>>

	c = startPoint.y - (slope * startPoint.x);

	//mark the start point as intersected.
	intersectedGridCells[lineIntersectedGridCellCounter].x = startPoint.x * GRID_CELL_SIZE;
	intersectedGridCells[lineIntersectedGridCellCounter++].y = startPoint.y * GRID_CELL_SIZE;

	int x = startPoint.x;
	int y = startPoint.y;

	int xP = x + 1, yP = y + 1;

	//check if slope is > 1 or < 1. Based on this, the intersected cells are calculated.
	if(slope < 1)
	    {
	    //following the algorithm developed....
	    while(xP < endPoint.x)
		{
		markIntersectedCellsForPositiveSlope(&xP, &yP, &x, &y, deltaX, deltaY, c);
		}
	    }
	else
	    {
	    while(yP < endPoint.y)
		{
		markIntersectedCellsForPositiveSlope(&xP, &yP, &x, &y, deltaX, deltaY, c);
		}
	    }
	//mark the cells intersected by the other edge of the parallelogram line as well.
	for( ; otherLineIntersectedGridCellCounter < lineIntersectedGridCellCounter ; otherLineIntersectedGridCellCounter++)
	    {
	    otherEdgeIntersectedGridCells[otherLineIntersectedGridCellCounter].x = intersectedGridCells[otherLineIntersectedGridCellCounter].x - GRID_CELL_SIZE;
	    otherEdgeIntersectedGridCells[otherLineIntersectedGridCellCounter].y = intersectedGridCells[otherLineIntersectedGridCellCounter].y + GRID_CELL_SIZE;
	    }
	}
    else 
	{
	//calculate the parallelogram vertices;
	parallelogramVertices[0].x = firstRightClickCellBase.x;
	parallelogramVertices[0].y = firstRightClickCellBase.y;

	parallelogramVertices[1].x = secondRightClickCellBase.x;
	parallelogramVertices[1].y = secondRightClickCellBase.y;

	parallelogramVertices[2].x = secondRightClickCellBase.x + GRID_CELL_SIZE;
	parallelogramVertices[2].y = secondRightClickCellBase.y + GRID_CELL_SIZE;

	parallelogramVertices[3].x = firstRightClickCellBase.x + GRID_CELL_SIZE;
	parallelogramVertices[3].y = firstRightClickCellBase.y + GRID_CELL_SIZE;

	//suppose the line is defined as y = mx + c, m is the slope, which is calculated.
	//set the start and the end points.
	MyPoint startPoint, endPoint;

	startPoint.x = (firstRightClickCellBase.x)/GRID_CELL_SIZE;
	startPoint.y = (firstRightClickCellBase.y)/GRID_CELL_SIZE;

	endPoint.x = (secondRightClickCellBase.x)/GRID_CELL_SIZE;
	endPoint.y = (secondRightClickCellBase.y)/GRID_CELL_SIZE;

	c = startPoint.y - (slope * startPoint.x);

	//mark the start point as intersected.
	intersectedGridCells[lineIntersectedGridCellCounter].x = startPoint.x * GRID_CELL_SIZE;
	intersectedGridCells[lineIntersectedGridCellCounter++].y = (startPoint.y - 1)* GRID_CELL_SIZE;

	int x = startPoint.x;
	int y = startPoint.y;

	int xP = x + 1, yP = y - 1;

	if(fabs(slope) < 1.0)
	    {
	    while(xP < endPoint.x)
		{
		markIntersectedCellsForNegativeSlope(&xP, &yP, &x, &y, deltaX, deltaY, c);
		}
	    }
	else
	    {
	    while(yP > endPoint.y)
		{
		markIntersectedCellsForNegativeSlope(&xP, &yP, &x, &y, deltaX, deltaY, c);
		}
	    }
	for( ; otherLineIntersectedGridCellCounter < lineIntersectedGridCellCounter; otherLineIntersectedGridCellCounter++)
	    {
	    otherEdgeIntersectedGridCells[otherLineIntersectedGridCellCounter].x = intersectedGridCells[otherLineIntersectedGridCellCounter].x + GRID_CELL_SIZE;
	    otherEdgeIntersectedGridCells[otherLineIntersectedGridCellCounter].y = intersectedGridCells[otherLineIntersectedGridCellCounter].y + GRID_CELL_SIZE;
	    }
	}
    }
    
MyPoint * Grid::getOtherLineIntersectedGridCells()
    {
    return otherEdgeIntersectedGridCells;
    }

MyPoint * Grid::getIntersectedGridCells()
    {
    return intersectedGridCells;
    }

int Grid::getLineIntersectedCellCount()
    {
    return lineIntersectedGridCellCounter;
    }

int Grid::getOtherLineIntersectedCellCount()
    {
    return otherLineIntersectedGridCellCounter;
    }

MyPoint Grid::getFirstRightClickCell()
    {
    return firstRightClickCellBase;
    }

MyPoint Grid::getSecondRightClickCell()
    {
    return secondRightClickCellBase;
    }

float Grid::getMForXY(int x, int y, int deltaX, int deltaY, float c)
    {
    int t1 = deltaY * x;
    int t2 = deltaX * y;
    float t3 = deltaX * c;

    float ans = t3 + t1 - t2;

    if(ans > 0.0)
	return 1;
    else if (ans < 0.0)
	return -1;
    else return 0;
    }

Disk * Grid::getDisks()
    {
    return gridDisks;
    }

int Grid::getDotProduct(MyPoint p1, MyPoint p2, MyPoint p3)
    {
    //consider vector p2->p1 and p3->p1
    int firstVectorXComponent = p2.x - p1.x;
    int firstVectorYComponent = p2.y - p1.y;

    int secVectorXComponent = p3.x - p1.x;
    int secVectorYComponent = p3.y - p1.y;

    return ((firstVectorXComponent * secVectorXComponent) + (firstVectorYComponent * secVectorYComponent)) ;

    }

float Grid::getPerpendicularDistance(MyPoint p, MyPoint edgeVertex1, MyPoint edgeVertex2)
    {

    int deltaX = edgeVertex2.x - edgeVertex1.x;
    int deltaY = edgeVertex2.y - edgeVertex1.y;

    int t1 = deltaX *(p.y - edgeVertex1.y);
    int t2 = deltaY *(p.x - edgeVertex1.x);

    float numerator = pow((float)(t1 - t2), 2);
    float denominator = pow((float)deltaX, 2) + pow((float)deltaY, 2);

    return sqrt(numerator/denominator);
    }

Grid::~Grid()
    {
    }

#pragma endregion

#pragma region GridCell class Implementation

Disk ** GridCell::getIntersectedDiskList()
    {
    return intersectedDiscs;
    }

int GridCell::getIntersectedDiscCount()
    {
    return intersectedDiscCount;
    }

GridCell::GridCell()
    {
    intersectedDiscCount = 0;
    }

void GridCell::addIntersectedDisk(Disk *d)
    {
    if(intersectedDiscCount < 200)
	intersectedDiscs[intersectedDiscCount++] = d;
    }

MyPoint GridCell::getBasePoint()
    {
    return base;
    }

void GridCell::setBaseXY(int x, int y)
    {
    base.x = x;
    base.y = y;
    }

#pragma endregion

#pragma region Disk class Implementation
Disk::Disk()
    {

    }

Disk::Disk(MyPoint p)
    {
    center.x = p.x;
    center.y = p.y;
    }
void Disk::setCenter(MyPoint p)
    {
    center.x = p.x;
    center.y = p.y;
    }

MyPoint Disk::getCenter()
    {
    return center;
    }

int Disk::getCenterX()
    {
    return center.x;
    }

int Disk::getCenterY()
    {
    return center.y;
    }

void Disk::setCenterX(int x)
    {
    center.x = x;
    }

void Disk::setCenterY(int y)
    {
    center.y = y;
    }
#pragma endregion
