
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"
#include "text.h"

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

GameObject* player;

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
    player = new GameObject();

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
            break;
        }
        // input parser
        DoInput();
        // run event parser
        engine.update(&q);
        // draw frame
        engine.draw();
        frameEnd = SDL_GetPerformanceCounter();
        // lock framerate
        FrameDelay(FPS_60, frameStart, frameEnd);
    }

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
    player->SetTexture(LoadImageToTexture("monkspr.png"));
    player->SetSize(64, 64);
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
