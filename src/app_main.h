

#ifndef APP_MAIN_H_
#define APP_MAIN_H_


#include <SDL.h>


#include <memory>


#include "editor.h"
#include "timer.h"


class AppMain
{


    public:


        AppMain(int level_w, int level_h);


        void EventLoop();


        void MainLoop();


    private:


        std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> win;


        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> ren; 


        Editor *editor;


        Timer frame_timer;


        bool app_quit;


        SDL_Rect camera;


        int level_w;


        int level_h;


        int cam_vel;


        void MoveCamera(float frame_time);


        void InBounds();


};

#endif // APP_MAIN_H_
