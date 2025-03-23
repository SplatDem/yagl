> [!WARNING]
> Library in the early stage of development.

# YAGL (Yet Another Graphic Library)

Yagl is a simple and easy to use library for creating OpenGL based applications.

## Possibilities
 - Draw basic shapes
 - Render textures (Almost all existing formats)
 - Collision shapes
 - **SOON**: ttf/otf text rendering
 - **SOON**: Audio
 - **SOON**: Shaders support

## Getting started with basic example
```C
#include <yagl.h>

int main() {
    InitWindow("Yagl Basic Example", 699, 699);

    while (!WindowClosed()) {
        ClearScreen(); // Start drawing
            DrawRect((Vec2){ 100., 100.}, (Vec2){ 150., 150.}, WHITE);
        SwapBuffer(); // End drawing
    }
    return 0;
}
```
Compile:
```shell
clang basic_example.c -o program -lyagl
# or other compiler
```
### Output
![basic example](assets/yagl_basic_example.png)

-----------------------------------------------
-----------------------------------------------
# --------------------Extra--------------------
-----------------------------------------------

## Raycasting example
![raycasting](assets/raycasting_example.png)

## Social links
 - Telegram: https://t.me/imperativeprogru (ONLY FOR RUSSIAN SPEACKERS)
