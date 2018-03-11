
#include "Graphics.hpp"

Graphics::Graphics(int width, int height, int scale[], std::vector<Depot>& depots)
:depots(depots),
width(width),
height(height),
finishEarly(false),
colors{{102,0,255}, {0,255,255}, {255,0,51},{204,102,51}, {255,51,255},{255,255,102}, {173,255,47},{102,0,0}, {36,24,194}, {24,194,132}, {136,165,1}, {165,1,151},{124,2,24},{2,97,124}, {121,131,49}}

{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    depotSize = 15;
    customerSize = 8;
    
    minX = scale[0];
    maxX = scale[2];
    minY = scale[1];
    maxY = scale[3];
            
    
}
        
Graphics::~Graphics()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
     SDL_Quit();
            
}

void Graphics::draw(upRouteMap routes)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    for(auto depotIt = depots.begin(); depotIt != depots.end(); depotIt++)
    {
        
        int x =depotIt->getX();
        int y =depotIt->getY();
        scaleCoordinates(&x,&y);
        
        SDL_Rect rect;
        rect.x = x-depotSize/2;
        rect.y = y-depotSize/2;
        rect.w = depotSize;
        rect.h = depotSize;
        
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
        
    }
    
    for(auto depotIt = routes->begin(); depotIt != routes->end(); depotIt++)
    {
        int depotX = depots[depotIt->first-1].getX();
        int depotY = depots[depotIt->first-1].getY();
        scaleCoordinates(&depotX, &depotY);
        int colorId = 0;
        for (auto route = depotIt->second.begin(); route != depotIt->second.end(); route++)
        {
            int prevX = depotX;
            int prevY = depotY;
            
            auto custList = (*route)->getCustomerList();
            
            for(auto cust = custList.begin(); cust != custList.end(); cust++)
            {
                int x = (*cust)->x;
                int y = (*cust)->y;
                scaleCoordinates(&x, &y);
                
                SDL_Rect rect;
                rect.x = x-customerSize/2;
                rect.y = y-customerSize/2;
                rect.w = customerSize;
                rect.h = customerSize;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(renderer, &rect);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, colors[colorId][0], colors[colorId][1], colors[colorId][2], SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, x, y, prevX, prevY);
                
                prevX=x;
                prevY=y;
            }
            SDL_RenderDrawLine(renderer, depotX, depotY, prevX, prevY);
            colorId++;
        }
        
        
    }
    SDL_RenderPresent(renderer);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            finishEarly = true;
        }
    }
    
}

void Graphics::scaleCoordinates(int* x, int* y)
{
    int scaleFactor = std::max((maxX-minX),(maxY-minY));
    *x = float((*x-minX))/scaleFactor *(width-20)+10;
    *y = float((*y-minY))/scaleFactor *(height-20)+10;
    
}

void Graphics::handleWindow()
{
    // To do event handling for window
}

 
