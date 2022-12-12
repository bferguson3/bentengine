
#include <stdio.h>
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

// functions
void FrameDelay(float fps, float frameStart, float frameEnd);
void DoInput();
void LoadScene(int sceneNo);

GameObject p;

// main!
int main(int argn, char** argv)
{
    // hello world!
    Text* hw = new Text("Hello World!", 0, 0, 128, 24);

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

    // set states TODO - make this class mgr?
    inputMode = DISABLED;
    gameState = TESTSTATE;
}