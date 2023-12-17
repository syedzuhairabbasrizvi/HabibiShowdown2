#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Function prototypes
bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Mix_Music* bgMusic = NULL;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    bgMusic = Mix_LoadMUS("RadioheadCreep.wav");
    if (bgMusic == NULL)
    {
        std::cerr << "Unable to load music: " << Mix_GetError() << std::endl;
        success = false;
    }

    return success;
}

void close()
{
    Mix_FreeMusic(bgMusic);
    bgMusic = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!init())
    {
        std::cerr << "Failed to initialize!\n";
    }
    else
    {
        if (!loadMedia())
        {
            std::cerr << "Failed to load media!\n";
        }
        else
        {
            bool quit = false;
            SDL_Event e;

            if (Mix_PlayMusic(bgMusic, 0) == -1)
            {
                std::cerr << "Mix_PlayMusic: " << Mix_GetError() << std::endl;
            }

            SDL_Delay(5000); // Wait for 5 seconds

            Mix_HaltMusic();

            quit = true;
        }
    }

    close();

    return 0;
}
