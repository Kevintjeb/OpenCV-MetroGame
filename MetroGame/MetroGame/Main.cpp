#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
using namespace std; //Lets not do this

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutMotionFunc(changeColor);
	//opengl init

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 0;
}