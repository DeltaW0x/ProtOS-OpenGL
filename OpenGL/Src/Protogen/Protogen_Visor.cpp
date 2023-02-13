#include "Protogen_Visor.hpp"

Protogen_Visor::Protogen_Visor()
{


    visorShader = new Shader("C:\\Users\\lucac\\source\\repos\\OpenGL\\OpenGL\\Src\\Shaders\\Protogen\\VisorShader.vs", "C:\\Users\\lucac\\source\\repos\\OpenGL\\OpenGL\\Src\\Shaders\\Protogen\\VisorShader.fs");


    proj = glm::ortho(-4.0f, 4.0f, -1.0f, 1.0f, 0.0001f, 400.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(6, 6, 6));
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



}

Protogen_Visor::~Protogen_Visor()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

}

void Protogen_Visor::Render()
{
    visorShader->use();
    int projLoc = glGetUniformLocation(visorShader->ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    int viewLoc = glGetUniformLocation(visorShader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int modelLoc = glGetUniformLocation(visorShader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 1872 / 3);
}
