#include "GridView.cpp"
#define D_ANGLE 0.1
#define VITESSE 10.0
namespace Window {
	int width = 800;
	int height = 600;
	int fps = 24;
	bool running = false;

	double camera_x = 0.0, camera_y = 0.0, camera_z = 5.0;


	static void checkError() {
		int err = glGetError();
		if(err != 0) {
	    printf("Error %s\n", gluErrorString(err));
	  }
	}

	static void display() {
		glClearColor(0.0, 0.0, 0.0, 0);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	  glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(camera_x, camera_y, camera_z, camera_x, camera_y, 0, 0.0, 1.0, 0.0);

		GridView::draw();

		checkError();
		glutSwapBuffers();
	}

	static void animate(int id) {
		if(running) {
				GridView::grid.nextStep();
		}
		glutPostRedisplay();
		glutTimerFunc(1000/fps, &animate, 0);
	}

	static void reshape(int w, int h) {
		if(w>3./2.*h)
	    w=3./2.*h;
	  else
	    h=2./3.*w;

	  glViewport(0,0,w,h);
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  glFrustum(-1.8, 1.8 ,-1.2 ,1.2, 2.0, 5000.0);
	}

}
