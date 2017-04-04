#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED
#include <GL/gl.h>

struct Color
{
    float r, g, b, a;
};

struct renderObject
{
    float position[2];
    float verticies[4];

    Color color;
};

void renderColoredQuad(float x, float y, float width, float height, Color color);

void renderTexturedQuad(float x, float y, float width, float height, GLuint texture, Color color);

GLuint loadBMP(const char*path);

#endif // RENDERER_H_INCLUDED
