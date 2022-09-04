#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include ".\classes\KochLine.h"
#include ".\classes\Shader.h"

#define PI 3.1415926538

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void closeWindow(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int power(int a, int b) {
  int ans = 1;
  while(b > 0) {
    int lb = (b & 1);

    if(lb) {
      ans *= a;
    }

    a *= a;

    b = b >> 1;
  }
  return ans;
}

void nextGen(int& gen, vector<KochLine>& v, GLFWwindow* window, float angle) {
  if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && gen < 6) {
    vector<KochLine> nextGen;
    int p = power(4, gen);
    for (int j = 0; j < v.size(); j++) {
      if(j < p) {
        v[j].generate(nextGen, angle);
      } else {
        v[j].generate(nextGen, -angle);
      }
    }
    v = nextGen;
    gen++;
  }
}

int main() {
  int gen = 0, type = -1;
  while(type != 1 && type != 2) {
    cout << "Enter which type of koch snowflake you want\n";
    cout << "[1]Koch's Snowflake\n";
    cout << "[2]Anti-Koch's Snowflake\n";
    cin >> type;
  }
  // koch curve stuff
  Vertex v1{-0.6f, -0.6f};
  Vertex v2{0.6f, -0.6f};
  Vertex v3{0.0f, 0.6f};
  KochLine e2{v1, v2};
  KochLine e1{v1, v3};
  KochLine e3{v2, v3};
  vector<KochLine> v;
  v.push_back(e1);
  v.push_back(e2);
  v.push_back(e3);

  float angle = PI / 3.0f;
  if(type == 2) {
    angle *= -1;
  }


  float* vertecies = (float*)malloc(v.size() * 6 * sizeof(float));
  int p = 0;
  for(int i = 0; i < v.size() * 6; i += 6) {
    vertecies[i] = v[p].p1.x;
    vertecies[i + 1] = v[p].p1.y;
    vertecies[i + 2] = 0.0f;

    vertecies[i + 3] = v[p].p2.x;
    vertecies[i + 4] = v[p].p2.y;
    vertecies[i + 5] = 0.0f;
    p++;
  }

  // openGL stuff
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "Cobweb_Diagram", NULL, NULL);

  if (window == NULL) {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD" << endl;
    return -1;
  }

  Shader ourShader("./shaders/my_vertex.vs", "./shaders/my_fragment.fs");


  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, v.size() * 6 * sizeof(float), vertecies, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    closeWindow(window);
    nextGen(gen, v, window, angle);

    float* vertecies = (float*)malloc(v.size() * 6 * sizeof(float));
    int p = 0;
    for (int i = 0; i < v.size() * 6; i += 6) {
      vertecies[i] = v[p].p1.x;
      vertecies[i + 1] = v[p].p1.y;
      vertecies[i + 2] = 0.0f;

      vertecies[i + 3] = v[p].p2.x;
      vertecies[i + 4] = v[p].p2.y;
      vertecies[i + 5] = 0.0f;
      p++;
    }

    int k = v.size();
    glBufferData(GL_ARRAY_BUFFER, k * 6 * sizeof(float), vertecies, GL_DYNAMIC_DRAW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    ourShader.use();
    glDrawArrays(GL_LINES, 0, v.size() * 2);
    glBindVertexArray(0);

    free(vertecies);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}