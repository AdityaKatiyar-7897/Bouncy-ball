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

    SDL_Renderer* renderer =SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int running = 1;
    SDL_Event event;

    float x = 300.0f;
    float velocity = 0.5f;

    int width = 200;
    int height = 150;
    int top = 200;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        int left = (int)x;

        for (int y_pos = top; y_pos < top + height;y_pos++)
        {
        	for (int x_pos = left; x_pos < left + width; x_pos++)
        	{
        		SDL_RenderDrawPoint(renderer, x_pos, y_pos);
        	}
        }

       

        x += velocity;

        if (x <= 0 || x + 200 >=800)
        {
        	velocity = -velocity;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
