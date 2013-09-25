//------------------------------------------------------
// MainWindow.cpp -- implementation of MainWindow class
//------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mainWindow.h"

#include "glutDefs.h"


MainWindow *MainWindow::current = NULL;

// ------------ MainWindow definitions ------------ //

/**
Ankur : Adding the show function.
*/

void MainWindow::show(int argc, char ** argv){
    
    //not implemented yet.
    
    }


MainWindow::MainWindow()
{
							// create windows
	glutInitWindowSize(700, 550);
	glutInitWindowPosition(200, 200);

	mainWin = glutCreateWindow("Select One of Lines/Triangles mode to begin drawing");

	glutSetWindow(mainWin);
							// glui widdgets
							// controls on the right, messages on the bottom

	glui_r = GLUI_Master.create_glui_subwindow(mainWin, GLUI_SUBWINDOW_RIGHT );
	glui_b = GLUI_Master.create_glui_subwindow(mainWin, GLUI_SUBWINDOW_BOTTOM );


	draw_panel = new GLUI_Panel(glui_r, "Draw Functions");

							// message area for application feedback
	message_panel = new GLUI_Panel(glui_b, "Message Area");
	currentDrawMode = "Welcome to glDraw!";
	glui_b->add_statictext_to_panel(message_panel, "Welcome to GLDraw!");
	int mode;
							// create the draw functions in a radio box

	GLUI_Button *btn;

	btn = new GLUI_Button(draw_panel, "Lines", 0, control_cb);
	btn = new GLUI_Button(draw_panel, "Triangle", 1, control_cb);
	btn = new GLUI_Button(draw_panel, "Polygon", 2, control_cb);
	btn = new GLUI_Button(draw_panel, "ClearScreen", 3, control_cb);
//	radio_g = new GLUI_RadioGroup(draw_panel, &rb_pressed, draw_mode, control_cb );

//		GLUI_RadioButton *rb;

//		rb = new GLUI_RadioButton( radio_g, "Lines" );
//		rb = new GLUI_RadioButton( radio_g, "Polyline" );
//		rb = new GLUI_RadioButton( radio_g, "Continuous Line");
//		rb = new GLUI_RadioButton( radio_g, "Redraw");
//		rb = new GLUI_RadioButton( radio_g, "Clear Screen");


							// quit button
	GLUI_Button *button = new GLUI_Button(glui_r, "Quit", 0,(GLUI_Update_CB)exit);

							// set parent windows for an integrated glut-gui app
	glui_r->set_main_gfx_window(mainWin);
	glui_b->set_main_gfx_window(mainWin);

	current = this;
}

MainWindow::~MainWindow()
{
//	delete glwidget, label, win;
}

void MainWindow::refreshWindow(){
    glutSetWindowTitle(currentDrawMode.c_str());
    }