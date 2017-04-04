#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include <windows.h>
#include <GL/gl.h>
#include "../entities/Entity.h"
#include "../entities/Ball.h"
#include "State.h""

class GameState: public State
{
public:
    GameState();

    void getInput(MSG* msg);

    void doLogic();

    void render();

private:
    Entity *players[2];
    Entity *arena; // Window Area

    Ball*ball;

    int score[2];

    bool gameOver;

    bool checkCollision(Entity* _entity1, Entity* _entity2); // Checks for collision between two entities
};

#endif // GAMESTATE_H_INCLUDED
