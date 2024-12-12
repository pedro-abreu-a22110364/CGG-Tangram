////////////////////////////////////////////////////////////////////////////////
//
//  Loading meshes from external files
//
// Copyright (c) 2023-24 by Carlos Martinho
//
// INTRODUCES:
// MODEL DATA, ASSIMP, mglMesh.hpp
//
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <glm/gtx/matrix_decompose.hpp>
#include "mgl/mgl.hpp"
#include "SceneGraph.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
 public:
  void initCallback(GLFWwindow *win) override;
  void displayCallback(GLFWwindow *win, double elapsed) override;
  void windowSizeCallback(GLFWwindow *win, int width, int height) override;
  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
  void scrollCallback(GLFWwindow* window, double x, double y) override;
  void cursorCallback(GLFWwindow* window, double xposition, double yposition) override;
  void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override;
  void rotateCamera(float angle_x, float angle_y);

 private:
  mgl::Camera *Camera = nullptr;
  mgl::Mesh* Mesh[3];
  SceneGraph scene;
  float animationProgress = 1.0f;
  double mouse_x_pos;
  double mouse_y_pos;
  bool rotate;
  bool left;
  bool right;

  void createMeshes();
  void createShaderPrograms();
  void createCamera();
  void drawScene();
  void createMatrix();
};

///////////////////////////////////////////////////////////////////////// MESHES

void MyApp::createMeshes() {
  std::string mesh_dir = "models/";
  // std::string mesh_file = "cube-v.obj";
  // std::string mesh_file = "cube-vn-flat.obj";
  // std::string mesh_file = "cube-vn-smooth.obj";
  // std::string mesh_file = "cube-vt.obj";
  // std::string mesh_file = "cube-vt2.obj";
  // std::string mesh_file = "torus-vtn-flat.obj";
  // std::string mesh_file = "torus-vtn-smooth.obj";
  // std::string mesh_file = "suzanne-vtn-flat.obj";
  // std::string mesh_file = "suzanne-vtn-smooth.obj";
  // std::string mesh_file = "teapot-vn-flat.obj";
  // std::string mesh_file = "teapot-vn-smooth.obj";
  // std::string mesh_file = "bunny-vn-flat.obj";
  // std::string mesh_file = "bunny-vn-smooth.obj";
  // std::string mesh_file = "monkey-torus-vtn-flat.obj";
  std::string mesh_file1 = "triangulo.obj";
  std::string mesh_file2 = "quadrado.obj";
  std::string mesh_file3 = "paralelogramo.obj";

  //create triangle mesh
  std::string mesh_fullname = mesh_dir + mesh_file1;
  Mesh[0] = new mgl::Mesh();
  Mesh[0]->joinIdenticalVertices();
  Mesh[0]->create(mesh_fullname);

  //create Square mesh
  mesh_fullname = mesh_dir + mesh_file2;
  Mesh[1] = new mgl::Mesh();
  Mesh[1]->joinIdenticalVertices();
  Mesh[1]->create(mesh_fullname);

  //create Parallelogram mesh
  mesh_fullname = mesh_dir + mesh_file3;
  Mesh[2] = new mgl::Mesh();
  Mesh[2]->joinIdenticalVertices();
  Mesh[2]->create(mesh_fullname);
  
  SceneNode* tangram = new SceneNode();
  SceneNode* firsttriangle= new SceneNode(Mesh[0]);
  SceneNode* secondtriangle = new SceneNode(Mesh[0]);
  SceneNode* thirdtriangle = new SceneNode(Mesh[0]);
  SceneNode* fourthtriangle = new SceneNode(Mesh[0]);
  SceneNode* fifthtriangle = new SceneNode(Mesh[0]);
  SceneNode* square = new SceneNode(Mesh[1]);
  SceneNode* parallelogram = new SceneNode(Mesh[2]);
  scene.addNode(tangram);
  scene.nodes[0]->addChild(firsttriangle);
  scene.nodes[0]->children[0]->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
  scene.nodes[0]->addChild(secondtriangle);
  scene.nodes[0]->children[1]->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
  scene.nodes[0]->addChild(thirdtriangle);
  scene.nodes[0]->children[2]->setColor(glm::vec3(1.0f, 0.0f, 1.0f));
  scene.nodes[0]->addChild(fourthtriangle);
  scene.nodes[0]->children[3]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
  scene.nodes[0]->addChild(fifthtriangle);
  scene.nodes[0]->children[4]->setColor(glm::vec3(0.0f, 1.0f, 1.0f));
  scene.nodes[0]->addChild(square);
  scene.nodes[0]->children[5]->setColor(glm::vec3(1.0f, 1.0f, 0.0f));
  scene.nodes[0]->addChild(parallelogram);
  scene.nodes[0]->children[6]->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

///////////////////////////////////////////////////////////////////////// SHADER

void MyApp::createShaderPrograms() {
    scene.createshader();
}

///////////////////////////////////////////////////////////////////////// CAMERA

// Eye(0,0,7) Center(0,0,0) Up(0,1,0)
glm::mat4 ViewMatrix1 =
    glm::lookAt(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));

// Eye(0,7,1) Center(0,0,0) Up(0,1,0)
glm::mat4 ViewMatrix2 =
    glm::lookAt(glm::vec3(0.0f, 7.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));

// Orthographic LeftRight(-2,2) BottomTop(-2,2) NearFar(1,10)
glm::mat4 ProjectionMatrix1 =
    glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);

// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
glm::mat4 ProjectionMatrix2 =
    glm::perspective(glm::radians(30.0f), 640.0f / 480.0f, 1.0f, 10.0f);

void MyApp::createCamera() {
  Camera = new mgl::Camera(UBO_BP);
  Camera->setViewMatrix(ViewMatrix2);
  Camera->setProjectionMatrix(ProjectionMatrix2);
}

/////////////////////////////////////////////////////////////////////////// DRAW

void MyApp::createMatrix() {
    scene.nodes[0]->children[0]->rotateend(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    scene.nodes[0]->children[0]->rotateend(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    scene.nodes[0]->children[0]->translateend(glm::vec3(0.52f, -1.0f, 0.01f));
    scene.nodes[0]->children[1]->rotateend(135.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    scene.nodes[0]->children[1]->rotateend(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    scene.nodes[0]->children[1]->translateend(glm::vec3(-0.19f, -1.0f, -0.69f));
    scene.nodes[0]->children[2]->rotateend(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    scene.nodes[0]->children[2]->rotateend(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    scene.nodes[0]->children[2]->translateend(glm::vec3(0.17f, -1.0f, 0.73f));
    scene.nodes[0]->children[3]->rotateend(225.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    scene.nodes[0]->children[3]->rotateend(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    scene.nodes[0]->children[3]->translateend(glm::vec3(-0.55f, -1.0f, 0.02f));
    scene.nodes[0]->children[4]->rotateend(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    scene.nodes[0]->children[4]->rotateend(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    scene.nodes[0]->children[4]->translateend(glm::vec3(0.53f, -1.0f, -0.33f));
    scene.nodes[0]->children[5]->rotateend(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    scene.nodes[0]->children[5]->rotateend(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    scene.nodes[0]->children[5]->translateend(glm::vec3(0.16f, -1.0f, -0.34f));
    scene.nodes[0]->children[6]->rotateend(135.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    scene.nodes[0]->children[6]->rotateend(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    scene.nodes[0]->children[6]->translateend(glm::vec3(0.72f, -1.0f, 0.21f));
    scene.nodes[0]->children[0]->scale(glm::vec3(0.25f, 0.25f, 0.2f));
    scene.nodes[0]->children[1]->scale(glm::vec3(0.25f, 0.25f, 0.2f));
    scene.nodes[0]->children[2]->scale(glm::vec3(0.5f, 0.5f, 0.2f));
    scene.nodes[0]->children[3]->scale(glm::vec3(0.5f, 0.5f, 0.2f));
    scene.nodes[0]->children[4]->scale(glm::vec3(glm::sqrt(2) * 0.25f, glm::sqrt(2) * 0.25f, 0.2f));
    scene.nodes[0]->children[5]->scale(glm::vec3(0.25f, 0.25f, 1.0f));
    scene.nodes[0]->children[6]->scale(glm::vec3(0.25f, 0.25f, 1.0f));
    scene.nodes[0]->children[0]->translatestart(glm::vec3(-0.23f, -1.5f, 0.0f));
    scene.nodes[0]->children[1]->translatestart(glm::vec3(0.27f, -1.5f, 0.0f));
    scene.nodes[0]->children[2]->translatestart(glm::vec3(0.52f, -1.04f, 0.0f));
    scene.nodes[0]->children[3]->translatestart(glm::vec3(0.53f, -1.04f, 0.0f));
    scene.nodes[0]->children[4]->translatestart(glm::vec3(1.05f, -1.75f, 0.0f));
    scene.nodes[0]->children[5]->translatestart(glm::vec3(-0.75f, -1.0f, 0.0f));
    scene.nodes[0]->children[6]->translatestart(glm::vec3(-0.5f, -1.5f, 0.0f));
    scene.nodes[0]->children[0]->rotatestart(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    scene.nodes[0]->children[2]->rotatestart(-45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    scene.nodes[0]->children[3]->rotatestart(135.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    scene.nodes[0]->children[4]->rotatestart(225.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void MyApp::drawScene() {
    if (left) {
        animationProgress = animationProgress + 0.01f;
    }
    else if(right) {
        
        animationProgress = animationProgress - 0.01f;
    }
    if (animationProgress > 1) {
        animationProgress = 1;
    }
    if (animationProgress < 0) {
        animationProgress = 0;
    }
    scene.draw(animationProgress);
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
    createMeshes();
    createShaderPrograms();  // after mesh;
    createCamera();
    createMatrix();
}

void MyApp::displayCallback(GLFWwindow* win, double elapsed) {
    drawScene(); 
}

void MyApp::windowSizeCallback(GLFWwindow* win, int width, int height) {
    glViewport(0, 0, width, height);

    // Calculate the new aspect ratio
    float newAspectRatio = static_cast<float>(width) / static_cast<float>(height);

    if (Camera != nullptr) {
        if (Camera->getProjectionMatrix() == ProjectionMatrix1) {
            ProjectionMatrix1 = glm::ortho(
                -2.0f * newAspectRatio, 2.0f * newAspectRatio,
                -2.0f, 2.0f,
                1.0f, 10.0f
            );
            Camera->setProjectionMatrix(ProjectionMatrix1);
        }
        else if (Camera->getProjectionMatrix() == ProjectionMatrix2) {
            ProjectionMatrix2 = glm::perspective(
                glm::radians(30.0f),
                newAspectRatio,
                1.0f, 10.0f
            );
            Camera->setProjectionMatrix(ProjectionMatrix2);
        }
    }
}


void MyApp::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    static bool activeCamera = true;
    static bool activeProjection = true;

    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        Camera->setViewMatrix(activeCamera ? ViewMatrix1 : ViewMatrix2);
        activeCamera = !activeCamera;
    }
    else if(key == GLFW_KEY_P && action == GLFW_PRESS) {
        Camera->setProjectionMatrix(activeProjection ? ProjectionMatrix1 : ProjectionMatrix2);
        activeProjection = !activeProjection;
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        if (!right) {
            left = true;
        }
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        if (!left) {
            right = true;
        }
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
        left = false;
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
        right = false;
    }
}

void MyApp::scrollCallback(GLFWwindow* window, double x, double y) {
    const float Speed = 0.4f;
    glm::mat4 Matrix = Camera->getViewMatrix();
    glm::vec3 Pos = glm::vec3(glm::inverse(Matrix)[3]);
    glm::vec3 UpVector = glm::vec3(glm::inverse(Matrix)[1]);
    glm::vec3 Direction = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - Pos);
    Pos += static_cast<float>(y) * Speed * Direction;
    if (Matrix == ViewMatrix1) {
        Camera->setViewMatrix(glm::lookAt(Pos, glm::vec3(0.0f, 0.0f, 0.0f), UpVector));
        ViewMatrix1 = Camera->getViewMatrix();
    }
    else {
        Camera->setViewMatrix(glm::lookAt(Pos, glm::vec3(0.0f, 0.0f, 0.0f), UpVector));
        ViewMatrix2 = Camera->getViewMatrix();
    }
}

void MyApp::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &mouse_x_pos, &mouse_y_pos);
        rotate = true;
    }else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        glfwGetCursorPos(window, &mouse_x_pos, &mouse_y_pos);
        rotate = false;
    }
}

void MyApp::rotateCamera(float angle_x, float angle_y) {
    glm::mat4 Matrix = Camera->getViewMatrix();
    glm::vec3 Pos = glm::vec3(glm::inverse(Matrix)[3]);
    glm::vec3 UpVector = glm::vec3(glm::inverse(Matrix)[1]);

    glm::quat q_x = glm::angleAxis(angle_x, UpVector);
    glm::vec3 Direction = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - Pos);
    glm::vec3 cam_right = glm::normalize(glm::cross(Direction, UpVector));
    glm::quat q_y = glm::angleAxis(angle_y, cam_right);
    glm::quat q = q_x * q_y;

    Camera->setViewMatrix(glm::lookAt(Pos * q, glm::vec3(0.0f, 0.0f, 0.0f), UpVector * q));
    if (Matrix == ViewMatrix1) {
        ViewMatrix1 = Camera->getViewMatrix();
    }else if (Matrix == ViewMatrix2) {
        Camera->setViewMatrix(glm::lookAt(Pos * q, glm::vec3(0.0f, 0.0f, 0.0f), UpVector * q));
        ViewMatrix2 = Camera->getViewMatrix();
    }
}

void MyApp::cursorCallback(GLFWwindow* window, double xposition, double yposition) {
    const float sensitivity = 0.05f;
    if (rotate) {
        // Calculate the mouse delta (how much the mouse moved since the last frame)
        double delta_x = xposition - mouse_x_pos;
        double delta_y = yposition - mouse_y_pos;
        mouse_x_pos = xposition;
        mouse_y_pos = yposition;

        // Apply sensitivity to the deltas
        float angle_x = static_cast<float>(-delta_x * sensitivity);
        float angle_y = static_cast<float>(-delta_y * sensitivity);

        rotateCamera(angle_x,angle_y);
    }
}

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char *argv[]) {
    mgl::Engine &engine = mgl::Engine::getInstance();
    engine.setApp(new MyApp());
    engine.setOpenGL(4, 6);
    engine.setWindow(800, 600, "Mesh Loader", 0, 1);
    engine.init();
    engine.run();
    exit(EXIT_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////