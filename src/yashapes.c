#include <GL/gl.h>
#include "yagl.h"

void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
    glBegin(GL_LINES);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2f((float)startPosX, (float)startPosY);
        glVertex2f((float)endPosX, (float)endPosY);
    glEnd();
}

void DrawLineV(Vec2 startPos, Vec2 endPos, Color color) {
    glBegin(GL_LINES);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2f(startPos.x, startPos.y);
        glVertex2f(endPos.x, endPos.y);
    glEnd();
}

void DrawRect(Vec2 topLeft, Vec2 bottomRight, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
        glVertex2f(topLeft.x, topLeft.y);
        glVertex2f(bottomRight.x, topLeft.y);
        glVertex2f(bottomRight.x, bottomRight.y);
        glVertex2f(topLeft.x, bottomRight.y);
    glEnd();
}

void DrawCircle(Vec2 zeroPoint, /* float radius, */ Color color) { // TODO: Complete
    glColor4ub(color.r, color.g, color.b, color.a);
    glBegin(GL_CIRCULAR_TANGENT_ARC_TO_NV);
        glVertex2f(zeroPoint.x, zeroPoint.y);
    glEnd();
} // Radius commented just for normal clang logs (Absolute coding)
