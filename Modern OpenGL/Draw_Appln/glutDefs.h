#ifndef GLUT_DEFS_H

#define GLUT_DEFS_H 1

                    // glut prototypes
void display();
void reshape (int, int);
void idle();
void mouseEvent(int button, int state, int x, int y);
void mouseMotionEvent(int x, int y);
void control_cb (int control);
void keyboard (unsigned char, int, int);

#endif
