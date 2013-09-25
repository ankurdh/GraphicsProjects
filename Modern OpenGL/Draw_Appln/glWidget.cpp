//--------------------------------------------------
// GLWidget.cpp -- implementation of GLWidget class
//--------------------------------------------------
//
// User vertex array objects, vertex buffer objects, shaders using OpenGL 3.2 or 
// above, GLSL v150
//
// Author: Kalpathi Subramanian, Aug. 16, 2013.
//

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/ext.hpp>

#include <math.h>
#include <iostream>

#include "glWidget.h"
#include "mainWindow.h"
#include "textfile.h"

#include <iostream>
#include <fstream>
#include <sstream>

#define VERTICES 0
#define COLORS 1
#define INDICES 2

// bad! using constants, need to fix
#define MAX_VERT_DATA   1000
#define MAX_COL_DATA	1000
#define MAX_CURR_DATA   200

#define BUFFER_OFFSET(bytes) ((GLvoid *) NULL + bytes)

static float timeElapsed = 0.0f; 

GLWidget *GLWidget::current = NULL;

GLfloat const vertices1[] = { 0.2, 0.2, 0.2,  -0.2, 0.2, 0.2,  -0.2,-0.2, 0.2,      // v0-v1-v2 (front)
    -0.2,-0.2, 0.2,   0.2,-0.2, 0.2,   0.2, 0.2, 0.2,      // v2-v3-v0

    0.2, 0.2, 0.2,   0.2,-0.2, 0.2,   0.2,-0.2,-0.2,      // v0-v3-v4 (right)
    0.2,-0.2,-0.2,   0.2, 0.2,-0.2,   0.2, 0.2, 0.2,      // v4-v5-v0

    0.2, 0.2, 0.2,   0.2, 0.2,-0.2,  -0.2, 0.2,-0.2,      // v0-v5-v6 (top)
    -0.2, 0.2,-0.2,  -0.2, 0.2, 0.2,   0.2, 0.2, 0.2,      // v6-v0.2-v0

    -0.2, 0.2, 0.2,  -0.2, 0.2,-0.2,  -0.2,-0.2,-0.2,      // v0.2-v6-v7 (left)
    -0.2,-0.2,-0.2,  -0.2,-0.2, 0.2,  -0.2, 0.2, 0.2,      // v7-v2-v0.2

    -0.2,-0.2,-0.2,   0.2,-0.2,-0.2,   0.2,-0.2, 0.2,      // v7-v4-v3 (bottom)
    0.2,-0.2, 0.2,  -0.2,-0.2, 0.2,  -0.2,-0.2,-0.2,      // v3-v2-v7

    0.2,-0.2,-0.2,  -0.2,-0.2,-0.2,  -0.2, 0.2,-0.2,      // v4-v7-v6 (back)
    -0.2, 0.2,-0.2,   0.2, 0.2,-0.2,   0.2,-0.2,-0.2 };    // v6-v5-v4


static GLfloat vertices_rotated[] = { 0.2, 0.2, 0.2,  -0.2, 0.2, 0.2,  -0.2,-0.2, 0.2,      // v0-v1-v2 (front)
    -0.2,-0.2, 0.2,   0.2,-0.2, 0.2,   0.2, 0.2, 0.2,      // v2-v3-v0

    0.2, 0.2, 0.2,   0.2,-0.2, 0.2,   0.2,-0.2,-0.2,      // v0-v3-v4 (right)
    0.2,-0.2,-0.2,   0.2, 0.2,-0.2,   0.2, 0.2, 0.2,      // v4-v5-v0

    0.2, 0.2, 0.2,   0.2, 0.2,-0.2,  -0.2, 0.2,-0.2,      // v0-v5-v6 (top)
    -0.2, 0.2,-0.2,  -0.2, 0.2, 0.2,   0.2, 0.2, 0.2,      // v6-v0.2-v0

    -0.2, 0.2, 0.2,  -0.2, 0.2,-0.2,  -0.2,-0.2,-0.2,      // v0.2-v6-v7 (left)
    -0.2,-0.2,-0.2,  -0.2,-0.2, 0.2,  -0.2, 0.2, 0.2,      // v7-v2-v0.2

    -0.2,-0.2,-0.2,   0.2,-0.2,-0.2,   0.2,-0.2, 0.2,      // v7-v4-v3 (bottom)
    0.2,-0.2, 0.2,  -0.2,-0.2, 0.2,  -0.2,-0.2,-0.2,      // v3-v2-v7

    0.2,-0.2,-0.2,  -0.2,-0.2,-0.2,  -0.2, 0.2,-0.2,      // v4-v7-v6 (back)
    -0.2, 0.2,-0.2,   0.2, 0.2,-0.2,   0.2,-0.2,-0.2 };    // v6-v5-v4


// normal array
GLfloat normals1[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
    0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

    1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
    1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

    0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
    0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

    -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
    -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

    0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
    0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

    0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
    0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4

// color array
GLfloat colors1[]   = { 1, 0, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
    1, 0, 0,   1, 0, 1,   1, 0, 1,      // v2-v3-v0

    1, 0, 1,   1, 0.8, 1,   0, 0, 1,      // v0-v3-v4 (right)
    0, 0, 1,   0, 1, 1,   1, 0, 1,      // v4-v5-v0

    1, 1, 0,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
    0, 1, 0,   1, 1, 0,   1, 1, 0,      // v6-v1-v0

    1, 1, 0,   0, 1, 0,   0, 0, 1,      // v1-v6-v7 (left)
    0, 0, 1,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

    0, 0, 1,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
    1, 0, 1,   1, 0, 0,   0, 0, 1,      // v3-v2-v7

    0, 0, 1,   0, 0, 1,   0, 1, 0,      // v4-v7-v6 (back)
    0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4



//======================================================================
GLWidget::GLWidget()
    {

    num_pts_line = num_pts_poly = num_pts_free = 0;

    // allocate vectors  to store geometry

    num_tri_pts = 0;

    current_poly.setLineWidth(1.0);
    current_curved_line.setLineWidth(1.0);

    current = this;

    // initializations for setting up vertex array objects
    // vertex buffer objects

    // some allocations for GL formatted arrays
    // assume a max of 100 points
    line_verts = new GLfloat[MAX_VERT_DATA];
    line_cols = new GLfloat[MAX_COL_DATA];
    tri_verts = new GLfloat[MAX_VERT_DATA];
    tri_cols = new GLfloat[MAX_COL_DATA];

    // allocate space for current primitive 
    line_verts_size = line_cols_size = 0;
    tri_verts_size = tri_cols_size = 0;

    // allocate a VAO for each type of primitive
    glGenVertexArrays (2, vao); 
    // alloate  2 VBOs per object type
    glGenBuffers(4, vbo);

    draw_mode = DrawLine;

    //Initialize polygon data
    polygonVertices = new GLfloat *[MAX_VERT_DATA];
    polygonIndicesCounts = new GLuint [MAX_VERT_DATA];
    polygonIndices = new GLuint *[MAX_VERT_DATA];
    polygonColors = new GLfloat [MAX_COL_DATA];

    polygonCount = 0;
    polygonColorCounter = 0;
    polygonVerticesCounter = 0;
    polygonIndicesArrayCounter = 0;
    currentPolygonVerticesCounter = 0;

    polygonVerticesCounting = false;

    glGenVertexArrays(1, &polygonVAO);
    glGenBuffers(3, polygonVBO);
    
    cout << "initializing.." << endl;
    }

void GLWidget::drawPolygons(){

    static GLfloat vertices[] = {
	//draw a quad first.
	0.3f, 0.2f, 0.0f, 1.0f,
	-0.1f, 0.2f, 0.0f, 1.0f,
	-0.1f, -0.2f, 0.0f, 1.0f,
	0.3f, -0.2f, 0.0f, 1.0f,

	//then draw a polygon
	-0.70f, 0.2f, 0.0f, 1.0f,
	-0.85f, 0.04f, 0.0f, 1.0f, 
	-0.78f, -0.181f, 0.0f, 1.0f,
	-0.59f, -0.170f, 0.0f, 1.0f,
	-0.54f, -0.053f, 0.0f, 1.0f
	};

    static GLuint indices[] = {
	//give the quadrilateral indices first.
	0, 1, 2, 3,

	//give the polygon indices
	4, 5, 6, 7, 8
	};

    static GLuint indexOffsets[] = {
	//the quadrilateral offset is 0 since the indices from 0th element are the quad indices.
	0,  

	//the polygon offset is starting from the 4th element in the index array.	
	sizeof(GLuint)*4 
	};

    static GLsizei elementCounts[] = {
	//its 4 elements for the quad and 5 for the pentagon
	4, 5};

	static GLfloat colors[] = {

	    //quadrilateral colors
	    0.4f, 0.2f, 0.7f, 1.0f,
	    0.7f, 0.8f, 0.1f, 1.0f,
	    0.3f, 0.7f, 0.8f, 1.0f,
	    0.2f, 0.5f, 0.7f, 1.0f,

	    //pentagon colors
	    0.84f, 0.26f, 0.67f, 1.0f,
	    0.7f, 0.8f, 0.31f, 1.0f,
	    0.93f, 0.17f, 0.48f, 1.0f,
	    0.72f, 0.25f, 0.27f, 1.0f,
	    0.7f, 0.8f, 0.81f, 1.0f

	    };

	const GLuint polyCount = 2;

	GLuint polyVAO, polyVBO[3];
	glGenVertexArrays(1, &polyVAO);
	glGenBuffers(3, polyVBO);

	glBindVertexArray(polyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, polyVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);

	glBindBuffer(GL_ARRAY_BUFFER, polyVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, polyVBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//The glDrawElements Version 
	//for(int i = 0 ; i < polyCount ; i ++)
	//glDrawElements(GL_TRIANGLE_FAN, elementCounts[i], GL_UNSIGNED_INT, (const GLvoid*)indexOffsets[i]);

	//The glMultiDrawElements version
	glMultiDrawElements(GL_TRIANGLE_FAN, elementCounts, GL_UNSIGNED_INT, (const GLvoid **)indexOffsets, polyCount);

    }

//======================================================================
void  GLWidget::handleMouseEvent(int button, int state, int x, int y) {
    // handles mouse  events
    switch(state) {
	// Mouse button pressed
    case GLUT_DOWN:

	if (button == GLUT_RIGHT_BUTTON){

	    if(!polygonVerticesCounting)
		return;

	    polygonVerticesCounting = false;
	    currentPolygonVerticesCounter = 0;
	    polygonCount ++;

	    //This should trigger a polygon draw
	    printf("Polygon Vertices: %d\n", polygonVerticesCounter);
	    for(int i = 0 ; i < polygonVerticesCounter; i ++)
		printf("(%.2f, %.2f)\t", polygonVertices[i][0], polygonVertices[i][1]);

	    printf("\nPolygon index count array:\n");
	    for(int i = 0 ; i < polygonCount; i ++)
		printf("  %d", polygonIndicesCounts[i]);

	    printf("\nPolygon Indices: %d\n", polygonIndicesCounts[polygonCount - 1]);
	    for(int j = 0 ; j < polygonCount; j ++){
		for(int i = 0 ; i < polygonIndicesCounts[j] ; i ++){
		    printf("%d  ", polygonIndices[j][i]);
		    }
		printf("\n");
		}

	    printf("\nPolygon Colors: %d\n", polygonColorCounter);
	    for(int i = 0 ; i < polygonColorCounter; i += 4)
		printf("(%.2f, %.2f, %.2f)\t", polygonColors[i], polygonColors[i + 1], polygonColors[i+2]);

	    UpdatePrimitiveData();
	    }

	// left button accepts point input
	if (button == GLUT_LEFT_BUTTON) {
	    switch (draw_mode) {

	    case DrawPolygon:
		if(!polygonVerticesCounting){
		    polygonIndices[polygonCount] = new GLuint[MAX_VERT_DATA];
		    polygonIndicesCounts[polygonCount] = 0;
		    polygonVerticesCounting = true;
		    }
		float ndc_x, ndc_y;
		screen_to_ndc(x, y, &ndc_x, &ndc_y);

		printf("Polygon vertex at: %.2f, %.2f\n", ndc_x, ndc_y);

		/*polygonVertices[polygonVerticesCounter] = ndc_x;
		polygonVertices[polygonVerticesCounter+1] = ndc_y;
		polygonVertices[polygonVerticesCounter+2] = 0.0f;
		polygonVertices[polygonVerticesCounter+3] = 1.0f;*/

		polygonVertices[polygonVerticesCounter] = new GLfloat[4];

		polygonVertices[polygonVerticesCounter][0] = ndc_x;
		polygonVertices[polygonVerticesCounter][1] = ndc_y;
		polygonVertices[polygonVerticesCounter][2] = 0.0f;
		polygonVertices[polygonVerticesCounter][3] = 1.0f;

		polygonColors[polygonColorCounter++] = 1.0f;
		polygonColors[polygonColorCounter++] = 1.0f;
		polygonColors[polygonColorCounter++] = 0.0f;
		polygonColors[polygonColorCounter++] = 1.0f;

		polygonIndices[polygonCount][currentPolygonVerticesCounter++] = polygonVerticesCounter;
		polygonIndicesCounts[polygonCount] ++;
		polygonVerticesCounter ++;

		break;

	    case DrawLine: 
		if (!num_pts_line) {
		    // Get the first point on the line
		    pts[0].x = x; pts[0].y = y;
		    num_pts_line++;
		    }
		else { 				// second point
		    pts[1].x = x; pts[1].y = y;
		    num_pts_line++;
		    num_pts_line  = 0;
		    // store the line segment into vertex array
		    UpdatePrimitiveData();
		    }
		break;

	    case DrawTriangle: 		// add point to current poly
		pts[num_tri_pts].x  = x;
		pts[num_tri_pts].y  = y;
		num_tri_pts++;
		if (num_tri_pts == 3) { 
		    // 3 points done, store in vertex array
		    UpdatePrimitiveData(); 
		    num_tri_pts = 0;
		    }
		break;
		}
	    }
	}
    }

int CalculateFrameRate()
    {

        static float framesPerSecond    = 0.0f;       // This will store our fps
        static float lastTime   = 0.0f;       // This will hold the time from the last frame
        float currentTime = GetTickCount() * 0.001f;    
        ++framesPerSecond;
        if( currentTime - lastTime > 1.0f )
        {
            lastTime = currentTime;
            int currentFrameRate = (int)framesPerSecond;
            framesPerSecond = 0;
	    return currentFrameRate;
        }
	return -1;
    }

void GLWidget::rotateCube(){

    //rotate by .05 degree per frame.
    timeElapsed += 0.05f;
    
    }

//======================================================================
void GLWidget::draw() {

    //drawPolygons();

    //draw a wire cube
    glBindVertexArray(polygonVAO);
    
#pragma region Draw and Rotate two Cubes at different rotation speeds & rotation axes

    glBindBuffer(GL_ARRAY_BUFFER, polygonVBO[VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rotated), vertices_rotated, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);
    
    glBindBuffer(GL_ARRAY_BUFFER, polygonVBO[COLORS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vColor);

    GLfloat alpha = 0.1f;
    glUniform1f(glGetUniformLocation(shader_program, "alpha"), alpha);

    glm::mat4 projectionMatrix = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
    glm::mat4 modelViewMatrix = glm::lookAt(glm::vec3(5,0,0), glm::vec3(0,0,0), glm::vec3(0,1,0));
    
    glm::mat4 objectToCameraTransformation(projectionMatrix * modelViewMatrix);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "objectToCameraTransformation"), 1, GL_FALSE, glm::value_ptr(objectToCameraTransformation));
    
    //draw two rotating cubes
    glm::mat4 translationMatrix = glm::translate(1.0f, 1.0f, 1.0f);
    glm::mat4 rotationMatrix = glm::rotate(timeElapsed, 0.50f, 0.50f, 0.50f);
    glm::mat4 scaleMat(glm::scale(glm::vec3(1.0f, 1.0f, 1.0f)));
    
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "rotationMat"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "translationMat"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "scaleMat"), 1, GL_FALSE, glm::value_ptr(scaleMat));
    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    alpha = 0.5f;
    glUniform1f(glGetUniformLocation(shader_program, "alpha"), alpha);

    scaleMat = glm::scale(glm::vec3(3.0f, 3.0f, 3.0f));
    rotationMatrix = glm::rotate(timeElapsed * 3.0f, 0.10f, 0.250f, 0.850f);
    translationMatrix = glm::translate(-1.0f, -1.0f, -1.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader_program, "rotationMat"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "translationMat"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "scaleMat"), 1, GL_FALSE, glm::value_ptr(scaleMat));
    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    alpha = 0.9f;
    glUniform1f(glGetUniformLocation(shader_program, "alpha"), alpha);

    scaleMat = glm::scale(glm::vec3(1.5f, 1.5f, 1.5f));
    rotationMatrix = glm::rotate(timeElapsed * 2.5f, 0.10f, 0.250f, 0.850f);
    translationMatrix = glm::translate(1.0f, 1.0f, 3.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader_program, "rotationMat"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "translationMat"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "scaleMat"), 1, GL_FALSE, glm::value_ptr(scaleMat));
    glDrawArrays(GL_TRIANGLES, 0, 12*3);

#pragma endregion

    glBindVertexArray(0);
    glFlush();

    int currentFrameRateValue = CalculateFrameRate();

    if(currentFrameRateValue != -1){
	std::stringstream currentFrameRate;
	currentFrameRate << "Framerate: " << currentFrameRateValue;
	glutSetWindowTitle(currentFrameRate.str().c_str());
	}

    }
//======================================================================
void	GLWidget::handleUI(int control) {

    // clear any partially drawn primitives
    current_poly.clear();
    current_curved_line.clear();

    cout << "Running GL Version: " << glGetString(GL_VERSION) << endl; 
    // set draw mode
    switch (control) {
    case 0 : 
	draw_mode = DrawLine;
	MainWindow::getCurrent()->currentDrawMode = "Current Draw Mode: Lines (Click on two points in the play area)";
	break;
    case 1 : 		// triangles
	MainWindow::getCurrent()->currentDrawMode = "Current Draw Mode: Triangles (Click on three points in the play area)";
	draw_mode = DrawTriangle;
	break;

    case 2:
	draw_mode = DrawPolygon;
	break;

    case 3: 
	// not implemented
	MainWindow::getCurrent()->currentDrawMode = "Select One of Lines/Triangles mode to begin drawing";
	draw_mode = ClearScreen;
	glutPostRedisplay();
	break;
	}

    MainWindow::getCurrent()->refreshWindow();
    std::cout<<"Current Draw Mode: "<<MainWindow::getCurrent()->currentDrawMode<<std::endl;

    }
//======================================================================
void	GLWidget::UpdatePrimitiveData() {

    float ndc_x, ndc_y;

    switch (draw_mode) {
    case DrawLine: 
	for (int k = 0; k < 2; k++) {
	    screen_to_ndc(pts[k].x, pts[k].y, &ndc_x, &ndc_y);
	    line_verts[line_verts_size++] = ndc_x; 
	    line_verts[line_verts_size++] = ndc_y;
	    line_verts[line_verts_size++] = 0.; 
	    line_verts[line_verts_size++] = 1.;


	    switch (k) {
	    case 0:
		line_cols[line_cols_size++] = 1.; 
		line_cols[line_cols_size++] = 0.;
		line_cols[line_cols_size++] = 0.; 
		line_cols[line_cols_size++] = 1.; 
		break;
	    case 1:
		line_cols[line_cols_size++] = 0.; 
		line_cols[line_cols_size++] = 1.;
		line_cols[line_cols_size++] = 0.; 
		line_cols[line_cols_size++] = 1.; 
		break;
		}
	    }
	// VAO 0 for lines, associated with vbo[0] and vbo[1]
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);	
	glBufferData(GL_ARRAY_BUFFER, line_verts_size*sizeof(GL_FLOAT), 
	    line_verts, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);	
	glBufferData(GL_ARRAY_BUFFER, line_cols_size*sizeof(GL_FLOAT), 
	    line_cols, GL_STATIC_DRAW);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vColor);
	break;
    case DrawTriangle:
	for (int k = 0; k < 3; k++) {
	    screen_to_ndc(pts[k].x, pts[k].y, &ndc_x, &ndc_y);
	    tri_verts[tri_verts_size++] = (GLfloat) ndc_x;
	    tri_verts[tri_verts_size++] = (GLfloat) ndc_y;
	    tri_verts[tri_verts_size++] = (GLfloat) 0.;
	    tri_verts[tri_verts_size++] = (GLfloat) 1.;
	    cout << "Screen: " << pts[k].x << "," << pts[k].y  << ":NDC: " 
		<< ndc_x<< "," << ndc_y<< endl << flush;

	    switch (k) {
	    case 0:
		tri_cols[tri_cols_size++] = rand()/(rand()+1); 
		tri_cols[tri_cols_size++] = rand()/(rand()+1);
		tri_cols[tri_cols_size++] = rand()/(rand()+1); 
		tri_cols[tri_cols_size++] = 1.; 
		break;
	    case 1:
		tri_cols[tri_cols_size++] = rand()/(rand()+1); 
		tri_cols[tri_cols_size++] = rand()/(rand()+1);
		tri_cols[tri_cols_size++] = rand()/(rand()+1); 
		tri_cols[tri_cols_size++] = 1.; 
		break;
	    case 2:
		tri_cols[tri_cols_size++] = rand()/(rand()+1); 
		tri_cols[tri_cols_size++] = rand()/(rand()+1);
		tri_cols[tri_cols_size++] = rand()/(rand()+1);
		tri_cols[tri_cols_size++] = 1.; 
		break;
		}
	    }
	// VAO 1 for triangles, associated with vbo[2] and vbo[3]
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);	
	glBufferData(GL_ARRAY_BUFFER, tri_verts_size*sizeof(GL_FLOAT), 
	    tri_verts, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	// colors
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, tri_cols_size*sizeof(GL_FLOAT), tri_cols, 
	    GL_STATIC_DRAW);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vColor);

	break;

    case DrawPolygon:


	break;
	}
    glutPostRedisplay();
    }
//======================================================================
GLuint GLWidget::initShader(const char* vs_file, const char* fs_file) {

    char *vs_str = NULL, *fs_str = NULL;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    //should test the textFileRead function. Doesn't return properly.
    vs_str = textFileRead(vs_file);
    fs_str = textFileRead(fs_file);

    const char *vv = vs_str;
    const char *ff = fs_str;

    glShaderSource(vs, 1, &vv, NULL);
    glShaderSource(fs, 1, &ff, NULL);

    free(vs_str); free(fs_str); 

    glCompileShader(vs);

    int IsCompiled;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &IsCompiled);
    cout << "Compiled VS:" << IsCompiled << endl << flush;
    if(!IsCompiled)
	{
	int maxLength;
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

	/* The maxLength includes the NULL character */
	char *vertexInfoLog = (char *)malloc(maxLength);

	glGetShaderInfoLog(fs, maxLength, &maxLength, vertexInfoLog);

	cout << vertexInfoLog << endl;
	/* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
	/* In this simple program, we'll just leave */
	free(vertexInfoLog);

	cout << "Vertex Shader Failure!" << endl;
	//		return -1;
	}
    glCompileShader(fs);
    IsCompiled = 0;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &IsCompiled);

    cout << "Compiled FS:" << IsCompiled << endl << flush;
    if(!IsCompiled)
	{
	int maxLength;
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

	/* The maxLength includes the NULL character */
	char *fragmentInfoLog = (char *)malloc(maxLength);

	glGetShaderInfoLog(fs, maxLength, &maxLength, fragmentInfoLog);

	cout << fragmentInfoLog << endl;
	// Handle the error in an appropriate way such as 
	// displaying a message or writing to a log file. */
	/* In this simple program, we'll just leave */
	free(fragmentInfoLog);
	cout << "Fragment Shader Failure!" << endl;
	return -1;
	}

    glEnable( GL_DEPTH_TEST );

    //	printShaderInfoLog(vs);
    //	printShaderInfoLog(fs);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);

    glBindAttribLocation(shader_program, 0, "in_Position");
    glBindAttribLocation(shader_program, 1, "in_Color");

    glLinkProgram(shader_program);

    glUseProgram(shader_program);

    // set up attribute locations, color and position
    vPosition = glGetAttribLocation( shader_program, "vPosition" );
    vColor    = glGetAttribLocation( shader_program, "vColor" );

    return shader_program;
    }

//======================================================================
void GLWidget::myTest() {

    }

