#include "text.h"
#include "renderer.h"

#include <stdio.h>

// init sdl class
SDLEngine engine;

int main(int argn, char **argv)
{

    SDL_Rect loc = {0, 0, 128, 24};
    Text *hw = new Text("Hello World!", &loc);

    bool q = false;
    while (!q)
    {
        // update
        engine.update(&q);

        // draw frame
        engine.draw();
    }

    return 0;
}
