#include "Application.hpp"
#include <iostream>

Application::Application(int width, int height,const char* title ){
        m_time = 0;
        m_width = width;
        m_height= height;
        m_title = title;
        m_window = nullptr;

        m_RenderManager = &m_RenderManager->instance();

        glfwSetErrorCallback(&glfwError);
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

        if (m_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);

        glViewport(0, 0, m_width, m_height);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void Application::mainLoop()
{
    while (!glfwWindowShouldClose(m_window)) {

        processInput();
        glfwPollEvents();
        render();
    }
    glfwTerminate();
    return;
}

void Application::start()
{
    init();
    mainLoop();
}

void Application::init()
{
    m_protogenFace = new Protogen_Face();
    m_protogenVisor = new Protogen_Visor();
    m_RenderManager->AddToRenderList(m_protogenFace);
    m_RenderManager->AddToRenderList(m_protogenVisor);
}

void Application::render()
{
    glClearColor(0.117, 0.117, 0.117, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_RenderManager->RenderAll();

    swapBuffers();
}

void Application::update(double dt)
{

}


void Application::swapBuffers()
{
    glfwSwapBuffers(m_window);
}



void Application::processInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}
