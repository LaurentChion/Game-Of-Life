namespace Controler {

  // action a effectuer lorsque que l'on appuie sur une touche
  void key(unsigned char key, int x, int y) {

    double newX = Window::camera_x, newY = Window::camera_y, newZ = Window::camera_z;

    switch(key) {
      case 'z':
	      newY = Window::camera_y + 1;
	      break;
	    case 's':
	      newY = Window::camera_y - 1;
	      break;
	    case 'q':
	      newX = Window::camera_x -1;
	      break;
	    case 'd':
	      newX = Window::camera_x + 1;
	      break;
      case ' ':
        Window::running = !(Window::running);
  			break;
  		default:
  			break;
  	}

    if (key != ' ') {
      Window::camera_x = newX;
  		Window::camera_y = newY;
  		Window::camera_z = newZ;
    }
  }

  void mouse(int button, int state, int x, int y) {
  	switch (button) {
  		case GLUT_LEFT_BUTTON :
  			break;
  		case GLUT_RIGHT_BUTTON :
  			break;
      //GLUT_WHEEL_UP
      case 4 :
        Window::camera_z *= 1.1;
        break;
      // GLUT_WHEEL_DOWN
      case 3 :
        Window:: camera_z /= 1.1;
        break;
      default:;
  	}
  }

}
