#include <math.h>
#include <yagl.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_SIZE 9
#define TILE_SIZE 64

#define SPEED 0.1

int map[MAP_SIZE][MAP_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 0}
};

typedef struct {
    Vec2 position;
    Vec2 direction;
    Vec2 plane;
} Player;

void Draw3DView(Player player) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        Vec2 rayDir = {
            player.direction.x + player.plane.x * cameraX,
            player.direction.y + player.plane.y * cameraX
        };

        Vec2 mapPos = { (int)player.position.x, (int)player.position.y };
        Vec2 sideDist;
        Vec2 deltaDist = {
            sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
            sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y))
        };
        double perpWallDist;
        Vec2 step;
        int hit = 0;
        int side;

        if (rayDir.x < 0) {
            step.x = -1;
            sideDist.x = (player.position.x - mapPos.x) * deltaDist.x;
        } else {
            step.x = 1;
            sideDist.x = (mapPos.x + 1.0 - player.position.x) * deltaDist.x;
        }
        if (rayDir.y < 0) {
            step.y = -1;
            sideDist.y = (player.position.y - mapPos.y) * deltaDist.y;
        } else {
            step.y = 1;
            sideDist.y = (mapPos.y + 1.0 - player.position.y) * deltaDist.y;
        }

        while (hit == 0) {
            if (sideDist.x < sideDist.y) {
                sideDist.x += deltaDist.x;
                mapPos.x += step.x;
                side = 0;
            } else {
                sideDist.y += deltaDist.y;
                mapPos.y += step.y;
                side = 1;
            }
            if (map[(int)mapPos.x][(int)mapPos.y] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (mapPos.x - player.position.x + (1 - step.x) / 2) / rayDir.x;
        else perpWallDist = (mapPos.y - player.position.y + (1 - step.y) / 2) / rayDir.y;

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        Color color;
        if (map[(int)mapPos.x][(int)mapPos.y] == 1) color = (Color){255., 0., 0., 127};
        else color = (Color){0., 255., 0., 255.};

        if (side == 1) {color.r /= 2; color.g /= 2; color.b /= 2;}

        DrawLine(x, drawStart, x, drawEnd, color);
    }
}

int main() {
    InitWindow("Yet Another Raycasting", SCREEN_WIDTH, SCREEN_HEIGHT);

    Player player = {
        .position = {2.0, 2.0},
        .direction = {-1.0, 0.0},
        .plane = {0.0, 0.66}
    };

    SetFPS(60);
    while (!WindowClosed()) {
        LimitFPS();
        if (KeyAction(KeyRight, KEY_PRESS)) {
            double oldDirX = player.direction.x;
            player.direction.x = player.direction.x * cos(-0.1) - player.direction.y * sin(-0.1);
            player.direction.y = oldDirX * sin(-0.1) + player.direction.y * cos(-0.1);
            double oldPlaneX = player.plane.x;
            player.plane.x = player.plane.x * cos(-0.1) - player.plane.y * sin(-0.1);
            player.plane.y = oldPlaneX * sin(-0.1) + player.plane.y * cos(-0.1);
        }
        if (KeyAction(KeyLeft, KEY_PRESS)) {
            double oldDirX = player.direction.x;
            player.direction.x = player.direction.x * cos(0.1) - player.direction.y * sin(0.1);
            player.direction.y = oldDirX * sin(0.1) + player.direction.y * cos(0.1);
            double oldPlaneX = player.plane.x;
            player.plane.x = player.plane.x * cos(0.1) - player.plane.y * sin(0.1);
            player.plane.y = oldPlaneX * sin(0.1) + player.plane.y * cos(0.1);
        }
        if (KeyAction(KeyW, KEY_PRESS)) {
            if (map[(int)(player.position.x + player.direction.x * 0.1)][(int)(player.position.y)] == 0) player.position.x += player.direction.x * SPEED;
            if (map[(int)(player.position.x)][(int)(player.position.y + player.direction.y * 0.1)] == 0) player.position.y += player.direction.y * SPEED;
        }
        if (KeyAction(KeyS, KEY_PRESS)) {
            if (map[(int)(player.position.x - player.direction.x * 0.1)][(int)(player.position.y)] == 0) player.position.x -= player.direction.x * SPEED;
            if (map[(int)(player.position.x)][(int)(player.position.y - player.direction.y * 0.1)] == 0) player.position.y -= player.direction.y * SPEED;
        }

        ClearScreen();
            Draw3DView(player);
        SwapBuffer();
    }
    return 0;
}
