
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <playsoundapi.h>
#include<string.h>
using namespace std;

/*small 3D sphere movment*/
int gx = 0, gy = 0, gz = 0;  

/*used to save last polygon number*/
int qn = 0; 

/*Normal vertices*/
GLfloat n[] = { 1.0, 1.0, 1.0 }; 

/*3b object sphere vertices*/
GLfloat obj[] = { 0.3f , 10.0f, 80.0f }; 

/*angle for moving the scene*/
float anglex = 0.0f; float angley = 0.0f; float moveeyesz = 1.0f;

//-------------------------------------------------------------------------------

void initLightM(void) {

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1 , 1, 1, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

//-------------------------------------------------------------------------------

struct polygon {
	int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5;
	float r, g, b;
	int state; //to determined which point
	int total; //keeps track of total number of Ploygon to draw

}; polygon q[100];

//-------------------------------------------------------------------------------

void addpolygonP() {

	q[0].state++; 
	if (q[0].state > 5) { q[0].state = 1; } //if state larger than 5 point then resume to 1 
	int st = q[0].state; //save state of first drawing 
	//set all values equal to current Sphere location 
	if (st == 1) { q[0].total++; qn = q[0].total; }
	if (st == 1) { q[qn].x1 = gx; q[qn].y1 = gy; q[qn].z1 = gz; }
	if (st == 1 || st == 2) { q[qn].x2 = gx; q[qn].y2 = gy; q[qn].z2 = gz; }
	if (st == 1 || st == 2 || st == 3) { q[qn].x3 = gx; q[qn].y3 = gy; q[qn].z3 = gz; }
	if (st == 1 || st == 2 || st == 3 || st == 4) { q[qn].x4 = gx; q[qn].y4 = gy; q[qn].z4 = gz; }
	if (st == 1 || st == 2 || st == 3 || st == 4 || st == 5) { q[qn].x5 = gx; q[qn].y5 = gy; q[qn].z5 = gz; }

}

//-------------------------------------------------------------------------------

void drawpolygon() {

	int i;
	for (i = 0; i < q[0].total + 1; i++) //move through array to draw the Polygon using total value
	{
		glColor3f(q[i].r, q[i].g, q[i].b);
		glBegin(GL_POLYGON);

		glNormal3fv(n);
		glVertex3f(q[i].x1, q[i].y1, q[i].z1);

		glNormal3fv(n);
		glVertex3f(q[i].x2, q[i].y2, q[i].z2);

		glNormal3fv(n);
		glVertex3f(q[i].x3, q[i].y3, q[i].z3);

		glNormal3fv(n);
		glVertex3f(q[i].x4, q[i].y4, q[i].z4);

		glNormal3fv(n);
		glVertex3f(q[i].x5, q[i].y5, q[i].z5);

		glEnd();

	}

}

//-------------------------------------------------------------------------------

void SolidSphere() {

	glPushMatrix(); 
	glColor3f(1 , 0.7 ,0.5);
	glTranslatef(gx, gy, gz);
	glPushMatrix();
	glutSolidSphere(obj[0], obj[1], obj[2]);
	glPopMatrix();
	glPopMatrix();
}

//-------------------------------------------------------------------------------

void drawgrid() {
	/*This method draws the lines*/
	int i; 
	for (i = 0; i < 40; i++)
	{
		glPushMatrix();

		if (i < 20) { glTranslatef(0, 0, i); }
		if (i >= 20) { glTranslatef(i - 20, 0, 0); glRotatef(-90, 0, 1, 0); }
	
		glBegin(GL_LINES);
		glColor3i(0, 0, 0); glLineWidth(2);
		glNormal3fv(n);glVertex3f(0, -0.1, 0); 
		glNormal3fv(n);glVertex3f(19, -0.1, 0);
		glEnd();

		glPopMatrix();

	}

}

//-------------------------------------------------------------------------------

void init() {
	
	
	glClearColor(0.4, 0, 1, 1);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0f, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();
	
}

//-------------------------------------------------------------------------------

void myinit() {
	glClearColor(0.4, 0, 1, 1);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(5, 5, 5, 5);

	glPopMatrix();
	glLoadIdentity();
	initLightM();
}

//-------------------------------------------------------------------------------

void display() {
	init();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutPostRedisplay();
	glLoadIdentity();

	// Set the camera + movment
	gluLookAt(0.0f, 0.0f, 0.5,
			  0.0f, 0.0f, 0.0f,
		      0.0f, 1.0f, 0.0f);
	glTranslatef(anglex, angley, moveeyesz); 

	/*rotate the small sphere*/
	glTranslatef(-13, 0, -45); 
	glRotatef(40, 1, 1, 0); 



	//draw polygon
	drawpolygon();
	//draw grid
	drawgrid();
	//draw small sphere
	SolidSphere(); 

	glutSwapBuffers();

}

//-------------------------------------------------------------------------------

void myspecialkey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:gz -= 1;break;	     //move Sphere in z forward
	case GLUT_KEY_DOWN:gz += 1; break;	 //move Sphere in z backward
	case GLUT_KEY_LEFT:gx -= 1; break;   //move Sphere left x
	case GLUT_KEY_RIGHT:gx += 1; break;  //move  Sphere right x 
		}

	glutPostRedisplay();

}


//-------------------------------------------------------------------------------

void mykeyboard(unsigned char key, int x, int y) {

	switch (key) {
	case'q':gy += 1;  break; //move Sphere UP 
	case'z':gy -= 1;  break; //move Sphere DOWN


	case 'd':anglex -= 5.0f; break;  //move the cam in x axis right
	case 'a':anglex += 5.0f; break;  //move the cam in x axis left
	case 'w':angley -= 5.0f; break;  //move the cam up
	case 's':angley += 5.0f; break;  //move the cam down

		/*play sound when clicking space keyboard ASCII 32 + set colors*/
	case 32: addpolygonP(); PlaySound(TEXT("press-button.wav"), NULL, SND_ASYNC);
	case 'v':  q[qn].r = 0.9, q[qn].g = 1.0, q[qn].b = 0.7; break;	//white
	case 'g':  q[qn].r = 0.2, q[qn].g = 1,   q[qn].b = 0;   break;  //green
	case 'b':  q[qn].r = 0,   q[qn].g = 1,   q[qn].b = 1;   break;  //blue 
	case 'y':  q[qn].r = 1,   q[qn].g = 1,   q[qn].b = 0;   break;	//Yellow
	case 'r':  q[qn].r = 1.0, q[qn].g = 0,   q[qn].b = 0.0; break;	//Red 

	case 'L':  glEnable(GL_LIGHT0); ; break;
	case 'l':  glDisable(GL_LIGHT0); ; break;

	case 'p':  moveeyesz -= 5.0f;   break;
	case 'o':  moveeyesz += 5.0f; break;

	case 'x': glutDisplayFunc(display); break;

	}
	
	glutPostRedisplay();
	

}

//-------------------------------------------------------------------------------

void interface() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1, 1, 1);
	glRasterPos3f(-0.2, 0.5, 0);
	char msg0[] = "Welcome to the";
	for (int i = 0; i < strlen(msg0); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg0[i]);


	glColor3f(1, 1, 1);
	glRasterPos3f(-0.3, 0.3, 0);
	char msg1[] = "DRAWING CANVAS";
	for (int i = 0; i < strlen(msg1); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

	glColor3f(1, 1, 1);
	glRasterPos3f(-0.6, 0.1, 0);
	char msg2[] = "Where you can get your own space, start drawing now!";
	for (int i = 0; i < strlen(msg2); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg2[i]);


	  //CLICK keyboard button 'x' to start Drawing Program


	glColor3f(1, 1, 1);
	glRasterPos3f(-0.3, -0.8, 0);
	char msg3[] = "**Press (x) to start the game**";
	for (int i = 0; i < strlen(msg3); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg3[i]);


	glutSwapBuffers();

	
}

//-------------------------------------------------------------------------------

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Drawing Canvas");
	myinit();
	glutDisplayFunc(interface);
	glutSpecialFunc(myspecialkey);
	glutKeyboardFunc(mykeyboard);
	glutMainLoop();
	return 0;
}


