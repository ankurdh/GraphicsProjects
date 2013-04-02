#include<math.h>
#include<stdlib.h>

#if 0
#include <GL/gl.h>
#else
// replacement for GL/gl.h incase an advanced student wants to use OGL extensions, OGL 2.1, etc.
#include <GL/glew.h>   
#endif

#include <GL/GLU.h>
#include <GL/glut.h>

#include <iostream>
#include "Grid.h"
using namespace std;

//Define constants.
#define GRID_DL_ID 1
#define DISC_DL_ID 2

#define INDIVIDUAL_DISC_DL_ID 3
#define VERTICAL_GRID_LINE_DL_ID 4
#define HORIZONTAL_GRID_LINE_DL_ID 5

class DisplayListHelper
    {
    private:
	int HEIGHT, WIDTH;
	Grid &g;
    public:
	DisplayListHelper(const int height, const int width, Grid & grid);
	void createIndividialDiscDL();
	void createDiscDL();
	void createHorizontalLineDL();
	void createVerticalLineDL();
	void createGridDL();

	void refreshDiscDL();
    };