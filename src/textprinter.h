

#ifndef TEXTPRINTER_H_
#define TEXTPRINTER_H_


#include <SDL.h>
#include <SDL_ttf.h>


#include <memory>
#include <string>
#include <vector>


#include "timer.h"


struct TimedText
{


    public:


        // duration_sec is the duration in seconds the
        // text should stay on screen for.
        TimedText(std::string message, SDL_Color colour,
            float duration_sec, float time_in, int x, int y);


        std::string text;


        float duration;


        SDL_Color colour;


        int x;


        int y;


        float time_in;


};


class TextPrinter
{


    public:


        TextPrinter();


        TextPrinter(std::string font_filename, int text_size);


        void PrintText(SDL_Renderer *ren); 


        void AddText(std::string text, SDL_Color colour, 
            float duration_sec, int x, int y);


    private:


        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> text_tex;


        std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> font;


        std::vector<TimedText> print_list;


        Timer text_timer;


        void LoadFont(std::string font_filename, int size);


};


#endif // TEXTPRINTER_H_






