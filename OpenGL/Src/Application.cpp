#include "Application.hpp"
#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


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

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();


        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("BlendShapes");
        ImGui::Checkbox("Thooty Mouth", &m_protogenFace->thootyShape);
        ImGui::End();
    
        render();

    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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
    ImGui::Render();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_RenderManager->RenderAll();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
