#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(unsigned int borderSize, HSLAPixel fillColor, PNG &img, double tolerance){
    this->borderSize = borderSize; 
    this->fillColor = fillColor;    
    this->img = img;                
    this->tolerance = tolerance; 
}

bool borderColorPicker::IsWithinBorder(point p){
    if((p.x >= img.width()-borderSize) || (p.x < borderSize) ||
     (p.y >= img.height()-borderSize) || (p.y < borderSize)){
         return false;
     }
     return true;
}

HSLAPixel borderColorPicker::operator()(point p){

    while(IsWithinBorder(p)){
        int xStart = p.x-borderSize;
        int xEnd = p.x+borderSize;
        int yStart = p.y-borderSize;
        int yEnd = p.y+borderSize;
        int dist = 0;
        HSLAPixel* newPixel;

        for(int x = xStart; x <= xEnd; ++x){
            for(int y = yStart; y <= yEnd; ++y){
                newPixel = img.getPixel(x,y);
                dist = (x-p.x) * (x-p.x) + (y-p.y)*(y-p.y);
                if(newPixel->dist(p.c.color)>tolerance && dist <= borderSize*borderSize){
                    return fillColor;
                }
            }
        }
        return *img.getPixel(p.x, p.y);
    }
    return fillColor;
}
