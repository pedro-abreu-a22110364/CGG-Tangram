////////////////////////////////////////////////////////////////////////////////
//
// Drawing two instances of a triangle in Clip Space.
// A "Hello 2D World" of Modern OpenGL.
//
// Copyright (c) 2013-24 by Carlos Martinho
//
// INTRODUCES:
// GL PIPELINE, mglShader.hpp, mglConventions.hpp
//
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>

#include "mgl/mgl.hpp"
#include "create-shape.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
public:
    void initCallback(GLFWwindow* win) override;
    void displayCallback(GLFWwindow* win, double elapsed) override;
    void windowCloseCallback(GLFWwindow* win) override;
    void windowSizeCallback(GLFWwindow* win, int width, int height) override;

private:
    const GLuint POSITION = 0, COLOR = 1;
    GLuint VaoId[7], VboId[2];
    std::unique_ptr<mgl::ShaderProgram> Shaders;
    GLint MatrixId;

    void createShaderProgram();
    void createBufferObjects();
    void destroyBufferObjects();
    void drawScene();
};

//////////////////////////////////////////////////////////////////////// SHADERs

void MyApp::createShaderProgram() {
    Shaders = std::make_unique<mgl::ShaderProgram>();
    Shaders->addShader(GL_VERTEX_SHADER, "clip-vs.glsl");
    Shaders->addShader(GL_FRAGMENT_SHADER, "clip-fs.glsl");

    Shaders->addAttribute(mgl::POSITION_ATTRIBUTE, POSITION);
    Shaders->addAttribute(mgl::COLOR_ATTRIBUTE, COLOR);
    Shaders->addUniform("Matrix");

    Shaders->create();

    MatrixId = Shaders->Uniforms["Matrix"].index;
}

//////////////////////////////////////////////////////////////////// VAOs & VBOs

Square square;
Parallelogram parallelogram;
Triangle triangle1;
Triangle triangle2;
Triangle triangle3;
Triangle triangle4;
Triangle triangle5;

void MyApp::createBufferObjects() {
    glGenVertexArrays(7, VaoId);

    // Square
    square.setColor(0.00f, 1.00f, 0.00f, 1.0f);
    square.createbuffershape(VaoId[0]);

    // Parallelogram
    parallelogram.setColor(1.00f, 0.50f, 0.00f, 1.0f);
    parallelogram.createbuffershape(VaoId[1]);

    // Triangle 1
    triangle1.setColor(1.00f, 0.00f, 0.00f, 1.0f);
    triangle1.createbuffershape(VaoId[2]);

    // Triangle 2
    triangle2.setColor(0.00f, 1.00f, 1.00f, 1.0f);
    triangle2.createbuffershape(VaoId[3]);

    // Triangle 3
    triangle3.setColor(0.80f, 0.00f, 0.80f, 1.0f);
    triangle3.createbuffershape(VaoId[4]);

    // Triangle 4
    triangle4.setColor(0.20f, 0.20f, 1.00f, 1.0f);
    triangle4.createbuffershape(VaoId[5]);

    // Triangle 5
    triangle5.setColor(0.40f, 0.00f, 0.40f, 1.0f);
    triangle5.createbuffershape(VaoId[6]);


}

void MyApp::destroyBufferObjects() {
    glBindVertexArray(VaoId[0]);
    glBindVertexArray(VaoId[1]);
    glBindVertexArray(VaoId[2]);
    glBindVertexArray(VaoId[3]);
    glBindVertexArray(VaoId[4]);
    glBindVertexArray(VaoId[5]);
    glBindVertexArray(VaoId[6]);
    glDisableVertexAttribArray(POSITION);
    glDisableVertexAttribArray(COLOR);
    glDeleteVertexArrays(3, VaoId);
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////// SCENE
const glm::vec3 axisz{ 0.0f, 0.0f, 1.0f };
const glm::mat4 I(1.0f);
const glm::mat4 ScaleMedium = glm::scale(glm::vec3(1.5f, 1.5f, 1.5f));
const glm::mat4 ScaleBig = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
const glm::mat4 Rotate315 = glm::rotate(glm::radians(-45.0f), axisz);
const glm::mat4 Rotate180 = glm::rotate(glm::radians(180.0f), axisz);
const glm::mat4 Rotate135 = glm::rotate(glm::radians(135.0f), axisz);
const glm::mat4 Rotate225 = glm::rotate(glm::radians(-135.0f), axisz);
const glm::mat4 TranslateSquare = glm::translate(glm::vec3(-0.870f, -0.3f, 0.0f));
const glm::mat4 TranslateParallelogram = glm::translate(glm::vec3(-0.875f, -0.55f, 0.0f));
const glm::mat4 TranslatefirstTriangle = glm::translate(glm::vec3(0.125f, 0.2f, 0.0f));
const glm::mat4 TranslatesecondTriangle = glm::translate(glm::vec3(-0.375f, -0.55f, 0.0f));
const glm::mat4 TranslatethirdTriangle = glm::translate(glm::vec3(-0.935f, 0.05f, 0.0f));
const glm::mat4 TranslatefourthTriangle = glm::translate(glm::vec3(1.185f, 0.05f, 0.0f));
const glm::mat4 TranslatefifthTriangle = glm::translate(glm::vec3(0.390f, 0.495f, 0.0f));


void MyApp::drawScene() {
    // Drawing directly in clip space

    glBindVertexArray(VaoId[0]);
    Shaders->bind();

    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(TranslateSquare));
    glDrawElements(GL_TRIANGLES, square.ShapeIndices.size(), GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(VaoId[1]);

    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(TranslateParallelogram));
    glDrawElements(GL_TRIANGLES, parallelogram.ShapeIndices.size(), GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(VaoId[2]);

    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(TranslatefirstTriangle * Rotate180));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(VaoId[3]);

    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(TranslatesecondTriangle));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(VaoId[4]);

    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(TranslatethirdTriangle * Rotate315 * ScaleBig));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(VaoId[5]);

    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(TranslatefourthTriangle * Rotate135 * ScaleBig));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(VaoId[6]);

    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(TranslatefifthTriangle * Rotate225 * ScaleMedium));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));

    Shaders->unbind();
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow* win) {
    createBufferObjects();
    createShaderProgram();
}

void MyApp::windowCloseCallback(GLFWwindow* win) { destroyBufferObjects(); }

void MyApp::windowSizeCallback(GLFWwindow* win, int winx, int winy) {
    glViewport(0, 0, winx, winy);
}

void MyApp::displayCallback(GLFWwindow* win, double elapsed) { drawScene(); }

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
    mgl::Engine& engine = mgl::Engine::getInstance();
    engine.setApp(new MyApp());
    engine.setOpenGL(4, 6);
    engine.setWindow(600, 600, "Tangram 2D", 0, 1);
    engine.init();
    engine.run();
    exit(EXIT_SUCCESS);
}

//////////////////////////////////////////////////////////////////////////// END