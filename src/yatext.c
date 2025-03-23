#include <stdio.h>
#include <GL/gl.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>
#include "yagl.h"

Font LoadFont(const char *fontPath, float fontSize) { // TODO: Make it possible to load system font
    Font font;
    font.fontSize = fontSize;

    FILE *fontFile = fopen(fontPath, "rb");
    if (!fontFile) printl(ERROR, "Failed to open font file: %s\n", fontPath);

    fseek(fontFile, 0, SEEK_END);
    long fileSize = ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);

    unsigned char *ttfBuffer = (unsigned char*)malloc(fileSize);
    fread(ttfBuffer, 1, fileSize, fontFile);
    fclose(fontFile);

    unsigned char* tempBitmap = (unsigned char*)malloc(512 * 512);
    stbtt_BakeFontBitmap(ttfBuffer, 0, fontSize, tempBitmap, 512, 512, 32, 96, font.cdata); // Just ignore it

    glGenTextures(1, &font.textureID);
    glBindTexture(GL_TEXTURE_2D, font.textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, tempBitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(ttfBuffer);
    free(tempBitmap);
    return font;
}

void DrawText(Font font, const char *text, float x, float y, float scale) {
    glBindTexture(GL_TEXTURE_2D, font.textureID);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
    for (const char *p = text; *p; p++) {
        if (*p >= 32 /*  && *p < 128 */ ) { // FIX: Result of comparison of constant 128 with expression of type 'const char' is always true
            Bakedchar *b = &font.cdata[*p - 32];

            float xpos = x + b->xoff * scale;
            float ypos = y - b->yoff * scale;

            float w = b->x1 - b->x0;
            float h = b->y1 - b->y0;

            glTexCoord2f(b->x0 / 512.0f, b->y0 / 512.0f); glVertex2f(xpos, ypos);
            glTexCoord2f(b->x1 / 512.0f, b->y0 / 512.0f); glVertex2f(xpos + w * scale, ypos);
            glTexCoord2f(b->x1 / 512.0f, b->y1 / 512.0f); glVertex2f(xpos + w * scale, ypos + h * scale);
            glTexCoord2f(b->x0 / 512.0f, b->y1 / 512.0f); glVertex2f(xpos, ypos + h * scale);

            x += b->xadvance * scale;
        }
    }
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}
