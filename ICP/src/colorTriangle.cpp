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

const char* fragmentShaderYellowSource="#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main(){\n"
	"	FragColor = vec4(0.75f, 0.75f, 0.0f, 1.0f);\n"
	"}\n\0";

int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	
	if(window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	-0.25f, 0.5f, 0.0f
	};
	float vertices2[] = {
	0.0f, -0.5f, 0.0f,
	0.25f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f	
	};

	if(!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VETEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	
	int fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	int yellowFragmentShader;
	yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowFragmentShader, 1, &fragmentShaderYellowSource, NULL);
       	glCompileShader(yellowFragmentShader);

	glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(yellowFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::Yellow::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(fragmentShader);


	unsigned int yellowShader = glCreateProgram();
	glAttachShader(yellowShader, vertexShader);
	glAttachShader(yellowShader, yellowFragmentShader);
	glLinkProgram(yellowShader);
	glDeleteShader(vertexShader);
	glDeleteShader(yellowFragmentShader);

	unsigned int VBOi, VBOii;
	unsigned int VAOi, VAOii;

	glGenVertexArrays(1, &VAOi);
	glGenVertexArrays(1, &VAOii);
	glGenBuffers(1, &VBOi);
	glGenBuffers(1, &VBOii);
	
	glBindVertexArray(VAOi);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBOi);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindVertexArray(VAOii);

	glBindBuffer(GL_ARRAY_BUFFER, VBOii);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while(!glfwWindowShouldClose(window)){

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAOi);
		
		glDrawArrays(GL_TRIANGLES, 0 ,3);

		glUseProgram(yellowShader);
		glBindVertexArray(VAOii);
		glDrawArrays(GL_TRIANGLES, 0, 3);




		glfwSwapBuffers(window);
		glfwPollEvents();
	
	
	}

	glDeleteVertexArrays(1, &VAOi);
	glDeleteVertexArrays(1, &VAOii);

	glDeleteBuffers(1, &VBOi);
	glDeleteBuffers(1, &VBOii);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(yellowShader);
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

