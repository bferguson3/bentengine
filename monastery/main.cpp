
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"
#include "text.h"
#include "tilesheet.h"
#include "sprite.h"
#include "player.h"

// init sdl class
SDLEngine engine;

enum InputMode
{
    TESTINPUT,
    DISABLED,
    EXPLORING
} inputMode;

enum GameState
{
    TESTSTATE
} gameState;

Player* player;

int frameCounter;

// functions
void FrameDelay(float fps, float frameStart, float frameEnd);
void DoInput();
void LoadScene(int sceneNo);
SDL_Texture* LoadImageToTexture(char* path);

// main!
int main(int argn, char** argv)
{
    // hello world!
    Text* hw = new Text("Hello World!", 0, 0, 128, 24);
    player = new Player(new TileSheet("monkspr.png", 4, 1, 16, 24));

    player->SetTexture(0);

    LoadScene(0);

    bool q = false;
    float frameStart, frameEnd;
    while (!q)
    {
        frameStart = SDL_GetPerformanceCounter();
        // Main Code :
        // CSM check
        switch (gameState)
        {
        case TESTSTATE:
            player->update();
            break;
        }

        DoInput();         // input parser
        engine.update(&q); // run event parser
        engine.draw();     // draw frame

        frameEnd = SDL_GetPerformanceCounter();
        FrameDelay(FPS_60, frameStart, frameEnd); // lock framerate
    }

    delete player;
    delete hw;
    // tilesheets are deleted inside sprites.

    return 0;
}

void FrameDelay(float fps, float frameStart, float frameEnd)
{
    float frameElapsed = (frameEnd - frameStart);
    float deltaTime = frameElapsed / engine.GetPerfFrequency(); // ticks / how many ticks per milisecond = time

    deltaTime = floor(fps) - deltaTime;

    SDL_Delay(deltaTime);
}

void DoInput()
{
    switch (inputMode)
    {
    case TESTINPUT:
        break;
    case DISABLED:
        break;
    }
}

void LoadScene(int sceneNo)
{
    // load in player graphics
    player->SetSize(16, 24);
    // set states TODO - make this class mgr?
    inputMode = DISABLED;
    gameState = TESTSTATE;
}

SDL_Texture* LoadImageToTexture(char* path)
{
    SDL_Surface* cv = IMG_Load(path); // SDL_LoadBMP(path);
    if (cv == NULL)
    {
        printf("Couldn't load image %s. Error: %s", path, SDL_GetError());
    }
    SDL_Texture* st = SDL_CreateTextureFromSurface(engine.GetRenderer(), cv);
    SDL_FreeSurface(cv);
    return st;
}
