#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Protogen/Protogen_Face.hpp"
#include "Protogen/Protogen_Visor.hpp"
#include "Graphics/RenderManager.hpp"

class Application {

public:

	Application(int width, int height, const char* title);

	void start();
	void render(void);
	void update(double dt);
	

private:

	void init();
	void mainLoop();
	void swapBuffers();
	void processInput();

	static void glfwError(int id, const char* description)
	{
		std::cout << description << std::endl;
	}
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	int m_width;
	int m_height;

	const char* m_title;

	float m_time;

	GLFWwindow* m_window;
	Protogen_Face* m_protogenFace;
	Protogen_Visor* m_protogenVisor;

	RenderManager* m_RenderManager;

};