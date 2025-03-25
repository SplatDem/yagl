#include "yagl.h"

int main() {
    InitWindow("Yet Another Camera", 699, 699);
    Camera camera = InitCamera(699, 699);

    Texture th = LoadTexture("touhou_is_shit.jpg");

    SetFPS(60);

    while (!WindowClosed()) {
        if (KeyAction(KeyRight, KEY_PRESS)) camera.x += 2.0f;
        if (KeyAction(KeyLeft, KEY_PRESS)) camera.x -= 2.0f;
        if (KeyAction(KeyUp, KEY_PRESS)) camera.y -= 2.0f;
        if (KeyAction(KeyDown, KEY_PRESS)) camera.y += 2.0f;
        if (KeyAction(KeyZ, KEY_PRESS)) camera.zoom *= 1.01f;
        if (KeyAction(KeyX, KEY_PRESS)) camera.zoom *= 0.99f;
        if (KeyAction(KeyR, KEY_PRESS)) camera.rotation += 1.0f;

        ClearScreen();

        BeginCamera(&camera);
        {
            DrawRectV((Vec2){300, 250}, (Vec2){350, 300}, RED);

            DrawRectV((Vec2){100, 100}, (Vec2){150, 150}, (Color){0, 0, 255, 255});
            DrawTexture(th, 100, 100, 100, 100);
        }
        EndCamera();

        SwapBuffer();
        LimitFPS();
    }

    return 0;
}
