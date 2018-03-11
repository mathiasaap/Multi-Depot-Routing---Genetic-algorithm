#ifndef Graphics_hpp
#define Graphics_hpp
#include "include/SDL2/SDL.h"
#include "route.hpp"

class Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int minX;
    int maxX;
    int minY;
    int maxY;
    int width, height;
    
    int colors[15][3];
    std::vector<Depot>& depots;
    int depotSize;
    int customerSize;
    void scaleCoordinates(int* x, int* y);
    bool finishEarly;
    
public:
    Graphics(int width, int height, int scale[], std::vector<Depot>& depots);
    ~Graphics();
    void draw(upRouteMap routes);
    void handleWindow();
    bool isFinishedEarly(){return finishEarly;}
};



#endif /* Graphics_hpp */


