//-------------------------------------------
// GLWidget.h -- declarations for the OpenGL
//               drawing area
//-------------------------------------------

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <vector>

using namespace std;

#include "glDefs.h"

#include "primitives.h"
#include "mainWindow.h"

class GLWidget
{
  private:

    int num_pts_line, num_pts_poly, num_pts_free;

    GLuint shader_program;

	enum DrawMode 
        { DrawLine, DrawTriangle, DrawPolygon, ClearScreen} draw_mode;


	GLfloat *line_verts, *line_cols,	// line data
			*tri_verts, *tri_cols;		// triangle data

	//polygon data:
	GLfloat *poly_verts;
	int polygon_vertices;
	GLuint ** polyIndices;
	int noOfPolygons;
	
	GLuint  vao[2], vbo[4], vPosition, vColor;

	int		line_verts_size, line_cols_size,
			tri_verts_size, tri_cols_size,
			num_tri_pts;

	int 	width, height;
	bool 	Initialized;
	Line currentLine;
	PolyLine currentPolyline;
	FreeHandCurve currentCurvedline;

	void UpdatePrimitiveData(void);

	/**
	*   Polygon rendering params
	*/
	//vectors for vertices, indices and indices counts
	GLfloat ** polygonVertices;
	GLuint * polygonIndicesCounts;
	GLuint ** polygonIndices;
	GLfloat * polygonColors;

	//counters for the vectors. 
	GLint polygonCount;
	GLint polygonVerticesCounter;
	GLint currentPolygonVerticesCounter;
	GLint polygonIndicesArrayCounter;
	GLint polygonColorCounter;

	bool polygonVerticesCounting;

	//vertex array object and two vertex buffers. One for color and one for vertices. 
	GLuint polygonVAO, polygonVBO[3];

  public:

    GLWidget();

    void setWindowExtents();
    void handleMouseEvent( int button, int state, int x, int y);
	void handleUI (int control);
    void draw();
    void clearScreen();
	void init();
	GLuint initShader(const char*, const char*);

	Point pts[4];
									// until completely drawn
	PolyLine current_poly;
	FreeHandCurve current_curved_line;

	int num_polylines, num_free;

							// handle
	static GLWidget *current;
	
	static GLWidget*  getCurrent(void)
	{
		return current;
	}

	void setDimensions (int w, int h) {
		width = w; height = h;
    }

    void screen_to_ndc (int x, int y, float *ndc_x, float *ndc_y) {
						// assume the default ndc (-1 to 1 in X and Y)
		*ndc_x = 2.*x/width - 1.;
		*ndc_y = -2.*y/height +1;
	}

	enum DrawMode getDrawMode() {
        return  draw_mode;
    }

	void setDrawMode (int mode) {
		switch (mode) {
			case 0:  draw_mode = DrawLine; break;
			case 2:  draw_mode = DrawTriangle; break;
			case 3:  draw_mode = ClearScreen; break;
		}
    }

	void myTest();
	void drawPolygons();
	void rotateCube();
};

#endif // GLWIDGET_H
