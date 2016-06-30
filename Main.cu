#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <time.h>

#define SIZE 500
// importer le modèle et la vue PUIS le controleur

#include "Model/Grid.cpp"
#include "View/Window.cpp"
#include "Controler/Controler.cpp"

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(Window::width, Window::height);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Jeu de la vie");
	glutDisplayFunc(&Window::display);

	glutKeyboardFunc(&Controler::key);
	glutMouseFunc(&Controler::mouse);

	glutTimerFunc(1000/Window::fps, &Window::animate, 0);
	glutReshapeFunc(&Window::reshape);
	glutMainLoop();
	return 0;
}
