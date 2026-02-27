#include <SDL2/SDL.h>
#include <math.h>

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

    float cx = 400.0f;
    float cy = 300.0f;
    int radius = 40;

    float velocityY = 0.0f;
    float gravity = 0.2f;       
    float bounceFactor = 0.8f;  

    int isHeld = 1;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            if (event.type == SDL_MOUSEMOTION && isHeld)
            {
                cx = event.motion.x;
                cy = event.motion.y;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                isHeld = 0;
                velocityY = 0.0f;
            }
        }

        
        if (!isHeld)
        {
            velocityY += gravity;
            cy += velocityY;

            if (cy + radius >= 600)
            {
                cy = 600 - radius;

                velocityY = -velocityY * bounceFactor;

                if (fabs(velocityY) < 0.5f)
                {
                    velocityY = 0;
                }
            }
        }

        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        
        SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);

        int draw_cx = (int)cx;
        int draw_cy = (int)cy;

        for (int y = draw_cy - radius; y <= draw_cy + radius; y++)
        {
            for (int x = draw_cx - radius; x <= draw_cx + radius; x++)
            {
                int dx = x - draw_cx;
                int dy = y - draw_cy;

                if (dx * dx + dy * dy <= radius * radius)
                {
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }

        SDL_RenderPresent(renderer);

        //for 60 fps
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
