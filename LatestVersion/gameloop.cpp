#include "gameloop.hpp"

GameLoop::GameLoop() : window(nullptr), renderer(nullptr), character1(nullptr), character2(nullptr), currentTexture(nullptr), mm("Begin") {}

GameLoop::~GameLoop() 
{
    cleanUp();
}


bool GameLoop::init()
{
    const char* windowTitle = "Habibi Showdown 2: Electric Boogaloo"; //title
    int windowWidth = 800; //width of window
    int windowHeight = 600; //and height


    if (!initSDL(window, renderer, windowTitle, windowWidth, windowHeight)) //error handling: note that the error handling is not comprehensive since we required it early on, then abandoned as we gained confidence in the process. also was taken from online since we could not write this ourselves
        return false;
    if (!loadTextures()) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load textures.");
        return false;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
        return false;
    }

    //load startup music
    startUpMusic = Mix_LoadMUS("RadioheadCreep.wav"); //loading the music at the beginning of the game
    matchMusic = Mix_LoadMUS("TheKingofFighters'96-ArashinoSaxophone2.wav"); //and during the game
    winMusic = Mix_LoadMUS("Winner-_Winner-Screen-Theme_-OST.wav");
    if (startUpMusic == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load background music! SDL_mixer Error: %s", Mix_GetError());
        return false;
    }

    
    currentTexture = beginTexture; //and beginning texture
    isMusicPlaying = false; //music not playing at beginning

    unordered_set<SDL_Keycode> pressedKeys; //this keeps a record of keys pressed in keyboard

    character1 = nullptr; //initializing our pointers as null pointers
    character2 = nullptr;
    timer = nullptr;
    return true; //to confirm that we have initialized successfully
}

bool GameLoop::loadTextures() 
{
    beginTexture = loadTexture("start.png", renderer); //we are storing the loaded textures in their respective variables, and we use the renderer to do so.
    
    IoriWin = loadTexture("IoriWin.jpg", renderer); //if iori wins, show this
    KyoWin = loadTexture("KyoWin.jpg", renderer); //and vice versa

    bg0 = loadTexture("park/frame_0.png", renderer); //background textures of the game, which is an animation
    bg1 = loadTexture("park/frame_1.png", renderer);
    bg2 = loadTexture("park/frame_2.png", renderer);
    bg3 = loadTexture("park/frame_3.png", renderer);
    bg4 = loadTexture("park/frame_4.png", renderer);
    bg5 = loadTexture("park/frame_5.png", renderer);
    bg6 = loadTexture("park/frame_6.png", renderer);
    bg7 = loadTexture("park/frame_7.png", renderer);

    health_1 = loadTexture("IoriHealth.png", renderer); //first health bar
    health_2 = loadTexture("KyoHealth.png", renderer); //and second
    clockbg = loadTexture("clockbg.png", renderer); //clock

    bgAnimator.pushFrame(bg0); //pushing the frames of the background into its respective animator
    bgAnimator.pushFrame(bg1);
    bgAnimator.pushFrame(bg2);
    bgAnimator.pushFrame(bg3);
    bgAnimator.pushFrame(bg4);
    bgAnimator.pushFrame(bg5);
    bgAnimator.pushFrame(bg6);
    bgAnimator.pushFrame(bg7);


    return true; //successfully loaded!
}

void GameLoop::run() {
    quit = false; //the user has not quit yet.
    Mix_PlayMusic(startUpMusic, -1); //play the starting music on loop (hence the -1)
    isMusicPlaying = true; //we are playing music
    while (!quit) { //until the user quits, do the following
        handleEvents(); //handle ingame events, elaborated on later
        update(); //then update the elements
        render(); //and render accordingly
    }
}

void GameLoop::handleEvents() 
{
    while (SDL_PollEvent(&e) != 0) //while the event of the game does not end
    {
        if (e.type == SDL_QUIT) 
            quit = true; //quit the game once app closed
        else if (e.type == SDL_KEYDOWN) //down key is pressed, this format is followed for later too
        {
            pressedKeys.insert(e.key.keysym.sym); //record the key pressed until it is released
        } 
        else if (e.type == SDL_KEYUP) //key released, free from pressed keys
            pressedKeys.erase(e.key.keysym.sym);
        else if (e.type == SDL_MOUSEBUTTONDOWN) //currently, switch states of game using mouse button. this will be changed later for match to end state
        {
            //switch state and texture on mouse click
            if (mm.getGameState() == "Begin") //we have clicked on begin state, so start the match
            {
                Mix_HaltMusic(); //enough radiohead, coldplay is better anyway
                Mix_PlayMusic(matchMusic, -1); //time for some saxophone
                SDL_Rect orig1Rect = {200, 366, 160, 208};  //beginning positions of my characters
                SDL_Rect orig2Rect = {550, 350, 160, 224}; //note that the x position is greater as kyo should be on the right
                character1= new Iori("Iori", 200, 100, 1, orig1Rect, true, renderer); //new derived class object stored in base pointer for polymorphism! read constructor to understand parameters
                character2 = new Kyo("Kyo", 200, 100, 2, orig2Rect, false, renderer);
                timer = new Timer(renderer, 800, 54);  //set the countdown time to 60 seconds
                timer->start(); //tick tock your time starts now :3

                mm.setGameState("Match");
                attackOne = false; //checks if we are attacking or not
                attackTwo = false;
            } 
            else if (mm.getGameState() == "End") 
            {
                mm.setGameState("Begin");
                currentTexture = beginTexture; //time to restart the game, so move to start screen
                if (!isMusicPlaying) 
                {
                    Mix_PlayMusic(startUpMusic, -1);  //-1 for infinite loop
                    isMusicPlaying = true;
                }
            }
        }
    }
}


void GameLoop::update()
{
    if (mm.getGameState() == "Match") //update only during match time, of course!
    {
        currentTexture = bgAnimator.animate(150); //animate the bg
        if ((character2->getDefeatState()) && (character2->defeatAnimator.isOn() == false) || (character1->getDefeatState() && (character1->defeatAnimator.isOn() == false))) //a player must be defeated AND their respective death animation is complete
        {
            {
                if (character1->getDefeatState()) //iori is defeated, so kyo has won
                    currentTexture = KyoWin;
                else
                    currentTexture = IoriWin;
                delete character1; //delete the memory in the pointers we have to avoid memory leaks, and assign null pointers to avoid leaving them dangle
                delete character2;
                delete timer;
                timer = nullptr;
                character1 = nullptr;
                character2 = nullptr;
                mm.setGameState("End"); //game is over. go home.
                Mix_HaltMusic(); //might replace with win music?
                Mix_PlayMusic(winMusic, 0); 
                return; //we dont want to access the following code!
            }
        }
        character1->move(pressedKeys, *character2); //handle the movement of the characters depending on buttons pressed
        character2->move(pressedKeys, *character1);

        character1->attackHandler(pressedKeys, *character2); //and handle their attacks
        character2->attackHandler(pressedKeys, *character1);

        if (character1->getJumpState() || character2->getJumpState()) //are any of them jumping (kris kross will make you)
        {
            if (character1->getJumpState())
                character1->gravity(*character2); //if iori is jumping, we have to make sure he doesnt crash into kyo and lands reasonably!
            if (character2->getJumpState())
                character2->gravity(*character1); //and vice versa
        }
        
    }
}

void GameLoop::render() //i rendered them all! the women and children too!
{
    //clear the screen
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, currentTexture, nullptr, nullptr);
    //render the current texture

    if (mm.getGameState() == "Match") //only render players once it is match state
    {
        SDL_Rect playerOneRect = character1->getHitbox(); //this is so that we know where our players are at the moment
        SDL_Rect playerTwoRect = character2->getHitbox();
        character1->handleDirection(*character2); //so that they may always face each other
        character2->handleDirection(*character1);
        character1->display(renderer,playerOneRect,pressedKeys); //polymorphism implemented successfully! read the classes to know more
        character2->display(renderer, playerTwoRect, pressedKeys);
        character1->renderHealth(renderer); //and of course render the health values (not the graphics)
        character2->renderHealth(renderer);
        SDL_Rect orig2Rect = {550, 350, 144, 224}; //might delete this
        SDL_Rect health1Rect = {0, 20, 350, 120}; //initialize the health positions (this is for the graphics of the health, not the value of the health itself!)
        SDL_Rect health2Rect = {450, 20, 350, 120};
        SDL_RenderCopy(renderer, health_1, nullptr, &health1Rect); //and render them
        SDL_RenderCopy(renderer, health_2, nullptr, &health2Rect);
        SDL_Rect clockrect = {344, 15, 110, 110};
        SDL_RenderCopy(renderer, clockbg, nullptr, &clockrect); //similar for clock
        timer->render();
    }

    //and update the screen
    SDL_RenderPresent(renderer);
}

void GameLoop::cleanUp()
{
    //free resources once game is truly over
    SDL_DestroyTexture(beginTexture);
    SDL_DestroyTexture(endTexture);
    SDL_DestroyTexture(bg0);
    SDL_DestroyTexture(bg1);
    SDL_DestroyTexture(bg2);
    SDL_DestroyTexture(bg3);
    SDL_DestroyTexture(bg4);
    SDL_DestroyTexture(bg5);
    SDL_DestroyTexture(bg6);
    SDL_DestroyTexture(bg7);
    SDL_DestroyTexture(IoriWin);
    SDL_DestroyTexture(KyoWin);

    SDL_DestroyTexture(health_1);
    SDL_DestroyTexture(health_2);
    SDL_DestroyTexture(clockbg);
    Mix_FreeMusic(startUpMusic);
    TTF_Quit();
    //close SDL and free resources
    closeSDL(window, renderer);
}
