#include <GL/gl.h>
#include "yagl.h"

Camera InitCamera(int viewportWidth, int viewportHeight) {
    Camera cam = {
        .x = viewportWidth / 2.0f,
        .y = viewportHeight / 2.0f,
        .zoom = 1.0f,
        .rotation = 0.0f,
        .viewportWidth = viewportWidth,
        .viewportHeight = viewportHeight
    };
    return cam;
}

void BeginCamera(Camera *cam) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, cam->viewportWidth, cam->viewportHeight, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(cam->x, cam->y, 0.0f);
    glRotatef(cam->rotation, 0.0f, 0.0f, 1.0f);
    glScalef(cam->zoom, cam->zoom, 1.0f);
    glTranslatef(-cam->x, -cam->y, 0.0f);
}

void EndCamera() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void ScreenToWorld(float screenX, float screenY, float *worldX, float *worldY) { *worldX = screenX; *worldY = screenY; }
