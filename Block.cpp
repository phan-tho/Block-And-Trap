#include "def.h"
#include "LTexture.h"
#include <iostream>

LTexture gBackground;
LTexture gBlock;
LTexture gHeart;

class Block{
    public:
        const int BLOCK_HEIGHT = 10;
        const int BLOCK_WIDTH  = 65;
        
        int PosX, PosY;
    
        Block();
        
        void move();
        
        void end();
        
        void render();
};

class Heart{
    public:
        const int HEART_HEIGHT = 18;
        const int HEART_WIDTH  = 18;
        
        int PosX, PosY;
    
        Heart();
        
        void move();
        
        void render();
    
        void assignPos(const int x, const int y);
};

Block::Block(){
    PosY = FLOOR;
    PosX = rand()%(rPIVOT - BLOCK_WIDTH - lPIVOT + 1) + lPIVOT;
    
//    Heart heartOnBlock((PosX + BLOCK_WIDTH)/2, PosY - BLOCK_HEIGHT);
}

void Block::move(){
    PosY -= Denta_Y;
}

void Block::render(){
    gBlock.render(PosX, PosY, NULL);
}

Heart::Heart(){
    PosX = 0;
    PosY = 0;
}



void Heart::move(){
    PosY -= Denta_Y;
}

void Heart::render(){
    gHeart.render(PosX, PosY, NULL);
}

void Heart::assignPos(const int x, const int y){
    PosX = x;
    PosY = y;
}

int main( int argc, char* argv[] ){
    init();
    loadMedia();
    
    bool quit = false;
    SDL_Event e;
    
    std::deque<Block> Blocks;
    int cnt = 0;
    
//    Block block;
    Heart heart;
//    heart.assignPos(lPIVOT + 50, FLOOR - heart.HEART_HEIGHT);
    
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
        
        if( cnt % (vGEN_BLOCK*20) == 0 && cnt){               // Gen block and heart
            Block block;
            Blocks.push_back(block);
            
            heart.assignPos(block.PosX + block.BLOCK_HEIGHT/2 + heart.HEART_WIDTH, block.PosY - heart.HEART_HEIGHT);
        }
        else if(cnt % vGEN_BLOCK == 0){
            Block block;
            Blocks.push_back(block);
        }
        cnt++;
        
        for(auto it = Blocks.begin(); it != Blocks.end(); it++){                // MOVE
            (*it).move();
        }
        heart.move();
        
        if( ( *Blocks.begin() ).PosY <= CEILING )           Blocks.pop_front();             // eliminate block and heart out board

        for(auto it = Blocks.begin(); it != Blocks.end(); it++){
            (*it).render();
        }
        
        if(heart.PosY >= CEILING)     heart.render();
        
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    
    close();

    return 0;
}

void loadMedia(){
    gBackground.loadFromFile("BackGr.png");
    gBlock.loadFromFile("Block.png");
    gHeart.loadFromFile("Heart.png");
}

void close()
{
    //Free loaded images
    gBackground.freeFire();
    gBlock.freeFire();
    gHeart.freeFire();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


