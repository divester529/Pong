#include "gamestate.h"
#include "mmsystem.h"
#include <math.h>
#include <time.h>
#include <stdio.h>

GameState::GameState()
{
    swapState=0;
    gameOver=false;

    players[0] = new Entity();
    players[0]->setColor(1, 0, 0, 1);
    players[0]->setX(0);
    players[0]->setY(326);

    players[1] = new Entity();
    players[1]->setColor(0, 0, 1, 1);
    players[1]->setX(992);
    players[1]->setY(326);

    ball = new Ball();
    ball->setColor(0, 1, 0, 1);
    ball->setVelocity(1);
    ball->setAngle(0);
    ball->setX(496);
    ball->setY(382);

    arena = new Entity();
    arena->setWidth(1024);
    arena->setHeight(780);

    score[0]=0;
    score[1]=0;

    GLuint player1wins = loadBMP("player1.bmp");
    GLuint player2wins = loadBMP("player2.bmp");
}

void GameState::getInput(MSG* msg)
{
    if(GetKeyState(0x57) & 0x8000)
        players[0]->incrY(-1);
    else if(GetKeyState(0x53) & 0x8000)
        players[0]->incrY(1);

    if(GetKeyState(VK_UP) & 0x8000)
        players[1]->incrY(-1);
    else if(GetKeyState(VK_DOWN) & 0x8000)
        players[1]->incrY(1);

    if(gameOver==true)
    {
        if(GetKeyState(VK_SPACE) & 0x8000)
        {
            score[0]=score[1]=0;
            ball->setVelocity(1);
            gameOver=false;
        }
    }
}

bool GameState::checkCollision(Entity* _entity1, Entity* _entity2)
{
    if(_entity1->getX()>=_entity2->getX() && _entity1->getX()<=_entity2->getX()+_entity2->getWidth())
        if(_entity1->getY()>=_entity2->getY() && _entity1->getY()<=_entity2->getY()+_entity2->getHeight())
            return true;

    return false;
}

void GameState::doLogic()
{
    ball->update();

    if(ball->getY()>=764 || ball->getY()<=0)
    {
        PlaySound("blip.wav", NULL, SND_FILENAME | SND_ASYNC);

        ball->setAngle(-ball->getAngle());
    }

    if(ball->getX()<=0)
    {
        PlaySound("sound.wav", NULL, SND_FILENAME);

        srand(time(NULL));
        ball->setAngle(-15+rand()%30);
        ball->setVelocity(1);

        ball->setVelocity(1);
        ball->setAngle(0);
        ball->setX(496);
        ball->setY(382);

        score[1]++;
    }

    if(ball->getX()>=1024)
    {
        PlaySound("sound.wav", NULL, SND_FILENAME);

        srand(time(NULL));
        ball->setAngle(-15+rand()%30);
        ball->setVelocity(1);

        ball->setVelocity(1);
        ball->setAngle(0);
        ball->setX(496);
        ball->setY(382);

        score[0]++;
    }

    if(checkCollision(ball, players[0]))
    {
        PlaySound("blip.wav", NULL, SND_FILENAME | SND_ASYNC);

        ball->setVelocity(-ball->getVelocity());

        srand(time(NULL));
        ball->setAngle(-45+rand()%135);
    }

    if(checkCollision(ball, players[1]))
    {
        PlaySound("blip.wav", NULL, SND_FILENAME | SND_ASYNC);

        ball->setVelocity(-ball->getVelocity());

        srand(time(NULL));
        ball->setAngle(-45+rand()%135);
    }

    if(gameOver)
        ball->setVelocity(0);
}

void GameState::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    renderColoredQuad(496, 0, 16, 780, Color{1, 1, 1 ,0});

    players[0]->render();
    players[1]->render();

    ball->render();

    for(int i = 0; i < score[0]; i++)
    {
        renderColoredQuad(16+i*32, 716, 16, 64, Color{1, 0, 0, 0});
    }

    for(int i = 0; i < score[1]; i++)
    {
        renderColoredQuad(992-i*32, 716, 16, 64, Color{0, 0, 1, 0});
    }

    if(score[0]>5){
        gameOver=true;
        renderTexturedQuad(256, 195, 512, 390, 1, Color{1, 1, 1, 0});
    }

    if(score[1]>5){
        gameOver=true;
        renderTexturedQuad(256, 195, 512, 390, 2, Color{1, 1, 1, 0});
    }

    glLoadIdentity();
}
