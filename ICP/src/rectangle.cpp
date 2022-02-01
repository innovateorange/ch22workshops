#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


const char* vertexShaderSource="#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";


const char* fragmentShaderSource="#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";


int main(){
	////////////////////////////////
	//initialize and configure glfw
	/////////////////////////////////
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//////////////////////////////////////////////////////////////
	

	///////////////////////////////
	//Create glfw window
	//////////////////////////////
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//////////////////////////////
	
	//////////////////////////
	if(window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//
	//Check for error's creating window
	//

	//Set the current GL context to the window
	////////////////////////////////////////
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//Set frame buffer size callback function

	//Vertices array
	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f, // bottom left
	-0.5, 0.5, 0.0f     // top left
	};

	unsigned int indices[] = {
		0,1,3, //top right bottom right, top left
		1,2,3  //bottom right bottom left top left
	};

	//Check for GLAD loader
	if(!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	///////////////////////
	//Create a vertex shader
	///////////////////////
	
	int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	////////////////////////

	////////////////
	// Debug compilation
	////////////////
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VETEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/////////////////////////////
	
	///////////////////////
	// Create a fragment Shader
	///////////////////////
	int fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//////////////////////////////
	
	//////////////////////////
	// Debug Compilation
	// //////////////////////
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/////////////////////
	//Create a shader program
	/////////////////////
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	//Delete Shaders (no longer need since we have prog)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VBO; //Vertex Buffer Object
	unsigned int VAO; //Vertex Array Object
	unsigned int EBO; //Element Buffer Array

	glGenVertexArrays(1, &VAO); //Generates a vertex array
	glGenBuffers(1, &VBO);      //Generates buffer object names
	glGenBuffers(1, &EBO);      //Generates buffer object names

	glBindVertexArray(VAO); //Bind the vertex array

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind the buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copy data to GPU

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Bind the element buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //Copy data to GPU

	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); //Vertex attributes

	glEnableVertexAttribArray(0); //Disable
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind GL_ARRAY_BUFFER

	glBindVertexArray(0); //Unbind Vertex Array

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Set polygon mode

	while(!glfwWindowShouldClose(window)){

		processInput(window); //Wait for escape key to be pressed

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Set color
		glClear(GL_COLOR_BUFFER_BIT); //Clear buffer

		glUseProgram(shaderProgram); //Use this shader program
		glBindVertexArray(VAO); //Bind the vertex array
		glDrawElements(GL_TRIANGLES, 6 ,GL_UNSIGNED_INT, 0); //draw the elements
		



		glfwSwapBuffers(window); //swap buffers
		glfwPollEvents(); //poll key-press on frame
	
		//repeat
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}

