main: Main.cu Model/Grid.cpp Controler/Controler.cpp View/GridView.cpp View/Window.cpp Model/Step.cu
	nvcc -std=c++11 Main.cu Model/Step.cu -lGL -lGLU -lglut -lm -rdc true -o main
