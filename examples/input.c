#include <stdio.h>
#include <yagl.h>

int main() {
    InitWindow("Input Example", 699, 699);
    Font font = LoadFont("VCR_OSD_MONO_1.001.ttf", 16);

    double cursor_x, cursor_y;
    int i = 0;
    int s = 0;
    while (!WindowClosed()) {
        GetCursorPos(&cursor_x, &cursor_y);
        if (KeyAction(KeySpace, KEY_PRESS)) s++;
        if (MouseAction(MouseButtonLeft, 1)) i++;
        if (MouseAction(MouseButtonRight, 1)) i--;
        if (KeyAction(KeyR, KEY_PRESS)) { i = 0; s = 0; }
        if (KeyAction(KeyC, KEY_PRESS)) printf("Cursor position: (X: %lf, Y: %lf)\n", cursor_x, cursor_y);
        else printf("Mouse button was pressed %d times\tSpace was pressed %d times\n", i, s);
        ClearScreen();
            DrawCircle((Vec2){cursor_x, cursor_y}, 100, WHITE);
            DrawText(font, 20, 600, 1, WHITE, "Cursor position: (X: %lf, Y: %lf)", cursor_x, cursor_y);
        SwapBuffer();
    }
    return 0;
}
