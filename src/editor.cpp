

#include "editor.h"


#include <iostream>


Editor::Editor() : map_tex(nullptr, SDL_DestroyTexture),
    t_printer(nullptr) {}

// constructor needs cleaning up
Editor::Editor(std::string font_name, int text_size, std::string dir_name,
    SDL_Renderer* ren, int level_w, int level_h) :
    map_tex(SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET, level_w, level_h), SDL_DestroyTexture),
    t_printer(new TextPrinter(font_name, text_size)) 
{

    collidable = false;

    LoadTiles(ren, dir_name);

    SDL_SetTextureBlendMode(map_tex.get(), SDL_BLENDMODE_BLEND);

}


Editor::~Editor()
{

    for(unsigned int i = 0; i < tiles.size(); ++i)
    {

        SDL_DestroyTexture(tiles[i]);
        
    }

}


void Editor::HandleEvents(SDL_Event e, SDL_Renderer *ren, SDL_Rect camera)
{

    if(e.type == SDL_MOUSEBUTTONDOWN)
    {

        HandleMouseButtons(e, ren, camera);

    }

    if(e.type == SDL_KEYDOWN)
    {

        HandleKeys(e);

    }

}


void Editor::Update(SDL_Renderer* ren, SDL_Rect camera)
{

    SDL_Rect dest = { 0 - camera.x, 0 - camera.y,
        3200, 3200 }; 

    SDL_RenderCopy(ren, map_tex.get(), NULL, &dest);

}


void Editor::HandleMouseButtons(SDL_Event e, 
    SDL_Renderer* ren, SDL_Rect camera)
{

    if(e.button.button == SDL_BUTTON_RIGHT)
    {

        // Remove tile

    }
    else if(e.button.button == SDL_BUTTON_LEFT)
    {

        PlaceTile(ren, camera);

    }

}


void Editor::HandleKeys(SDL_Event e)
{

    if(e.key.keysym.sym == SDLK_c)
    {

        collidable = !collidable;

    }
    if(e.key.keysym.sym == SDLK_z)
    {

        PrevTile();

    }
    if(e.key.keysym.sym == SDLK_x)
    {

        NextTile();

    }
    if(e.key.keysym.sym == SDLK_w)
    {

        WriteMapToFile();

    }

}


void Editor::ClearMap()
{

    for(int i = 0; i < 50; ++i)
    {

        for(int x = 0; x < 50; ++x)
        {

            map_arr[i][x] = 0;

        }

    }

}


void Editor::LoadTiles(SDL_Renderer *ren, std::string dir_name)
{

    ClearMap(); // zero out the whole array.

    dir_handler.ReadDirectory(dir_name, tile_map);

    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> temp_tex =
        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>
        (nullptr, SDL_DestroyTexture);

    // Probably needs refactoring into two different functions

    tiles.push_back(nullptr);

    // Starts at one to skip 0 which is reservered for empty space.
    for(unsigned int i = 1; i < tile_map.size(); ++i)
    {
        
        if(tile_map[i].find(".png") != std::string::npos)
        {      

            temp_tex.reset(IMG_LoadTexture(ren,
                (std::string("resources/") + tile_map[i]).c_str()));

            if(temp_tex.get() == nullptr)
            {

                // Generate warning.

            }
            else
            {

                tiles.push_back(temp_tex.get());
                
            }
        }
        else
        {

            std::cout << "Found the following, non-image, file: "
                << tile_map[i] << ".\n";

            tile_map.erase(tile_map.begin() + i);

        }


    }

    std::cout << "Amount of tiles " << tiles.size() << ".\n";

}


void Editor::NextTile()
{

    if(current_tile < tile_map.size())
    {

        ++current_tile;

    }
    else
    {

        t_printer.get()->AddText("No more tiles! Use Z to scroll back.",
            {255, 127, 127, 255}, 2.0f, 0, 0);
        
    }

}


void Editor::PrevTile()
{
   
    // Doesn't allow current tile to go to 
    // index reserved for empty space.
    if(current_tile > 1)
    {

        --current_tile;
        
    }
    else
    {

        t_printer.get()->AddText("No more tiles! Use X to scroll forward.",
            {255, 127, 127, 255}, 2.0,  0, 0);
        
    }  

}


void Editor::PlaceTile(SDL_Renderer *ren, SDL_Rect camera)
{

    int x, y;
    
    if(SDL_SetRenderTarget(ren, map_tex.get()) < 0)
    {

        // Throw render target setting exception

    }

    SDL_GetMouseState(&x, &y);
    SDL_Rect dest = GetGridSquare(x, y, camera);
    
    int arr_x, arr_y;

    arr_x = dest.x;
    arr_y = dest.y;

    dest.x *= 64;
    dest.y *= 64;

    // Change to text printer
    std::cout << "Current tile: " << tile_map[current_tile] << ".\n";

    SDL_RenderCopy(ren, tiles[current_tile], NULL, &dest);
    
    if(SDL_SetRenderTarget(ren, NULL) < 0)
    {

        // Throw render target setting exception

    }

    map_arr[arr_y][arr_x] = current_tile;
    
    if(collidable)
    {
    
        map_arr[arr_y][arr_x] *= -1;
        t_printer.get()->AddText("Collidable mode is on.", 
            {255, 127, 127, 255}, 60.0, 0, 670);

    }

}


SDL_Rect Editor::GetGridSquare(int x, int y, SDL_Rect camera)
{

    // TODO: Modify to accept different sized tiles
 
    std::cout << "Getting grid squares.\n";
 
    x += camera.x;

    y += camera.y;
 
    x = x / 64;

    y = y / 64;
 
    return { x, y, 64, 64 };   

}


void Editor::WriteMapToFile()
{

    // need to generate a key that maps each filename to an integer
    // so that writing to, and reading from, map files can be done 
    // more easily and reliably.

    dir_handler.WriteStringVectorToFile(tile_map, "map.txt", "output");

    dir_handler.Write2DIntArrayToFile(map_arr, "map.txt", "output");
    
    // eventually encrypt the file so it is harder to tamper with without
    // going through the editor.

}


