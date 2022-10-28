#include <iostream>
#include <iomanip>
#include <cstring>
#include <tuple>
#include <array>
#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <boost/format.hpp>
#include "GameClass.hpp"
#include <chrono>
using namespace std::chrono;
using namespace std;


const int width = 512;
const int height = 512;
const int squareSize = height/8;

SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
SDL_Surface *surface =  SDL_GetWindowSurface(window);
SDL_Surface *grid;
SDL_Renderer *render = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);



void DrawBoard(){
    bool colourPick = true;
    for (int y=0; y<8; y++) {

        tuple<int, int, int, int> primary = {255, 252, 231, 1};
        tuple<int, int, int, int> secondary = {0, 85, 0, 1};
        
        tuple<int, int, int, int> colour;
        
        for (int x=0; x<8; x++) {
            colourPick = !colourPick;
            
            SDL_Rect square;
            square.x = x * squareSize;
            square.y = y * squareSize;
            square.w = squareSize;
            square.h = squareSize;
            
            
            colour = (colourPick)? secondary : primary;
            SDL_SetRenderDrawColor(render, get<0>(colour), get<1>(colour), get<2>(colour), get<3>(colour));
            SDL_RenderFillRect(render, &square);
        }
        colourPick = !colourPick;
        colour = (colourPick)? secondary : primary;
        SDL_SetRenderDrawColor(render, get<0>(colour), get<1>(colour), get<2>(colour), get<3>(colour));
    }
    SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(render);
}


void DrawPieces(Game game){
    string pieces[12] = {"blackKing", "blackQueen", "blackRook", "blackKnight", "blackBishop", "blackPawn",
                         "whiteKing", "whiteQueen", "whiteRook", "whiteKnight", "whiteBishop", "whitePawn"};
    
    string basePath = "/Users/anirudhanvijay/Desktop/programs/SDLtest1/SDLtest1/Images/{ }.bmp";
    
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(game.GetBoard()[i][j].Type() != "empty"){
                Piece piece = game.GetBoard()[i][j];
                
                char basePathArr[69];
                strcpy(basePathArr, basePath.c_str());
                basePathArr[64] = piece.Colour()[0];
                basePathArr[65] = piece.Type()[0];
                basePathArr[66] = piece.Type()[1];
                
                SDL_Rect dest;
                    dest.x = j*squareSize;
                    dest.y = i*squareSize;
                    dest.w = squareSize;
                    dest.h = squareSize;

                SDL_Surface *pieceImage = SDL_LoadBMP(basePathArr);
                
                //method 1:
                
                SDL_BlitSurface(pieceImage, NULL, surface, &dest);
                SDL_FreeSurface(pieceImage);
                
                //method 2:
                
//                SDL_Texture * texture = SDL_CreateTextureFromSurface(render, pieceImage);
//                SDL_RenderCopy(render, texture, NULL, &dest);
//                SDL_RenderPresent(render);
//
//                SDL_DestroyTexture(texture);
//                SDL_FreeSurface(pieceImage);
            }
        }
    }
    SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(render);
}


int main(int argc, const char * argv[]) {
    
    // Boilerplate for SDL window
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }
    

    if(!window){
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Event event;
    bool running = true;
    
    
    Uint32 grey = SDL_MapRGB(surface->format, 130, 130, 130);
    SDL_FillRect(surface, NULL, grey);
    
    Game game = Game();
//    DrawBoard();
    DrawPieces(game);
    SDL_UpdateWindowSurface(window);
    
    while (running) {
    
        // Event handling
        while (SDL_PollEvent(&event)) {
            if(event.type ==  SDL_QUIT){
                running = false;
            }
        }
        
        // Rendering
        
        // Update window
    }
    
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return 0;
}


