

#include "app_main.h"


AppMain::AppMain(int level_w, int level_h) : 
    win(SDL_CreateWindow(
    "Map Editor v0.0.1", 0, 0, 640, 480, SDL_WINDOW_SHOWN),
    SDL_DestroyWindow),
    ren(SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_PRESENTVSYNC
    | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED),
    SDL_DestroyRenderer)
{

    app_quit = false;

    camera = {0, 0, 640, 480};

    cam_vel = 1;

    this->level_w = level_w;

    this->level_h = level_h;

}


void AppMain::EventLoop()
{

    SDL_Event e;

    while(SDL_PollEvent(&e))
    {

        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE
            || e.type == SDL_QUIT)
        {

            app_quit = true;

        }

        editor->HandleEvents(e, ren.get(), camera);

    }

}


void AppMain::MainLoop()
{

    editor = new Editor("resources/Hack-Regular.ttf", 28, "resources", 
        ren.get(), 3200, 3200);

    float frame_time = 0.0;    

    while(!app_quit)
    {

        frame_timer.StartTimer();

        SDL_Delay(0017);

        SDL_SetRenderDrawColor(ren.get(), 127, 127, 127, 255);

        SDL_RenderClear(ren.get());

        EventLoop();

        MoveCamera(frame_time);

        editor->Update(ren.get(), camera);
        
        SDL_RenderPresent(ren.get());

        frame_timer.StopTimer();

        frame_time = frame_timer.GetTimeMs();

    }

}


void AppMain::MoveCamera(float frame_time)
{

    int x, y;

    SDL_GetMouseState(&x, &y);

    if(x >= 0 && x <= 40)
    {

        camera.x -= cam_vel * frame_time;

    }
    else if(x <= camera.w && x >= camera.w - 40)
    {

        camera.x += cam_vel * frame_time;

    }
    
    if(y >= 0 && y <= 40)
    {

        camera.y -= cam_vel + frame_time;

    }
    else if(y <= camera.h && y >= camera.h - 40)
    {

        camera.y += cam_vel * frame_time;

    }

    InBounds();

}


void AppMain::InBounds()
{

   if(camera.x < 0)
   {

        camera.x = 0;

   }

   if(camera.y < 0)
   {

       camera.y = 0;

   }

   if(camera.x + camera.w > level_w)
   {

       camera.x = level_w - camera.w;

   }

   if(camera.y + camera.h > level_h)
   {

       camera.y = level_h - camera.h;

   }

}


