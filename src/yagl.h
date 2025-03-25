#ifndef YAPI_H
#define YAPI_H

#define YAGL_VERSION "0.3.0" // Add camera support

#define ERROR   "\x1b[31mERROR\x1b[0m"
#define WARNING "\x1b[33mWARNING\x1b[0m"
#define NOTE    "\x1b[32mNOTE\x1b[0m"
#define NONE    "\x1b[42m        \x1b[0m"

#if (defined(__STDC__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
    #include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool) && !defined(YA_BOOL_TYPE)
    typedef enum bool { false = 0, true = !false } bool;
#endif

#define KEY_PRESS 1
#define KEY_RELEASE 2

// Colors TODO: Add more colors
#define /* World looks */ WHITE (Color){255, 255, 255, 255}
#define /* World looks */ RED (Color){255, 0, 0, 255}

// RGB + Alpha
typedef struct { float r, g, b, a; } Color;

typedef struct { float x, y; } Vec2;
typedef struct { float x, y, z; } Vec3;

typedef struct { float left, right, bottom, top; } Hitbox;
typedef struct { float x, y, radius; } CircleHitbox;

typedef struct {
    float x, y, width, height;
    Hitbox hitbox;
} Object;

// Image data in RAM
typedef struct Image {
    void *data;
    int width;
    int height;
    int mipmaps;
    int format;
} Image;

// Texture data in VRAM
typedef struct {
    unsigned int id;
    int width;
    int height;
    int mipmaps; // 1 by default
    int format;
} Texture;

typedef struct { // Stolen from stb_truetype.h
   unsigned short x0,y0,x1,y1;
   float xoff, yoff, xadvance;
} Bakedchar;

// Font
typedef struct {
    unsigned int textureID;
    Bakedchar cdata[96];
    float fontSize;
} Font;

// Camera 2D
typedef struct {
    float x, y;
    float zoom;
    float rotation;
    int viewportWidth;
    int viewportHeight;
} Camera;

// Keyboard keys
typedef enum {
    KeyNULL         = 0,     // No key pressed
    KeyApostrophe   = 39,    // '
    KeyComma        = 44,    // ,
    KeyMinus        = 45,    // -
    KeyDot          = 46,    // .
    KeySlash        = 47,    // /

    KeyZero  = 48, KeyOne   = 49,
    KeyTwo   = 50, KeyThree = 51,
    KetFour  = 52, KeyFive  = 53,
    KeySix   = 54, KeySeven = 55,
    KeyEight = 56, KeyNine  = 57,
    KeySemicolon    = 59,    // ;
    KeyEqual        = 61,    // =

    KeyA = 65, KetB = 66,
    KeyC = 67, KeyD = 68,
    KeyE = 69, KetF = 70,
    KetG = 71, KeyH = 72,
    KeyI = 73, KeyJ = 74,
    KeyK = 75, KeyL = 76,
    KeyM = 77, KeyN = 78,
    KeyO = 79, KeyP = 80,
    KeyQ = 81, KeyR = 82,
    KeyS = 83, KeyT = 84,
    KeyU = 85, KeyV = 86,
    KeyW = 87, KeyX = 88,
    KeyY = 89, KeyZ = 90,

    KeyLeftBracket  = 91,    // [
    KeyBackSlash    = 92,    // '\'
    KeyRightBracket = 93,    // ]
    KeyGrave        = 94,    // `

    KeySpace       = 32,  KeyEscape   = 256,
    KeyEnter       = 257, KeyTab      = 258,
    KeyBackspace   = 259, KeyInsert   = 260,
    KeyDelete      = 261, KeyRight    = 262,
    KeyLeft        = 263, KeyDown     = 264,
    KeyUp          = 265, KeyPageUp   = 266,
    KeyPageDown    = 267, KeyHome     = 268,
    KeyEnd         = 269, KeyCapsLock = 280,
    KeyScrollLock  = 281, KeyNumLock  = 282,
    KeyPrintScreen = 283, KeyPause    = 284,

    KeyF1  = 290,         KeyF2  = 291,
    KeyF3  = 292,         KeyF4  = 293,
    KeyF5  = 294,         KeyF6  = 295,
    KeyF7  = 296,         KeyF8  = 297,
    KeyF9  = 298,         KeyF10 = 299,
    KeyF11 = 300,         KeyF12 = 301,

    KeyLeftShift  = 340,  KeyLeftControl  = 341,
    KeyLeftAlt    = 342,  KeyLeftSuper    = 343,
    KeyRightShift = 340,  KeyRightControl = 341,
    KeyRightAlt   = 342,  KeyRightSuper   = 343,
//==========================================
    // KeyPad keys goes here
} Key;

// Mouse buttons
typedef enum {
    MouseButtonLeft    = 0,     // Mouse Button Left
    MouseButtonRight   = 1,     // Mouse Button Right
    MouseButtonMiddle  = 2,     // Mouse Button Middle  (pressed wheel)
    MouseButtonSide    = 3,     // Mouse Button Side    (for cooller mouses (like mine))
    MouseButtonExtra   = 4,     // Mouse Button Extra   (for cooller mouses)
    MouseButtonForward = 5,     // Mouse Button Forward (for cooller mouses)
    MouseButtonBack    = 6,     // Mouse Button Back    (for cooller mouses)
} MouseButton; // Mouse doesn't implemented yet

// Mouse cursor states
typedef enum { // TODO: Complete this enum
    MouseCursorDefault      = 0,     // Default Pointer Shape
    MouseCursorArrow        = 1,     // Arrow Shape
    MouseCursorIbeam        = 2,     // Text Writing Cursor Shape
    MouseCursorCrosshair    = 3,     // Cross Shape
    MouseCursorPointingHand = 4,     // Finger tap-tap
    MouseCursorResizeEw     = 5,     // Horizontal Resize Arrow Shape
    MouseCursorResizeNs     = 6,     // Vertical Resize Arrow Shape
} MouseCursor;

void printl(const char *type, const char *format, ...);
void yaGLinit(const char *title, int width, int height);
void InitWindow(const char *title, int width, int height);
int  WindowClosed();
void ClearScreen();
void SwapBuffer();
void SetFPS(int fps);
void LimitFPS();

// Math
// Nothing ever happen (silksong when...)

// Shapes
void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
void DrawLineV(Vec2 startPos, Vec2 endPos, Color color);
void DrawRect(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, Color color);
void DrawRectV(Vec2 topLeft, Vec2 bottomRight, Color color);
void DrawCircle(Vec2 center, float radius, Color color);

// Textures and images
Image   LoadImage(const char *filepath);
Texture LoadTextureFromImage(Image image);
Texture LoadTexture(const char *filepath);
void    UnloadImage(Image image);
void    DrawTexture(Texture texture, int posX, int posY, int width, int height);
void    UnloadTexture(Texture texture);

// Text
Font LoadFont(const char *fontPath, float fontSize);
void DrawText(Font font, float x, float y, float scale, Color color, const char *text, ...);

// Input
int KeyAction(Key key, int state); // KEY_PRESS or KEY_RELEASE
int MouseAction(MouseButton button, int state);
void GetCursorPos(double *posX, double *posY);

// Camera
Camera InitCamera(int viewportWidth, int viewportHeight);
void   BeginCamera(Camera *cam);
void   EndCamera();
void   ScreenToWorld(float screenX, float screenY, float *worldX, float *worldY);

// Physics
Hitbox CreateHitbox(float x, float y, float width, float height);
void   UpdateHitbox(Hitbox *hb, float x, float y);
bool   collision(const Hitbox *hb1, const Hitbox *hb2);
int    CircleCollision(const CircleHitbox *c1, const CircleHitbox *c2);
void   InitObject(Object *obj, float x, float y, float width, float height);
void   UpdateObject(Object *obj, float newX, float newY);
void   DrawHitbox(const Hitbox *hb, Color color);

#endif
