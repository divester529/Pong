#ifndef GAMEOVERSTATE_H_INCLUDED
#define GAMEOVERSTATE_H_INCLUDED
#include "State.h"

class GameOverState: public State
{
public:
    GameOverState();

    void doLogic();

    void getInput(MSG* msg);

    void render();

private:

};

#endif // GAMEOVERSTATE_H_INCLUDED
