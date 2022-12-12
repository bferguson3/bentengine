#include <stdio.h>

#include "renderer.h"

int main(int argn, char **argv)
{
    // init sdl class
    SDLEngine sdl2;

    // print HW
    sdl2.hello();

    bool q = false;
    while (!q)
    {
        // update
        sdl2.update(&q);

        // draw frame
        sdl2.draw();
    }

    return 0;
}
