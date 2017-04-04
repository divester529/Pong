#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#include "Entity.h"

class Ball: public Entity
{
public:
    Ball();

    void setAngle(float _angle); // Sets ball angle

    void setVelocity(float _vel); // Sets ball velocity

    float getVelocity();
    float getAngle();

    void update(); // Updates position by (cos(x)*vel, sin(y)*vel)

private:
    float velocity; // Ball velocity

    float angle; // Angle in Radians
};


#endif // BALL_H_INCLUDED
