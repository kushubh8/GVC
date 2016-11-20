#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

void initWindow(void);

float angle = 0.0;
int left, right;
int leftTime, rightTime;
int thrust, thrustTime;
int joyThrust = 0, joyLeft = 0, joyRight = 0;
float x = 20, y = 20, xv, yv, v;
int shield = 0;
int lastTime;
int paused = 0;
int resuming = 1;
int originalWindow = 0, currentWindow;

void drawShip(float angle)
{
  float rad;

  glPushMatrix();
  glTranslatef(x, y, 0.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  if (thrust)
 {

  //-------------flame----------------
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-7.0,1.5);
    glVertex2f(-6.0,1.5);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-6.0,1.0);
    glVertex2f(-5.0,1.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-7.0,0.5);
    glVertex2f(-6.0,0.5);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-6.0,0.0);
    glVertex2f(-5.0,0.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-7.0,-0.5);
    glVertex2f(-6.0,-0.5);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-6.0,-1.0);
    glVertex2f(-5.0,-1.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-7.0,-1.5);
    glVertex2f(-6.0,-1.5);
	glEnd();

  }

//--------------------center fornt-----------------
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(3.0, 0.0);
  glVertex2f(-2.5, -2.5);
  glVertex2f(1.0, 0.0);
  glVertex2f(-2.5, 2.5);
  glVertex2f(3.0, 0.0);
  glEnd();



  //---------------------center------blue-----

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(-2.5, 2.5);
  glVertex2f(-3.0, 2.0);
  glVertex2f(-3.0, -2.0);
  glVertex2f(-2.5, -2.5);
  glVertex2f(1.0,0.0);
  glVertex2f(-2.5,2.5);
  glEnd();


  //-----end---skin--
     glColor3f(1.0, 1.0, 0.5);
	 glBegin(GL_POLYGON);
  glVertex2f(-3.0,2.0);
  glVertex2f(-3.0,-2.0);
  glVertex2f(-4.5,-3.5);
  glVertex2f(-5.5,-2.5);
  glVertex2f(-4.5,-1.5);
  glVertex2f(-4.5,1.5);
  glVertex2f(-5.5,2.5);
  glVertex2f(-4.5,3.5);
  glVertex2f(-3.0,2.0);
  glEnd();

  //----------- flaps ----green------
 glColor3f(0.0, 1.0, 0.0);
 glBegin(GL_POLYGON);
  glVertex2f(-1.5,2.0);
  glVertex2f(-0.8,2.6);
  glVertex2f(3.0,0.0);
  glVertex2f(-1.5,2.0);
  glEnd();

  //------------------flaps---green---
glColor3f(0.0, 1.0, 0.0);
glBegin(GL_POLYGON);
  glVertex2f(-1.5,-2.0);
  glVertex2f(-0.8,-2.6);
  glVertex2f(3.0,0.0);
  glVertex2f(-1.5,-2.0);
  glEnd();

//--------------front rectangle------black------
glColor3f(0.0, 0.0, 0.0);
glBegin(GL_POLYGON);
  glVertex2f(1.25,0.4);
  glVertex2f(1.75,0.4);
  glVertex2f(1.25,-0.4);
  glVertex2f(1.75,-0.4);
  glVertex2f(1.75,0.4);
  glEnd();

  //--------------------stars--------green-------
glColor3f(0.0, 1.0, 0.0);
glBegin(GL_POINTS);
  glVertex2f(1.5,0.0);
  glEnd();

  //-points-
if (shield)
{
    glColor3f(0.1, 0.1, 1.0);
    glBegin(GL_LINE_LOOP);
    for (rad=0.0; rad<30.0; rad += 1.0) {
      glVertex2f(3.2 * cos(2*rad/M_PI)+0.2, 3.0 * sin(2*rad/M_PI));
    }
    glEnd();
  }
  glPopMatrix();
}


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,0.0,0.0);
  drawShip(angle);
  glutSwapBuffers();
}

void idle(void)
{
  int time, delta;

  time = glutGet(GLUT_ELAPSED_TIME);
  if (resuming) {
    lastTime = time;
    resuming = 0;
  }
  if (left) {
    delta = time - leftTime;
    angle = angle + delta * 0.4;
    leftTime = time;
  }
  if (right) {
    delta = time - rightTime;
    angle = angle - delta * 0.4;
    rightTime = time;
  }
  if (thrust==1) {
    delta = time - thrustTime;
    v = delta * 0.00004;
    xv = xv + cos(angle*M_PI/180.0) * v;
    yv = yv + sin(angle*M_PI/180.0) * v;
    thrustTime = time;
  }
  if (thrust==2) {
    delta = time - thrustTime;
    v = -1*delta * 0.00008;
    xv = xv + cos(angle*M_PI/180.0) * v;
    yv = yv + sin(angle*M_PI/180.0) * v;
    thrustTime = time;
  }
  delta = time - lastTime;
  x = x + xv * delta;
  y = y + yv * delta;

  // goes off from one end of screen and shows up at opposite end
  x = x / 40.0;
  x = (x - floor(x))*40.0;
  y = y / 40.0;
  y = (y - floor(y))*40.0;
  lastTime = time;
  //advanceBullets(delta, time);
  glutPostWindowRedisplay(currentWindow);
}


void visible(int vis)
{
  if (vis == GLUT_VISIBLE) {
    if (!paused) {
      glutIdleFunc(idle);
    }
  } else {
    glutIdleFunc(NULL);
  }
}


/* ARGSUSED1 */
void key(unsigned char key, int px, int py)
{
  switch (key) {

 //------exit-----escape key-----
  case 27:
    exit(0);
    break;
//-------speed------w key--------
  case 'W':
  case 'w':
    thrust = 1;
    thrustTime = glutGet(GLUT_ELAPSED_TIME);
    break;
//------shield------s key-------
  case 'S':
  case 's':
    shield = 1;
    break;
//------initial position----z key----
  case 'z':
  case 'Z':
    x = 20;
    y = 20;
    xv = 0;
    yv = 0;
    angle=0.0;
    break;
//--------pause----space key-------
  case 32:
    paused = !paused;
    if (paused) {
      glutIdleFunc(NULL);
    } else {
      glutIdleFunc(idle);
      resuming = 1;
    }
    break;
  }
}


/* ARGSUSED1 */
void keyup(unsigned char key, int x, int y)
{
  switch (key) {
  case 'W':
  case 'w':
    thrust = 0;
    break;
  case 'S':
  case 's':
    shield = 0;
    break;
  }
}


/* ARGSUSED2 */
void special(int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_UP:
    thrust = 1;
    thrustTime = glutGet(GLUT_ELAPSED_TIME);
    break;
  /*  case GLUT_KEY_DOWN:
    thrust = 2;
    thrustTime = glutGet(GLUT_ELAPSED_TIME);
    break;
  */
  case GLUT_KEY_LEFT:
    left = 1;
    leftTime = glutGet(GLUT_ELAPSED_TIME);
    break;
  case GLUT_KEY_RIGHT:
    right = 1;
    rightTime = glutGet(GLUT_ELAPSED_TIME);
    break;
  }
}


/* ARGSUSED2 */
void specialup(int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_UP:
    thrust = 0;
    break;
  case GLUT_KEY_LEFT:
    left = 0;
    break;
  case GLUT_KEY_RIGHT:
    right = 0;
    break;
  }
}

void initWindow(void)
{
  glutIgnoreKeyRepeat(1);
  glutDisplayFunc(display);
  glutVisibilityFunc(visible);
  glutKeyboardFunc(key);
  glutKeyboardUpFunc(keyup);
  glutSpecialFunc(special);
  glutSpecialUpFunc(specialup);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 40, 0, 40, 0, 40);
  glMatrixMode(GL_MODELVIEW);
  glPointSize(3.0);
  currentWindow = glutGetWindow();
  }


  int  main(int argc, char **argv)
  {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  if (argc > 1 && !strcmp(argv[1], "-fullscreen")) {
    glutGameModeString("640x480:16@60");
    glutEnterGameMode();
  } else {
    originalWindow = glutCreateWindow("SPACE SHIP");
  }

  initWindow();

  glutMainLoop();
  return 0;
  }
