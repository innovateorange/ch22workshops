

default: 
	g++ -I include/ src/glad.c src/test.cpp -lX11 -lpthread -lXrandr -lXi -ldl -o test

window:
	g++ -I include/ src/glad.c src/helloWindow.cpp -lglfw3 -lX11 -lGL -lpthread -lXrandr -lXi -ldl -o window


triangle:
	g++ -I include/ src/glad.c src/triangle.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o triangle

rectangle:
	g++ -I include/ src/glad.c src/rectangle.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o rectangle

twoTriangle:
	g++ -I include/ src/glad.c src/twoTriangle.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o twoTriangle


doubleTriangle:
	g++ -I include/ src/glad.c src/doubleTriangle.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o dubTriangle

colorTriangle:
	g++ -I include/ src/glad.c src/colorTriangle.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o colorTriangle



clean:
	@rm -f window
	@rm -f test
	@rm -f triangle
	@rm -f rectangle
	@rm -f twoTriangle
	@rm -f dubTriangle
	@rm -f colorTriangle
