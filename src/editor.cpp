

#include "editor.h"


#include <iostream>


Editor::Editor() : map_tex(nullptr, SDL_DestroyTexture),
    t_printer(nullptr) {}


Editor::Editor(std::string font_name, int text_size, std::string dir_name,
    SDL_Renderer* ren, int level_w, int level_h) :
    map_tex(SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET, level_w, level_h), SDL_DestroyTexture),
    t_printer(new TextPrinter(font_name, text_size)) 
{

    LoadTiles(ren, dir_name);

    SDL_SetTextureBlendMode(map_tex.get(), SDL_BLENDMODE_BLEND);

}


Editor::~Editor()
{

    for(auto itr = tiles.begin(); itr != tiles.end(); ++itr)
    {

        SDL_DestroyTexture(itr->second);
        
    }

}


void Editor::HandleEvents(SDL_Event e, SDL_Renderer *ren)
{

    if(e.type == SDL_MOUSEBUTTONDOWN)
    {

        if(e.button.button == SDL_BUTTON_RIGHT)
        {

            // remove tile

        }

        if(e.button.button == SDL_BUTTON_LEFT)
        {
            
            PlaceTile(ren);

        }

    }

    if(e.type == SDL_KEYDOWN)
    {

        if(e.key.keysym.sym == SDLK_c)
        {

            collidable = !collidable;

        }
        if(e.key.keysym.sym == SDLK_z)
        {

            PrevTile(ren);

        }
        if(e.key.keysym.sym == SDLK_x)
        {

            NextTile(ren);

        }
        if(e.key.keysym.sym == SDLK_w)
        {

            WriteMapToFile();

        }

    }

}


void Editor::Update(SDL_Renderer* ren, SDL_Rect camera)
{

    SDL_Rect dest = { 0 - camera.x, 0 - camera.y,
        3200, 3200 }; 

    SDL_RenderCopy(ren, map_tex.get(), NULL, &dest);

}


void Editor::LoadTiles(SDL_Renderer *ren, std::string dir_name)
{

    std::vector<std::string> filenames;

    dir_handler.ReadDirectory(dir_name, filenames);

    for(unsigned int i = 0; i < filenames.size(); ++i)
    {

        tiles.insert(std::pair<std::string, SDL_Texture*> 
            (filenames[i], IMG_LoadTexture(ren, 
            (std::string("resources/") + filenames[i]).c_str())));

    }

    for(auto itr = tiles.begin(); itr != tiles.end(); ++itr)
    {

        if(itr->second == nullptr)
        {

            // Throw exception

        }

    }

    tile_itr = tiles.begin();

    // Should generate warnings if tiles are different sizes,
    // if non-image files are found (include names) and
    // if there were any errors loading the images.

}


void Editor::NextTile(SDL_Renderer* ren)
{

    if(tile_itr != tiles.end())
    {

        ++tile_itr;

    }
    else
    {

        t_printer.get()->AddText("No more tiles! Use Z to scroll back.",
            {255, 127, 127, 255}, 2.0f, 0, 0);

    }

}


void Editor::PrevTile(SDL_Renderer* ren)
{
    
    if(tile_itr != tiles.begin())
    {

        --tile_itr;
    }
    else
    {

        t_printer.get()->AddText("No more tiles! Use X to scroll forward.",
            {255, 127, 127, 255}, 2.0,  0, 0);

    }  

}


void Editor::PlaceTile(SDL_Renderer *ren)
{

    int x, y;
    
    if(SDL_SetRenderTarget(ren, map_tex.get()) < 0)
    {

        // Throw render target setting exception

    }

    SDL_GetMouseState(&x, &y);
    SDL_Rect dest = GetGridSquare(x, y);
    
    int arr_x, arr_y;

    arr_x = dest.x;
    arr_y = dest.y;

    dest.x *= 64;
    dest.y *= 64;

    SDL_RenderCopy(ren, tile_itr->second, NULL, &dest);

    if(SDL_SetRenderTarget(ren, NULL) < 0)
    {

        // Throw render target setting exception

    }

    map_arr[arr_x][arr_y] = tile_itr->first;
    
    if(collidable)
    {
    
        map_arr[dest.x][dest.y] += std::string(" c ");
        t_printer.get()->AddText("Collidable mode is on.", 
            {255, 127, 127, 255}, 0.0, 0, 670);

    }

}


SDL_Rect Editor::GetGridSquare(int x, int y)
{

    // TODO: Modify to accept different sized tiles
 
    std::cout << "Getting grid squares.\n";
 
    // add camera to x and y to make it relative to camera
  
    x = x / 64;

    y = y / 64;
 
    return { x, y, 64, 64 };   

}


void Editor::WriteMapToFile()
{

    // write map_arr to txt file with each array being a new line
    // store the file in output directory under the name map txt.
    
    // eventually encrypt the file so it is harder to tamper with without
    // going through the editor.

}


