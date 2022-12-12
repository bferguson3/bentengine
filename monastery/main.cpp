
#include <stdio.h>
#include "renderer.h"
#include "text.h"

// init sdl class
SDLEngine engine;

// functions
void FrameDelay(float fps, float frameStart, float frameEnd);

// main!
int main(int argn, char** argv)
{
    // hello world!
    // SDL_Rect loc = {0, 0, 128, 24};
    Text* hw = new Text("Hello World!", 0, 0, 128, 24);

    bool q = false;
    float frameStart, frameEnd;
    while (!q)
    {
        frameStart = SDL_GetPerformanceCounter();

        // update
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