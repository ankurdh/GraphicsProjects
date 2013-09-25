//--------------------------------------------------
// MainWindow.h -- declarations for the main window
//--------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>
#include <GL/glui.h>


class MainWindow
{
  private:

	GLUI *glui_r, *glui_b;
	GLUI_Panel *draw_panel, *message_panel;
	GLUI_RadioGroup *radio_g;

	// handle to object
	static MainWindow *current;

	//handle to the id of GLUT main window
	int mainWin;

  public:

    MainWindow();
    ~MainWindow();
    void show( int argc, char **argv );

	static MainWindow *getCurrent(void) {
		return current;
	}

	int draw_mode, rb_pressed, btn_pressed;
							// accessor functions
	GLUI_Panel *getMessagePanel() {
		return message_panel;
	}
	GLUI_Panel *getDrawPanel() {
		return draw_panel;
	}
	GLUI_RadioGroup *getRadioGroup() {
		return radio_g;
	}

	int getDrawMode() {
		return draw_mode;
	}

	void refreshWindow();

	void setWindowTitle(const char * title){
	    glutSetWindowTitle(title);
	    }
    
	//handle to show what is the current draw mode. 
	std::string currentDrawMode;

};

#endif // MAINWINDOW_H
