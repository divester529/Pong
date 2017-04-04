#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED
#include <GL/gl.h>
#include <windows.h>
#include "states/GameState.h"
#include "states/GameOverState.h"


class Instance
{
public:
    Instance();
    ~Instance();

    void doLogic();

    void getInput(MSG* );

    void render();

private:
    State* states[2]; // [0]=Running, [1]=GameOver
    int curState;
};

#endif // INSTANCE_H_INCLUDED
