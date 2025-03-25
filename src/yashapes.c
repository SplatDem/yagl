#include <math.h>
#include <GL/gl.h>
#include "yagl.h"

// void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
//     glBegin(GL_LINES);
//         glColor4ub(color.r, color.g, color.b, color.a);
//         glVertex2f((float)startPosX, (float)startPosY);
//         glVertex2f((float)endPosX, (float)endPosY);
//     glEnd();
// }

void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color)
{ DrawLineV((Vec2){(float)startPosX, (float)startPosY}, (Vec2){(float)endPosX, (float)endPosY}, color); }

void DrawLineV(Vec2 startPos, Vec2 endPos, Color color) {
    glBegin(GL_LINES);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2f(startPos.x, startPos.y);
        glVertex2f(endPos.x, endPos.y);
    glEnd();
}

void DrawRect(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, Color color)
{ DrawRectV((Vec2){(float)topLeftX, (float)topLeftY}, (Vec2){(float)bottomRightX, (float)bottomRightY}, color); }

void DrawRectV(Vec2 topLeft, Vec2 bottomRight, Color color) {
    glBegin(GL_QUADS);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2f(topLeft.x, topLeft.y);
        glVertex2f(bottomRight.x, topLeft.y);
        glVertex2f(bottomRight.x, bottomRight.y);
        glVertex2f(topLeft.x, bottomRight.y);
    glEnd();
}

void DrawCircle(Vec2 center, float radius, Color color) {
    const int segments = 36;
    const float angleIncrement = 2.0f * M_PI / segments;

    glBegin(GL_TRIANGLE_FAN);
        glColor4f(color.r, color.g, color.b, color.a);
        glVertex2f(center.x, center.y);
        for (int i = 0; i <= segments; i++) {
            float angle = i * angleIncrement;
            float x = center.x + cosf(angle) * radius;
            float y = center.y + sinf(angle) * radius;
            glVertex2f(x, y);
        }
    glEnd();
}

void DrawTriangle(Vec2 a, Vec2 b, Vec2 c, Color color) {
    glBegin(GL_TRIANGLES);
        glColor4f(color.r, color.g, color.b, color.a);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
        glVertex2f(c.x, c.y);
    glEnd();
}
