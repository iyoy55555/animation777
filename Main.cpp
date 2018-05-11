#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
//#define M_PI 3.14159265359
//#define V 2500
//#define v 50

#include "shader.h"
#include "Model.h"
#include "Camera.h"
const GLint WIDTH = 800, HEIGHT = 600;


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn Opengl", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window) {
		std::cout << "Create Window fail" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (GLEW_OK != glewInit()) {
		std::cout << "Fail to init GLEW" << std::endl;

		return -1;
	}
	
	glViewport(0, 0, screenWidth, screenHeight);


	glEnable(GL_DEPTH_TEST);
	/*
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	*/
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	Shader Ourshader("shader.vs","shader.fs");
	string path= "../Nanosuit/nanosuit.obj";
	Model ourModel(path);
	/*float R = 0.7, r = 0.15;
	float x = 0, y = 0, z = 0;
	float tx, ty, tz, sx, sy, sz;
	float VerticesX[V], VerticesY[V], VerticesZ[V];
	float vertices[12 * (v + 1)*v];
	float normalx[V], normaly[V], normalz[V];
	for (int i = 0; i < v; ++i) {
		for (int j = 0; j<v; ++j)
		{
			VerticesX[v*i + j] = (R + r*cos(j * 2 * M_PI / v))*cos(i * 2 * M_PI / v);
			VerticesY[v*i + j] = (R + r*cos(j * 2 * M_PI / v))*sin(i * 2 * M_PI / v);
			VerticesZ[v*i + j] = r*sin(j * 2 * M_PI / v);
			tx = -sin(i * 2 * M_PI / v);
			ty = cos(i * 2 * M_PI / v);
			tz = 0;
			sx = cos(i * 2 * M_PI / v)*(-sin(j * 2 * M_PI / v));
			sy = sin(i * 2 * M_PI / v)*(-sin(j * 2 * M_PI / v));
			sz = cos(j * 2 * M_PI / v);
			normalx[v*i + j] = ty*sz - tz*sy;
			normaly[v*i + j] = tz*sx - tx*sz;
			normalz[v*i + j] = tx*sy - ty*sx;
		}
	}
	for (int i = 0; i<v; ++i)
		for (int j = 0; j < v + 1; ++j) {
			if (i == (v - 2)) {
				if (j == v + 1) {
					vertices[i * 12 * (v + 1) + j * 12] = VerticesX[0];
					vertices[i * 12 * (v + 1) + j * 12 + 1] = VerticesY[0];
					vertices[i * 12 * (v + 1) + j * 12 + 2] = VerticesZ[0];
					vertices[i * 12 * (v + 1) + j * 12 + 3] = normalx[0];
					vertices[i * 12 * (v + 1) + j * 12 + 4] = normaly[0];
					vertices[i * 12 * (v + 1) + j * 12 + 5] = normalz[0];
					vertices[i * 12 * (v + 1) + j * 12 + 6] = VerticesX[0];
					vertices[i * 12 * (v + 1) + j * 12 + 7] = VerticesY[0];
					vertices[i * 12 * (v + 1) + j * 12 + 8] = VerticesZ[0];

					vertices[i * 12 * (v + 1) + j * 12 + 9] = normalx[0];
					vertices[i * 12 * (v + 1) + j * 12 + 10] = normaly[0];
					vertices[i * 12 * (v + 1) + j * 12 + 11] = normalz[0];
				}
				else {
					vertices[i * 12 * (v + 1) + j * 12] = VerticesX[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 1] = VerticesY[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 2] = VerticesZ[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 3] = normalx[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 4] = normaly[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 5] = normalz[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 6] = VerticesX[j];
					vertices[i * 12 * (v + 1) + j * 12 + 7] = VerticesY[j];
					vertices[i * 12 * (v + 1) + j * 12 + 8] = VerticesZ[j];

					vertices[i * 12 * (v + 1) + j * 12 + 9] = normalx[j];
					vertices[i * 12 * (v + 1) + j * 12 + 10] = normaly[j];
					vertices[i * 12 * (v + 1) + j * 12 + 11] = normalz[j];
				}
			}
			else {
				if (j == v + 1) {
					vertices[i * 12 * (v + 1) + j * 12] = VerticesX[v*i];
					vertices[i * 12 * (v + 1) + j * 12 + 1] = VerticesY[v*i];
					vertices[i * 12 * (v + 1) + j * 12 + 2] = VerticesZ[v*i];
					vertices[i * 12 * (v + 1) + j * 12 + 3] = normalx[v*i];
					vertices[i * 12 * (v + 1) + j * 12 + 4] = normaly[v*i];
					vertices[i * 12 * (v + 1) + j * 12 + 5] = normalz[v*i];
					vertices[i * 12 * (v + 1) + j * 12 + 6] = VerticesX[v*(i + 1)];
					vertices[i * 12 * (v + 1) + j * 12 + 7] = VerticesY[v*(i + 1)];
					vertices[i * 12 * (v + 1) + j * 12 + 8] = VerticesZ[v*(i + 1)];
					vertices[i * 12 * (v + 1) + j * 12 + 9] = normalx[v*(i + 1)];
					vertices[i * 12 * (v + 1) + j * 12 + 10] = normaly[v*(i + 1)];
					vertices[i * 12 * (v + 1) + j * 12 + 11] = normalz[v*(i + 1)];
				}
				else {
					vertices[i * 12 * (v + 1) + j * 12] = VerticesX[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 1] = VerticesY[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 2] = VerticesZ[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 3] = normalx[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 4] = normaly[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 5] = normalz[v*i + j];
					vertices[i * 12 * (v + 1) + j * 12 + 6] = VerticesX[v*(i + 1) + j];
					vertices[i * 12 * (v + 1) + j * 12 + 7] = VerticesY[v*(i + 1) + j];
					vertices[i * 12 * (v + 1) + j * 12 + 8] = VerticesZ[v*(i + 1) + j];
					vertices[i * 12 * (v + 1) + j * 12 + 9] = normalx[v*(i + 1) + j];
					vertices[i * 12 * (v + 1) + j * 12 + 10] = normaly[v*(i + 1) + j];
					vertices[i * 12 * (v + 1) + j * 12 + 11] = normalz[v*(i + 1) + j];
				}
			}
		}


	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (float*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	*/
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Ourshader.use();


		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		view = camera.GetViewMatrix();
		Ourshader.setMat4("projection", projection);
		Ourshader.setMat4("view", view);
		Ourshader.setMat4("model", model);
		ourModel.Draw(Ourshader);
	

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
