#include <GL/gl.h>
#include "yagl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

Image LoadImage(const char *filename) {
    Image image = {0};

    image.data = stbi_load(filename, &image.width, &image.height, &image.format, 0);
    if (!image.data) {
        printl(WARNING, "Failed to define %s extension", filename);
        return image;
    }

    if (image.format == 3) image.format = GL_RGB;
    else if (image.format == 4) image.format = GL_RGBA;
    else {
        printl(WARNING, "Unsupported image format: %s", filename);
        stbi_image_free(image.data);
        image.data = NULL;
        return image;
    }

    image.mipmaps = 1;

    printl(NOTE, "IMAGE (%s):", filename);
    printl(NONE, "Width:    %d", image.width);
    printl(NONE, "Height:   %d", image.height);
    printl(NONE, "Channels: %d", image.format);
    return image;
}

Texture LoadTextureFromImage(Image image) {
    Texture texture = {0};

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);

    // if (image.mipmaps > 1) glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture.width = image.width;
    texture.height = image.height;
    texture.mipmaps = image.mipmaps;
    texture.format = image.format;

    return texture;
}
void UnloadImage(Image image) { if (image.data) stbi_image_free(image.data); }

void DrawTexture(Texture texture, int posX, int posY, int width, int height, Color color) {
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glEnable(GL_TEXTURE_2D);
    glColor4f(color.r, color.b, color.g, color.a);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex2f(posX, posY);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(posX + width, posY);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(posX + width, posY + height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(posX, posY + height);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void UnloadTexture(Texture texture) { glDeleteTextures(1, &texture.id); }

Texture LoadTexture(const char *filepath) { // Cool function, I know
    Image temp = LoadImage(filepath);
    Texture texture = LoadTextureFromImage(temp);
    UnloadImage(temp);
    return texture;
}
