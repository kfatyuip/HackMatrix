#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include "camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "app.h"
#include "world.h"

class Controls {
  bool cursorDisabled = true;
  bool appFocused = false;
  double lastToggleFocusTime = 0;
  double lastToggleAppTime = 0;
  double lastClickTime = 0;
  bool firstMouse = true;
  float lastX;
  float lastY;
  X11App* app = NULL;

  void handleControls(GLFWwindow* window, Camera* camera);
  void handleEscape(GLFWwindow* window);
  void handleToggleFocus(GLFWwindow* window);
  void handleToggleApp(GLFWwindow* window);

  void handleKeys(GLFWwindow* window, Camera* camera);
  void handleClicks(GLFWwindow* window, World* world);
public:
  void poll(GLFWwindow* window, Camera* camera, World* world);
  void mouseCallback (GLFWwindow* window, double xpos, double ypos);
  void registerApp(X11App* app);
};
#endif