main: Main.cu Model/Grid.cpp Controler/Controler.cpp View/GridView.cpp View/Window.cpp Model/Step.cu
	nvcc -std=c++11 -D__CORRECT_ISO_CPP11_MATH_H_PROTO -rdc true Main.cu Model/Step.cu -lGL -lGLU -lglut -o main
