/**Abstract Base Class for all Entities
**
**
**/
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include "../Renderer.h"
#include <GL/gl.h>

class Entity
{
public:
    Entity();

    virtual void render();

    float getX();
    float getY();

    float getWidth();
    float getHeight();

    void setX(float _x);
    void setY(float _y);

    void setWidth(float _w);
    void setHeight(float _h);

    void incrX(float _f); // Increases x by f
    void incrY(float _f); // Increases y by f

    void setColor(float r, float g, float b, float a);

protected:
    float x, y; // Position
    float width, height;// Width & height

    Color color; // Entity color
};

#endif // ENTITY_H_INCLUDED
