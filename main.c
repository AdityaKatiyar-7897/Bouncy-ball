#include <SDL2/SDL.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Bouncy Ball Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    int running = 1;
    SDL_Event event;

    float cx = 400.0f;     // center x (float for smooth movement)
    int cy = 300;          // center y
    int radius = 80;

    float velocity = 1.0f; // horizontal speed

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Ball color
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        int draw_cx = (int)cx;

        // Draw filled circle manually
        for (int y = cy - radius; y <= cy + radius; y++)
        {
            for (int x = draw_cx - radius; x <= draw_cx + radius; x++)
            {
                int dx = x - draw_cx;
                int dy = y - cy;

                if (dx * dx + dy * dy <= radius * radius)
                {
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }

        // Update position
        cx += velocity;

        // Bounce logic (correct boundary check)
        if (cx - radius <= 0 || cx + radius >= 800)
        {
            velocity = -velocity;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
