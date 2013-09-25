//---------------------------------------------
// 	2D Drawing Application -- main function 
// 	--version using vertex and fragment shaders
//---------------------------------------------

#include <iostream>

using namespace std;

#include "glDefs.h"
#include "glutDefs.h"
#include "glWidget.h"

#include "textfile.h"

int main(int argc, char *argv[]) {

								// initialize glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	MainWindow mainwin;			// set up main window

								// specify glut call backs
	glutDisplayFunc(display);
	glutMouseFunc(mouseEvent);
	glutReshapeFunc(reshape);
	glutKeyboardFunc( keyboard );
	glutIdleFunc(idle);

							// check to see opengl 2.0 is available using glew
	glewInit();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const char* version = (const char*)glGetString(GL_VERSION); 
    cout << "OpenGL Version: " << string(version) << endl;

    version = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION); 
    cout << "GLSL Version: " << string(version) << endl;

	GLWidget *glw = new GLWidget;

							// initialize shaders
	GLuint shader_program = glw->initShader("draw.vert", "draw.frag");
	
							// activate shader program
	//glUseProgram(shader_program);

    glutMainLoop();			// enter the event loop

    return 0;
}
void display(void) {

    //clear black
    glClearColor(0, 0, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						// draw the line segment

	GLWidget *glw = GLWidget::getCurrent();

						// draw calls in GL Widget class
	GLWidget::getCurrent()->draw();

						// swap buffers to update the view
    glutSwapBuffers();
}

void reshape(int width, int height) {

						// maps window to device coordinates
	glViewport(0, 0, width, height);
						// resizing the window will need to be propagated
	GLWidget::getCurrent()->setDimensions(width, height);

}

void idle(void) {

 //   glutPostRedisplay();
    GLWidget::getCurrent()->rotateCube();

    glutPostRedisplay();
}

void mouseEvent(int button, int state, int x, int y) {
								// all interaction via this function
	GLWidget::getCurrent()->handleMouseEvent(button, state, x, y);
}

void keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
    	case 033: // Escape Key
    	case 'q': 
		case 'Q':
        	exit( EXIT_SUCCESS );
        break;
		case 'i' : 
			GLWidget::getCurrent()->myTest();
		break;
    }
}


void control_cb(int control) {
							// switching primitive types
	GLWidget::getCurrent()->handleUI(control);
}
