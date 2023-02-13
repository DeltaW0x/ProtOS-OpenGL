#include "Protogen_Face.hpp"
#include <imgui/imgui.h>

Protogen_Face::Protogen_Face()
{


    protoShader = new Shader("C:\\Users\\lucac\\source\\repos\\OpenGL\\OpenGL\\Src\\Shaders\\Protogen\\ProtoShader.vs", "C:\\Users\\lucac\\source\\repos\\OpenGL\\OpenGL\\Src\\Shaders\\Protogen\\ProtoShader.fs");

 
    proj = glm::ortho(-4.0f, 4.0f, -1.0f, 1.0f, 0.0001f, 400.0f);

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.0, 0.2, 0.0f));

    model = glm::scale(model, glm::vec3(6, 6, 6));
    glGenVertexArrays(1, &VAO);

    glGenBuffers(2, V_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, V_VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Base), Base, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, V_VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MouthType_Toothy), MouthType_Toothy, GL_STATIC_DRAW);



    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, V_VBO[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, V_VBO[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    

   

   

}

Protogen_Face::~Protogen_Face()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, V_VBO);

}

void Protogen_Face::Render()
{
    

    protoShader->use();

    if (thootyShape) {
        int blendLoc = glGetUniformLocation(protoShader->ID, "thoothy_w");
        glUniform1f(blendLoc, 1.0f);
    }
    else {
        int blendLoc = glGetUniformLocation(protoShader->ID, "thoothy_w");
        glUniform1f(blendLoc, 0.0f);
    }

    int projLoc = glGetUniformLocation(protoShader->ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    int viewLoc = glGetUniformLocation(protoShader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int modelLoc = glGetUniformLocation(protoShader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO); 
    glDrawArrays(GL_TRIANGLES, 0, 11124/3);
}
