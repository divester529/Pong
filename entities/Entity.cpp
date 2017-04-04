#include "Entity.h"

Entity::Entity()
{
    color={1, 1, 1, 1};
    x=y=0;
    width=32;
    height=128;
}

void Entity::render()
{
    renderColoredQuad(x, y, width, height, color);
}

float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}

float Entity::getWidth()
{
    return width;
}

float Entity::getHeight()
{
    return height;
}

void Entity::setX(float _x)
{
    x=_x;
}

void Entity::setY(float _y)
{
    y=_y;
}

void Entity::incrX(float _f)
{
    x+=_f;
}

void Entity::incrY(float _f)
{
    y+=_f;
}

void Entity::setWidth(float _w)
{
    width=_w;
}

void Entity::setHeight(float _h)
{
    height=_h;
}

void Entity::setColor(float r, float g, float b, float a)
{
    color.r=r;
    color.g=g;
    color.b=b;
    color.a=a;
}
