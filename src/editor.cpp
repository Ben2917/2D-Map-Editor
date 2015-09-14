

#include "editor.h"


#include <iostream>


Editor::Editor() : map_tex(nullptr, SDL_DestroyTexture) {}


Editor::Editor(const Editor &e)
    : map_tex(e.map_tex)
{

    dir_handler = e.dir_handler;

    tiles = e.tiles;

    test = e.test;
    
    map_arr = e.map_arr;

    collidable = e.collidable;

}


Editor::Editor(std::string dir_name, SDL_Renderer* ren,
    int level_w, int level_h) :
    map_tex(SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET, level_w, level_h), SDL_DestroyTexture) 
{

    LoadTiles(ren, dir_name);

    // test = IMG_LoadTexture(ren, "resources/ceiling_tile.png");

    // test_tiles.push_back(test);

    // tiles.insert(std::pair<std::string, SDL_Texture*>("ceiling_tile.png", 
       //  test));

    // current_tile = 0;

    SDL_SetTextureBlendMode(map_tex.get(), SDL_BLENDMODE_BLEND);

    // test= IMG_LoadTexture(ren, "resources/ceiling_tile.png");

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
            
            std::cout << "Left clicked\n";
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

    std::cout << "Files found: " << filenames.size() << "\n";

    for(unsigned int i = 0; i < filenames.size(); ++i)
    {

        tiles.insert(std::pair<std::string, SDL_Texture*> 
            (filenames[i], IMG_LoadTexture(ren, 
            (std::string("resources/") + filenames[i]).c_str())));

        std::cout << (std::string("resources/") + filenames[i]).c_str()
            << "\n";

    }

    for(auto itr = tiles.begin(); itr != tiles.end(); ++itr)
    {

        if(itr->second == nullptr)
        {

            std::cout << "Null texture " << itr->first << " found.\n";

        }

    }

    tile_itr = tiles.begin();

    // Should generate warnings if tiles are different sizes,
    // if non-image files are found (include names) and
    // if there were any errors loading the images.

}


void Editor::NextTile()
{

    if(tile_itr != tiles.end())
    {

        ++tile_itr;

    }
    else
    {

        // print message "no more tiles"
        // prompt to use prev tile button to cycle back

    }

}


void Editor::PrevTile()
{
    
    if(tile_itr != tiles.begin())
    {

        --tile_itr;
    }
    else
    {

        // print error message

    }  

}


void Editor::PlaceTile(SDL_Renderer *ren)
{

    std::cout << "Placing tile.\n";
    int x, y;
    
    if(SDL_SetRenderTarget(ren, map_tex.get()) < 0)
    {

        std::cout << "Error setting render target.\n";

    }

    SDL_GetMouseState(&x, &y);
    SDL_Rect dest = GetGridSquare(x, y);
    
    std::cout << "dest.x " << dest.x << "\ndest.y " << dest.y <<
        "\ndest.w " << dest.w << "\ndest.h " << dest.h << "\n";

    int arr_x, arr_y;

    arr_x = dest.x;
    arr_y = dest.y;

    dest.x *= 64;
    dest.y *= 64;

    if(tiles["ceiling_tile.png"] == nullptr)
    {

        std::cout << "ceiling_tile.png is nullptr.\n";

    }

    SDL_RenderCopy(ren, tile_itr->second, NULL, &dest);
    std::cout << "tex copied to renderer.\n";

    if(SDL_SetRenderTarget(ren, NULL) < 0)
    {

        std::cout << "Error reseting render target.\n";

    }

    //map_arr[arr_x][arr_y] = tile_itr->first;
    /*
    std::cout << "Name loaded into array.\n";
    if(collidable)
    {
    
        map_arr[dest.x][dest.y] += std::string(" c ");
        std::cout << "Tile made collidable.\n";

    }*/

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


SDL_Texture* Editor::GetCurrentTile(std::string &tile_name)
{

    //std::cout << "Getting current tile.\n";

    //tile_name = tile_itr->first;

    //return tile_itr->second;

    return nullptr;

}


void Editor::WriteMapToFile()
{

    // write map_arr to txt file with each array being a new line
    // store the file in output directory under the name map txt.
    
    // eventually encrypt the file so it is harder to tamper with without
    // going through the editor.

}


