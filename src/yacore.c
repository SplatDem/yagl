#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <GLFW/glfw3.h>
#include "yagl.h"

GLFWvidmode screen;

static GLFWwindow *window;
static int targetFPS = 60;

void InitWindow(const char *title, int width, int height) {
    printl(NOTE, "Yagl version: " YAGL_VERSION);
    printl(NOTE, "WINDOW:");
    printl(NONE, "Title:  %s", title);
    printl(NONE, "Width:  %d", width);
    printl(NONE, "Height: %d", height);

    yaGLinit(title, width, height);
    printl(NOTE, "GPU Ready");
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void yaGLinit(const char *title, int width, int height) {
    if (!glfwInit()) printl(ERROR, "Failed to initialize OpenGL");

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) { glfwTerminate(); printl(ERROR, "Failed to create OpenGL window"); }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int  WindowClosed() { return glfwWindowShouldClose(window); }
void ClearScreen() { glClearColor(0.0f, 0.0f, 0.0f, 1.0f); glClear(GL_COLOR_BUFFER_BIT); }
void SwapBuffer()  { glfwSwapBuffers(window); glfwPollEvents(); }

int  KeyAction(Key key, int state) { return glfwGetKey(window, key) == state; }
int  MouseAction(MouseButton button, int state) { return glfwGetMouseButton(window, button) == state; }
void GetCursorPos(double *posX, double *posY) { glfwGetCursorPos(window, posX, posY); }

void SetFPS(int fps) {
    if (fps > 0) {
        targetFPS = fps;
        printl(NOTE, "Target FPS set to: %d", targetFPS);
    } else {
        printl(ERROR, "Invalid FPS value: %d", fps);
    }
}

void LimitFPS() {
    static clock_t lastTime = 0;
    clock_t currentTime = clock();

    double frameTime = 1.0 / targetFPS;
    double elapsedTime = (double)(currentTime - lastTime) / CLOCKS_PER_SEC;

    if (elapsedTime < frameTime) {
        double sleepTime = (frameTime - elapsedTime) * 1000;
        struct timespec ts = { 0, (long)(sleepTime * 1000000) };
        nanosleep(&ts, NULL);
    }

    lastTime = currentTime;
}

// Print Log
void printl(const char *type, const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stdout, "%s", type);
    if (strcmp(type, NONE)) fprintf(stdout, ": ");
    else fprintf(stdout, "\t");
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
    va_end(args);
    if (!strcmp(type, ERROR)) exit(1);
}
