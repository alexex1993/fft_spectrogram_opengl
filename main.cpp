#include <GL/glut.h>
#include "display.h"
#include <iostream>


int main(int argc, char **argv)
{
	if(argc < 3)
	{
		std::cout << "Invalid input format. Usage:" << std::endl << "./wav_spectr <name_of_wav-file> <fft_size>" << std::endl << 
		"Example: ./wav_spectr file.wav 10 " << std::endl;
		exit(0);
	}  
	name = argv[1];
	globalLogN = atoi(argv[2]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(880, 500); 
	glutInitWindowPosition(200, 200); 
	glutCreateWindow(argv[1]);
	glClearColor(1.0, 1.0, 1.0, 1.0); ;
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL, 0); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); 
	glutDisplayFunc(display); 
	glutMainLoop(); 
	exit(0);
}
