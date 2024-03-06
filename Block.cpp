#include "def.h"
#include "LTexture.h"
#include <iostream>

LTexture gBackground;
LTexture gBlock;

struct Block{
    const int BLOCK_HEIGHT = 10;
    const int BLOCK_WIDTH  = 65;
    
    int Denta_Y = 3;
    
    int PosX, PosY;
    
    Block();
    
    void move();
    
    void end();
    
    void render();
};

Block::Block(){
    PosY = FLOOR;
    PosX = rand()%(rPIVOT - BLOCK_WIDTH - lPIVOT + 1) + lPIVOT;
}

void Block::move(){
    PosY -= Denta_Y;
}

void Block::render(){
    gBlock.render(PosX, PosY, NULL);
}

void Block::end(){
    
}


int main( int argc, char* argv[] ){
    init();
    loadMedia();
    
    bool quit = false;
    SDL_Event e;
    
    std::queue<Block> Blocks;
    
    Block block;
    
    while( !quit ){
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_x)        quit = true;
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //Render objects
        gBackground.render(0, 0, NULL);
        
        // move and render block
        block.move();
        if(block.PosY >= CEILING)      block.render();
        
        
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    
    close();

    return 0;
}

void loadMedia(){
    gBackground.loadFromFile("BackGr.png");
    gBlock.loadFromFile("Block.png");
}

void close()
{
    //Free loaded images
    gBackground.freeFire();
    gBlock.freeFire();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


