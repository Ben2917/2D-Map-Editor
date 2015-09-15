

#include "textprinter.h"


TimedText::TimedText(std::string message, SDL_Color colour,
    float duration_sec, float time_in, int x, int y)
{

    text = message;

    duration_sec = duration;

    this->colour = colour;

    this->time_in = time_in;

    this->x = x;

    this->y = y;

}


TextPrinter::TextPrinter() : 
    text_tex(nullptr, SDL_DestroyTexture),
    font(nullptr, TTF_CloseFont){}


TextPrinter::TextPrinter(std::string font_filename, int text_size)
    : text_tex(nullptr, SDL_DestroyTexture),
    font(nullptr, TTF_CloseFont)
{

    LoadFont(font_filename, text_size);

    text_timer.StartTimer();

}


void TextPrinter::PrintText(SDL_Renderer* ren)
{

    for(int i = 0; i < print_list.size(); ++i)
    {

        if(text_timer.GetTimeMs() > print_list[i].time_in + 
            print_list[i].duration)
        {

            print_list.erase(print_list.begin() + i);

        }
        else
        {

            std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> text_surface
                (TTF_RenderText_Solid(font.get(), print_list[i].text.c_str(),
                print_list[i].colour), SDL_FreeSurface);

            if(text_surface.get() == nullptr)
            {

                // throw surface creation exception

            }

            text_tex.reset(SDL_CreateTextureFromSurface(
                ren, text_surface.get()));
 
            if(text_tex.get() == nullptr)
            {

                // throw texture creation error

            }

            SDL_Rect dest;

            dest.x = print_list[i].x;

            dest.y = print_list[i].y;

            dest.w = text_surface.get()->w;

            dest.h = text_surface.get()->h;

            SDL_RenderCopy(ren, text_tex.get(), NULL, &dest);

        }

    }

}


void TextPrinter::AddText(std::string text, SDL_Color colour,
    float duration_sec, int x, int y)
{

    print_list.push_back(TimedText(text, colour, duration_sec,
        text_timer.GetTimeMs(), x, y));

}


void TextPrinter::LoadFont(std::string font_filename, int size)
{

    font.reset(TTF_OpenFont(font_filename.c_str(), size));

    if(font.get() == nullptr)
    {

        // throw font load error

    }

}
