#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade){
     fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p){
    HSLAPixel newPixel;
    newPixel.h = p.c.color.h;
    newPixel.s = p.c.color.s;
    double dist = sqrt((p.x - p.c.x) * (p.x - p.c.x) + (p.y - p.c.y) * (p.y - p.c.y));
    newPixel.l = p.c.color.l * pow(fadeFactor, dist);
    return newPixel;
}
