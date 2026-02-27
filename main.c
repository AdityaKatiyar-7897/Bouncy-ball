#include <SDL2/SDL.h>

int main()
{
    // 1. Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // 2. Create window
    SDL_Window* window = SDL_CreateWindow(
        "Mouse Ball",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0
    );

    // 3. Create renderer (our drawing tool)
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    int running = 1;
    SDL_Event event;

    // Ball center position
    int cx = 400;
    int cy = 300;
    int radius = 40;

    while (running)
    {
        // --- Handle Events ---
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                cx = event.motion.x;
                cy = event.motion.y;
            }
        }

        // --- Clear Screen ---
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // --- Draw Ball ---
        SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);

        for (int y = cy - radius; y <= cy + radius; y++)
        {
            for (int x = cx - radius; x <= cx + radius; x++)
            {
                int dx = x - cx;
                int dy = y - cy;

                if (dx * dx + dy * dy <= radius * radius)
                {
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }

        // --- Show Frame ---
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
