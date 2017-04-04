#include "Renderer.h"
#include <GL/glext.h>
#include <GL/glu.h>
#include <fstream>

void renderColoredQuad(float x, float y, float width, float height, Color color)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    glColor4f(color.r, color.g, color.b, color.a);

    glBegin(GL_QUADS);
    glVertex2f(0 ,0);
    glVertex2f(0, height);
    glVertex2f(width, height);
    glVertex2f(width, 0);
    glEnd();

    glPopMatrix();

    glLoadIdentity();
}

void renderTexturedQuad(float x, float y, float width, float height, GLuint texture, Color color)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    glColor4f(color.r, color.g, color.b, color.a);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(0 ,0);

    glTexCoord2f(0, 1);
    glVertex2f(0, height);


    glTexCoord2f(1, 1);
    glVertex2f(width, height);


    glTexCoord2f(1, 0);
    glVertex2f(width, 0);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glLoadIdentity();
}

GLuint loadBMP(const char* path)
{
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;

    unsigned char * data;

    FILE* file = fopen(path, "rb");

    if(!file){
        printf("File: %s not found!\n", path);
        return 0;}

    if(fread(header, 1, 54, file)!=54){
        printf("File: %s incorrect format!\n", path);
        return 0;}

    if(header[0]!= 'B' || header[1] !='M'){
        printf("File: %s incorrect format!\n", path);
        return 0;}

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    if(imageSize==0)
        imageSize=width*height*3;

    data = new unsigned char [imageSize];

    fread(data,1,imageSize,file);

    fclose(file);

    printf("File: %s successfully loaded!\n", path);
    printf("Width: %i\nHeight: %i\n", width, height);

    GLuint textureID;

    glGenTextures(1, &textureID);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glDisable(GL_TEXTURE_2D);

    return textureID;
}
