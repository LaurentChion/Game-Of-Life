namespace GridView {;
  Grid grid(SIZE);

  void drawGrid() {
    glColor3f(0.2,0.2,0.2);
		glBegin(GL_LINES);

    float incr = 1.0;
    float x = -1;

			for(int i=0; i< SIZE-1; i++) {
				x += incr;
				glVertex3f(x, 0, 0);
				glVertex3f(x,  SIZE, 0);
				glVertex3f(0, x, 0);
				glVertex3f( SIZE, x, 0);
			}
		glEnd();
  }

  void drawSquares() {
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(0.5,0.5,0);
    for(int i=0; i< SIZE; i++) {
			for(int j=0; j< SIZE; j++) {
        if(grid.getTab(i,j) != 0 ) {
          glPushMatrix();
          glTranslatef(i,j,0);
          glutSolidCube(1.0);
          glPopMatrix();
        }
      }
    }
    glPopMatrix();
  }

  void draw() {
    drawGrid();
    drawSquares();
  }
}
