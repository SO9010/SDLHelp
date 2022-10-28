#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameClass.hpp"

#define WIDTH 512
#define HEIGHT 512
#define SQUARESIZE 64

void DrawBoard(SDL_Renderer *render){
    int startPos = 0;
    for (int y = 0; y < 8; y++) {       
        for (int x = startPos; x < 8; x+=2) {           
                SDL_Rect square;
                square.x = x * SQUARESIZE;
                square.y = y * SQUARESIZE;
                square.w = SQUARESIZE;
                square.h = SQUARESIZE;
                SDL_SetRenderDrawColor(render, 0, 85, 0, 255);
                SDL_RenderFillRect(render, &square);              
        }
        startPos = 1 - startPos;
    }
}

void DrawPieces(Game game, SDL_Renderer * render){
    string pieces[12] = {"blackKing", "blackQueen", "blackRook", "blackKnight", "blackBishop", "blackPawn",
                         "whiteKing", "whiteQueen", "whiteRook", "whiteKnight", "whiteBishop", "whitePawn"};
    //if your in the working directory you can just use ../ to go back a dir (This would be useful in a multifile project)
    string basePath = "../Images/{ }.bmp";
    
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
                    dest.x = j*SQUARESIZE;
                    dest.y = i*SQUARESIZE;
                    dest.w = SQUARESIZE;
                    dest.h = SQUARESIZE;


                for(auto i = 0; i < 69; i++){
                    std::cout << basePathArr[i];
                }
                std::cout << std::endl;
                SDL_Surface *pieceImage = SDL_LoadBMP("../Images/bBi.bmp");
                
                SDL_Texture * texture = SDL_CreateTextureFromSurface(render, pieceImage);
                if(SDL_RenderCopy(render, texture, NULL, &dest) < 0){
                    std::cout << SDL_GetError() << std::endl;
                }

               // SDL_DestroyTexture(texture);
              //  SDL_FreeSurface(pieceImage);
            }
        }
    }
}


int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    bool running = false;

    if(render){
        std::cout << "renderer created!" << std::endl;
        running = true;
    }
    else{
        running = false;
    }
    Game game = Game();
    while(running){
        SDL_Event event;
        if(SDL_WaitEvent(&event)) {
            if(event.type ==  SDL_QUIT){
                running = false;
            }
        }
        // refresh screen
        SDL_SetRenderDrawColor(render, 255, 252, 231, 255);
        SDL_RenderClear(render);

        //Put the things we want to draw here
        DrawBoard(render);
        DrawPieces(game, render);
        SDL_RenderPresent(render);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    IMG_Quit();
    SDL_Quit();
    return 0;
}