////////////////////////////////////////////////////////////////////////////////
//
// Starting OpenGL
//
// Copyright (c) 2013-24 by Carlos Martinho
//
// INTRODUCES:
// GLFW, GLEW, mglApp.hpp, mglError.hpp
//
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <iostream>
#include <sstream>

#include "mgl/mgl.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
public:
  void initCallback(GLFWwindow *win) override;
  void displayCallback(GLFWwindow *win, double elapsed) override;
  void windowCloseCallback(GLFWwindow *win) override;
  void windowSizeCallback(GLFWwindow *win, int width, int height) override;
  void keyCallback(GLFWwindow *win, int key, int scancode, int action,
                   int mods) override;
  void cursorCallback(GLFWwindow *win, double xpos, double ypos) override;
  void mouseButtonCallback(GLFWwindow *win, int button, int action,
                           int mods) override;
  void scrollCallback(GLFWwindow *win, double xoffset, double yoffset) override;
  void joystickCallback(int jid, int event) override;

private:
  void updateFPS(GLFWwindow *win, double ellapsed_sec);
};

/////////////////////////////////////////////////////////////////////////// INIT

void MyApp::initCallback(GLFWwindow *win) {
  std::cout << "Initializing..." << std::endl;
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::windowCloseCallback(GLFWwindow *win) {
  std::cout << "closing..." << std::endl;
}

void MyApp::windowSizeCallback(GLFWwindow *win, int width, int height) {
  std::cout << "size: " << width << " " << height << std::endl;
  glViewport(0, 0, width, height);
}

void MyApp::keyCallback(GLFWwindow *win, int key, int scancode, int action,
                        int mods) {
  std::cout << "key: " << key << " " << scancode << " " << action << " " << mods
            << std::endl;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, GLFW_TRUE);
    windowCloseCallback(win);
  }
}

void MyApp::cursorCallback(GLFWwindow *win, double xpos, double ypos) {
  std::cout << "mouse: " << xpos << " " << ypos << std::endl;
}

void MyApp::mouseButtonCallback(GLFWwindow *win, int button, int action,
                                int mods) {
  std::cout << "button: " << button << " " << action << " " << mods
            << std::endl;
}

void MyApp::scrollCallback(GLFWwindow *win, double xoffset, double yoffset) {
  std::cout << "scroll: " << xoffset << " " << yoffset << std::endl;
}

void MyApp::joystickCallback(int jid, int event) {
  std::cout << "joystick: " << jid << " " << event << std::endl;
}

//////////////////////////////////////////////////////////////////////////// RUN

void MyApp::displayCallback(GLFWwindow *win, double elapsed_sec) {
  updateFPS(win, elapsed_sec);
}

void MyApp::updateFPS(GLFWwindow *win, double elapsed_sec) {
  static unsigned int acc_frames = 0;
  static double acc_time = 0.0;
  const double UPDATE_TIME = 1.0;

  ++acc_frames;
  acc_time += elapsed_sec;
  if (acc_time > UPDATE_TIME) {
    std::ostringstream oss;
    double fps = acc_frames / acc_time;
    oss << std::fixed << std::setw(5) << std::setprecision(1) << fps << " FPS";
    glfwSetWindowTitle(win, oss.str().c_str());

    acc_frames = 0;
    acc_time = 0.0;
  }
}

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char *argv[]) {
  int gl_major = 4, gl_minor = 6;
  int is_fullscreen = 0;
  int is_vsync = 1;

  mgl::Engine &engine = mgl::Engine::getInstance();
  engine.setApp(new MyApp());
  engine.setOpenGL(gl_major, gl_minor);
  engine.setWindow(800, 600, "MGL Window", is_fullscreen, is_vsync);
  engine.init();
  engine.run();
  return (EXIT_SUCCESS);
}

//////////////////////////////////////////////////////////////////////////// END
