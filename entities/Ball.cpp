#include "ball.h"
#include <math.h>
#include <stdio.h>

Ball::Ball()
{
    setWidth(16);
    setHeight(16);
}

void Ball::setAngle(float _angle)
{
    angle=_angle;
    printf("Angle-%f\nSin-%f\nCos-%f\n", _angle, sin(angle), cos(angle));
}

void Ball::setVelocity(float _vel)
{
    velocity=_vel;
}

void Ball::update()
{
    x+=cos((3.14*angle)/180)*velocity;
    y+=sin((3.14*angle)/180)*velocity;
}

float Ball::getVelocity(){
    return velocity;}

float Ball::getAngle(){
    return angle;}
